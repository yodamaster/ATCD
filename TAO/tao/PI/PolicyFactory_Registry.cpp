#include "tao/PI/PolicyFactory_Registry.h"
#include "tao/PI/PolicyFactoryC.h"
#include "tao/ORB_Constants.h"
#include "tao/SystemException.h"
#include "tao/PolicyC.h"

ACE_RCSID (PI,
           PolicyFactory_Registry,
           "$Id$")


// ****************************************************************

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

TAO_PolicyFactory_Registry::TAO_PolicyFactory_Registry (void)
  : factories_ (TAO_DEFAULT_POLICY_FACTORY_REGISTRY_SIZE)
{
}

TAO_PolicyFactory_Registry::~TAO_PolicyFactory_Registry (void)
{
  const TABLE::iterator end (this->factories_.end ());

  for (TABLE::iterator i = this->factories_.begin (); i != end; ++i)
    {
      CORBA::release ((*i).int_id_);
    }

  this->factories_.close ();
}

void
TAO_PolicyFactory_Registry::register_policy_factory (
  CORBA::PolicyType type,
  PortableInterceptor::PolicyFactory_ptr policy_factory
  ACE_ENV_ARG_DECL)
{
  if (CORBA::is_nil (policy_factory))
    {
      ACE_THROW (CORBA::BAD_PARAM (
                   CORBA::SystemException::_tao_minor_code (
                     0,
                     EINVAL),
                   CORBA::COMPLETED_NO));
    }

  PortableInterceptor::PolicyFactory_ptr factory =
    PortableInterceptor::PolicyFactory::_duplicate (policy_factory);

  const int result = this->factories_.bind (type,
                                            factory);

  if (result != 0)
    {
      // Release the duplicated factory to prevent a memory leak
      CORBA::release (factory);

      if (result == 1)
        {
          // PolicyFactory of given type already exists.
          ACE_THROW (CORBA::BAD_INV_ORDER (CORBA::OMGVMCID | 16,
                                           CORBA::COMPLETED_NO));
        }
      else
        {
          // Could not add PolicyFactory due to internal bind failures.
          ACE_THROW (CORBA::INTERNAL ());
        }
    }
}

CORBA::Policy_ptr
TAO_PolicyFactory_Registry::create_policy (CORBA::PolicyType type,
                                           const CORBA::Any &value
                                           ACE_ENV_ARG_DECL)
{
  PortableInterceptor::PolicyFactory_ptr policy_factory =
    PortableInterceptor::PolicyFactory::_nil ();

  if (this->factories_.find (type, policy_factory) == -1)
    {
      // Policy factory corresponding to given policy type does not
      // exist in policy factory map.
      ACE_THROW_RETURN (
         CORBA::PolicyError (CORBA::BAD_POLICY_TYPE),  // @@ Right exception?
         CORBA::Policy::_nil ());
    }

  return policy_factory->create_policy (type,
                                        value
                                        ACE_ENV_ARG_PARAMETER);
}

CORBA::Policy_ptr
TAO_PolicyFactory_Registry::_create_policy (CORBA::PolicyType type
                                            ACE_ENV_ARG_DECL)
{
  PortableInterceptor::PolicyFactory_ptr policy_factory =
    PortableInterceptor::PolicyFactory::_nil ();

  if (this->factories_.find (type,
                             policy_factory) == -1)
    {
      // Policy factory corresponding to given policy type does not
      // exist in policy factory map.
      ACE_THROW_RETURN (
         CORBA::PolicyError (CORBA::BAD_POLICY_TYPE),  // @@ Right exception?
         CORBA::Policy::_nil ());
    }

  return policy_factory->_create_policy (type
                                         ACE_ENV_ARG_PARAMETER);
}

bool
TAO_PolicyFactory_Registry::factory_exists (CORBA::PolicyType & type) const
{
  return (this->factories_.find (type) == 0);
}


TAO_END_VERSIONED_NAMESPACE_DECL
