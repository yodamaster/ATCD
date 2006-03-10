// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be\be_codegen.cpp:277


#include "tao/PortableServer/ServantManagerC.h"
#include "tao/CDR.h"
#include "ace/OS_NS_string.h"

// TAO_IDL - Generated from
// be\be_visitor_arg_traits.cpp:70

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Arg traits specializations.
namespace TAO
{
}

#if (TAO_HAS_MINIMUM_POA == 0)

// TAO_IDL - Generated from
// be\be_visitor_interface/interface_cs.cpp:60

// Traits specializations for PortableServer::ServantManager.

PortableServer::ServantManager_ptr
TAO::Objref_Traits<PortableServer::ServantManager>::duplicate (
    PortableServer::ServantManager_ptr p
  )
{
  return PortableServer::ServantManager::_duplicate (p);
}

void
TAO::Objref_Traits<PortableServer::ServantManager>::release (
    PortableServer::ServantManager_ptr p
  )
{
  CORBA::release (p);
}

PortableServer::ServantManager_ptr
TAO::Objref_Traits<PortableServer::ServantManager>::nil (void)
{
  return PortableServer::ServantManager::_nil ();
}

CORBA::Boolean
TAO::Objref_Traits<PortableServer::ServantManager>::marshal (
    PortableServer::ServantManager_ptr p,
    TAO_OutputCDR & cdr
  )
{
  return CORBA::Object::marshal (p, cdr);
}

PortableServer::ServantManager::ServantManager (void)
{}

PortableServer::ServantManager::~ServantManager (void)
{}

PortableServer::ServantManager_ptr
PortableServer::ServantManager::_narrow (
    CORBA::Object_ptr _tao_objref
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  return ServantManager::_duplicate (
      dynamic_cast<ServantManager_ptr> (_tao_objref)
    );
}

PortableServer::ServantManager_ptr
PortableServer::ServantManager::_unchecked_narrow (
    CORBA::Object_ptr _tao_objref
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  return ServantManager::_duplicate (
      dynamic_cast<ServantManager_ptr> (_tao_objref)
    );
}

PortableServer::ServantManager_ptr
PortableServer::ServantManager::_duplicate (ServantManager_ptr obj)
{
  if (! CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

void
PortableServer::ServantManager::_tao_release (ServantManager_ptr obj)
{
  CORBA::release (obj);
}

CORBA::Boolean
PortableServer::ServantManager::_is_a (
    const char *value
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  if (
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/PortableServer/ServantManager:2.3"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/CORBA/LocalObject:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/CORBA/Object:1.0"
        )
    )
    {
      return true; // success using local knowledge
    }
  else
    {
      return false;
    }
}

const char* PortableServer::ServantManager::_interface_repository_id (void) const
{
  return "IDL:omg.org/PortableServer/ServantManager:2.3";
}

CORBA::Boolean
PortableServer::ServantManager::marshal (TAO_OutputCDR &)
{
  return false;
}

TAO_END_VERSIONED_NAMESPACE_DECL

#endif /* TAO_HAS_MINIMUM_CORBA == 0 */
