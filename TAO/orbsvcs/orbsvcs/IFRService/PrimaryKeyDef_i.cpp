/* -*- C++ -*- */
// $Id$

#include "Repository_i.h"
#include "PrimaryKeyDef_i.h"

ACE_RCSID(IFR_Service, PrimaryKeyDef_i, "$Id$")

TAO_PrimaryKeyDef_i::TAO_PrimaryKeyDef_i (
    TAO_Repository_i *repo
  )
  : TAO_IRObject_i (repo),
    TAO_Contained_i (repo)
{
}

TAO_PrimaryKeyDef_i::~TAO_PrimaryKeyDef_i (void)
{
}

CORBA::DefinitionKind
TAO_PrimaryKeyDef_i::def_kind (ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  return CORBA::dk_PrimaryKey;
}

void
TAO_PrimaryKeyDef_i::destroy (ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_WRITE_GUARD;

  this->update_key (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK;

  this->destroy_i (ACE_ENV_SINGLE_ARG_PARAMETER);
}

void
TAO_PrimaryKeyDef_i::destroy_i (ACE_ENV_SINGLE_ARG_DECL_NOT_USED /* ACE_ENV_SINGLE_ARG_PARAMETER */)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // TODO
}

CORBA::Contained::Description *
TAO_PrimaryKeyDef_i::describe (ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (0);

  this->update_key (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK_RETURN (0);

  return this->describe_i (ACE_ENV_SINGLE_ARG_PARAMETER);
}

CORBA::Contained::Description *
TAO_PrimaryKeyDef_i::describe_i (ACE_ENV_SINGLE_ARG_DECL_NOT_USED /* ACE_ENV_SINGLE_ARG_PARAMETER */)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // TODO
  return 0;
}

CORBA::Boolean
TAO_PrimaryKeyDef_i::is_a (const char *primary_key_id
                           ACE_ENV_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (0);

  this->update_key (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK_RETURN (0);

  return this->is_a_i (primary_key_id
                       ACE_ENV_ARG_PARAMETER);
}

CORBA::Boolean
TAO_PrimaryKeyDef_i::is_a_i (const char * /* primary_key_id */
                             ACE_ENV_ARG_DECL_NOT_USED /* ACE_ENV_SINGLE_ARG_PARAMETER */ )
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // TODO
  return 0;
}

CORBA::ValueDef_ptr
TAO_PrimaryKeyDef_i::primary_key (ACE_ENV_SINGLE_ARG_DECL)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (CORBA::ValueDef::_nil ());

  this->update_key (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK_RETURN (CORBA::ValueDef::_nil ());

  return this->primary_key_i (ACE_ENV_SINGLE_ARG_PARAMETER);
}

CORBA::ValueDef_ptr
TAO_PrimaryKeyDef_i::primary_key_i (ACE_ENV_SINGLE_ARG_DECL_NOT_USED /* ACE_ENV_SINGLE_ARG_PARAMETER */)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // TODO
  return 0;
}

