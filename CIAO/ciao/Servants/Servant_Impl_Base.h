// -*- C++ -*-

//=============================================================================
/**
 *  @file    Servant_Impl_Base.h
 *
 *  $Id$
 *
 *  This file contains the non-template declaration of a base class for
 *  the template mixin for the generated component servant class.
 *
 *  @author Jeff Parsons <j.parsons@vanderbilt.edu>
 */
//=============================================================================

#ifndef CIAO_SERVANT_IMPL_BASE_H
#define CIAO_SERVANT_IMPL_BASE_H

#include /**/ "ace/pre.h"

#include "Connector_Servant_Impl_Base.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

namespace CIAO
{
#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
  namespace Servant
  {
    template<typename T_var>
    void describe_pub_event_source (
        const char *port_name,
        const char *port_type_repo_id,
        std::map <ptrdiff_t, T_var> &consumers,
        ::Components::PublisherDescriptions_var &descriptions,
        CORBA::ULong slot);

    template<typename T_var>
    void describe_emit_event_source (
        const char *port_name,
        const char *port_type_repo_id,
        T_var &consumer_ref,
        ::Components::EmitterDescriptions_var &descriptions,
        CORBA::ULong slot);
  } /* Servant */
#endif
  /**
   * @class Servant_Impl_Base
   *
   * @brief Non-template base class for Servant_Impl.
   *
   * Holds the non-template parts of its child class
   * Servant_Impl. Inherits from Connector_Servant_Impl_Base,
   * which contains the facet and receptacle functionality that
   * Connectors are limited to.
   */
  class CIAO_Servant_Impl_Export Servant_Impl_Base
    : public Connector_Servant_Impl_Base
  {
  protected:
    Servant_Impl_Base (Components::CCMHome_ptr home,
                       Home_Servant_Impl_Base *home_servant,
                       Container_ptr  c);

  public:
    virtual ~Servant_Impl_Base (void);

    /// Operations for CCMObject interface.
    virtual void remove (void);

#if !defined (CCM_LW)
    virtual ::Components::ComponentPortDescription * get_all_ports (void);
#endif

#if !defined (CCM_LW)
    virtual ::Components::PrimaryKeyBase * get_primary_key (void);
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
    virtual ::Components::ConsumerDescriptions * get_all_consumers (void);
#endif

#if !defined (CCM_NOEVENT)
    virtual ::Components::EventConsumerBase_ptr
    get_consumer (const char *sink_name);
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
    virtual ::Components::ConsumerDescriptions *
    get_named_consumers (const ::Components::NameList & names);
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
    virtual ::Components::EmitterDescriptions *
    get_named_emitters (const ::Components::NameList & names);
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
    virtual ::Components::PublisherDescriptions *
    get_named_publishers (const ::Components::NameList & names);
#endif

  protected:
#if !defined (CCM_NOEVENT)
    void add_consumer (const char *port_name,
                       ::Components::EventConsumerBase_ptr port_ref);
#endif

#if !defined (CCM_NOEVENT)
    ::Components::EventConsumerBase_ptr lookup_consumer (
      const char *port_name);
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
    ::Components::ConsumerDescription *lookup_consumer_description (
      const char *port_name);
#endif

  private:

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
    ::Components::PublisherDescription *
    lookup_publisher_description (const char *publisher_name);
#endif

#if !defined (CCM_LW) && !defined (CCM_NOEVENT)
    ::Components::EmitterDescription *
    lookup_emitter_description(const char* emitter_name);
#endif

  protected:
#if !defined (CCM_NOEVENT)
    typedef std::map <ACE_CString, ::Components::EventConsumerBase_var>
       ConsumerTable;

    ConsumerTable consumer_table_;
#endif
    };
}

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "Servant_Impl_Utils_T.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Servant_Impl_Utils_T.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#include /**/ "ace/post.h"

#endif /* CIAO_SERVANT_IMPL_BASE_H */
