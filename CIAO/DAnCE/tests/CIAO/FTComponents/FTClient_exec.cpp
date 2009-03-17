// $Id$
//
// ****              Code generated by the                 ****
// ****  Component Integrated ACE ORB (CIAO) CIDL Compiler ****
// CIAO has been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// CIDL Compiler has been developed by:
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about CIAO is available at:
//    http://www.dre.vanderbilt.edu/CIAO

#include "FTClient_exec.h"
#include "FTClient_svnt.h"
#include "ace/Reactor.h"
#include "tao/ORB_Core.h"
#include "ciao/CIAO_common.h"
#include "ciao/Containers/Container_Base.h"
#include "FTClient_Timer_Handler.h"
#include "ciao/FTComponentServer/Name_Helper_T.h"

namespace CIDL_FTClient_Impl
{
  //==================================================================
  // Component Executor Implementation Class:   FTClient_exec_i
  //==================================================================

  FTClient_exec_i::FTClient_exec_i (void)
    : period_ (0.0),
      execution_time_ (0.0),
      iterations_ (0),
      name_ ("?"),
      started_ (false),
      orb_ (CORBA::ORB::_nil ()),
      timeout_handler_ (this)
  {
  }

  FTClient_exec_i::~FTClient_exec_i (void)
  {
  }

  // Supported or inherited operations.

  void
  FTClient_exec_i::start (const char * prefix)
  {
    CIAO_TRACE ("FTClient_exec_i::start ()");

    if (!started_)
      {
        timeout_handler_.set_prefix (prefix);

        // register the timer handler with the ORB reactor
        ACE_Time_Value period;
        period.msec (static_cast<long> (period_));

        orb_->orb_core ()->reactor ()->schedule_timer (&timeout_handler_,
                                                       0,
                                                       ACE_Time_Value::zero,
                                                       period);

        started_ = true;
      }    
  }

  // Attribute operations.

  ::CORBA::Double
  FTClient_exec_i::period ()
  {
    // Your code here.
    return period_;
  }

  void
  FTClient_exec_i::period (::CORBA::Double period)
  {
    period_ = period;
  }

  ::CORBA::Double
  FTClient_exec_i::execution_time ()
  {
    return execution_time_;
  }

  void
  FTClient_exec_i::execution_time (::CORBA::Double execution_time)
  {
    execution_time_ = execution_time;
  }

  ::CORBA::ULong
  FTClient_exec_i::iterations ()
  {
    return iterations_;
  }

  void
  FTClient_exec_i::iterations (::CORBA::ULong iterations)
  {
    iterations_ = iterations;
  }

  char *
  FTClient_exec_i::server_ior ()
  {
    return CORBA::string_dup (server_ior_.in ());
  }

  void
  FTClient_exec_i::server_ior (const char * server_ior)
  {
    server_ior_ = server_ior;
  }

  DeCoRAM::Worker_ptr 
  FTClient_exec_i::server (void)
  {
    CORBA::Object_var obj = orb_->string_to_object (server_ior_);

    return DeCoRAM::Worker::_narrow (obj.in ());
  }

  char *
  FTClient_exec_i::name (void)
  {
    return CORBA::string_dup (name_.c_str ());
  }

  void
  FTClient_exec_i::name (const char * name)
  {
    name_ = name;
  }

  ::CORBA::Object_ptr
  FTClient_exec_i::COMPONENT_REFERENCE ()
  {
    CIAO_TRACE ("FTClient_exec_i::COMPONENT_REFERENCE () getter");
    return CORBA::Object::_duplicate (myself_.in ());
  }

  void
  FTClient_exec_i::COMPONENT_REFERENCE (::CORBA::Object_ptr COMPONENT_REFERENCE)
  {
    CIAO_TRACE ("FTClient_exec_i::COMPONENT_REFERENCE () setter");
    myself_ = CORBA::Object::_duplicate (COMPONENT_REFERENCE);
  }

  // Port operations.

  // Operations from Components::SessionComponent

  void
  FTClient_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->context_ =
      DeCoRAM::CCM_FTClient_Context::_narrow (ctx);

    if (CORBA::is_nil (this->context_.in ()))
    {
      throw ::CORBA::INTERNAL ();
    }

    CIDL_FTClient_Impl::FTClient_Context * ft_context = 
      CIDL_FTClient_Impl::FTClient_Context::_narrow (context_.in ());

    if (0 == ft_context)
      {
	CIAO_ERROR ((LM_ERROR, "could not narrow to SimpleFT_Context\n"));
	return;
      }

    CIAO::Container_var container = ft_context->_ciao_the_Container ();

    CIAO::Container_i * ci = dynamic_cast <CIAO::Container_i*> (container.in ());

    if (ci == 0)
      {
	CIAO_ERROR ((LM_WARNING, "could not cast to Container_i\n"));
	return;
      }

    orb_ = ci->the_ORB ();

    timeout_handler_.set_orb (orb_.in ());
  }

  void
  FTClient_exec_i::configuration_complete ()
  {
    // Your code here.
  }

  void
  FTClient_exec_i::ccm_activate ()
  {
    CIAO_TRACE ("FTClient_exec_i::ccm_activate ()");

    // publish application in NameService for the client

    Name_Helper_T <Trigger> tnh (orb_.in ());

    Trigger_var ref = Trigger::_narrow (myself_.in ());

    tnh.bind ("FLARE_TESTAPPLICATION/" + name_ + "Client",
              ref.in ());

    // and write it to a file
    std::string iorfilename = name_ + "Client.ior";
    std::ofstream file (iorfilename.c_str ());
    file << orb_->object_to_string (ref.in ());
    file.flush ();
    file.close ();
  }

  void
  FTClient_exec_i::ccm_passivate ()
  {
    orb_->orb_core ()->reactor ()->cancel_timer (&timeout_handler_);

    timeout_handler_.dump ();
  }

  void
  FTClient_exec_i::ccm_remove ()
  {
    // Your code here.
  }

  extern "C" FTCLIENT_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_DeCoRAM_FTClient_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();
    
    ACE_NEW_RETURN (retval,
                    FTClient_exec_i,
                    ::Components::EnterpriseComponent::_nil ());
    
    return retval;
  }

  //==================================================================
  // Home Executor Implementation Class:   FTClientHome_exec_i
  //==================================================================

  FTClientHome_exec_i::FTClientHome_exec_i (void)
  {
  }

  FTClientHome_exec_i::~FTClientHome_exec_i (void)
  {
  }

  // Supported or inherited operations.

  // Home operations.

  // Factory and finder operations.

  // Attribute operations.

  // Implicit operations.

  ::Components::EnterpriseComponent_ptr
  FTClientHome_exec_i::create ()
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_THROW_EX (
      retval,
      FTClient_exec_i,
      ::CORBA::NO_MEMORY ());

    return retval;
  }

  extern "C" FTCLIENT_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_DeCoRAM_FTClientHome_Impl (void)
  {
    ::Components::HomeExecutorBase_ptr retval =
      ::Components::HomeExecutorBase::_nil ();

    ACE_NEW_RETURN (
      retval,
      FTClientHome_exec_i,
      ::Components::HomeExecutorBase::_nil ());

    return retval;
  }
}
