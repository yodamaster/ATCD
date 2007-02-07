// $Id$

#include "ace/Get_Opt.h"
#include "Controller.h"

ACE_RCSID(LongUpcalls, blocking_client, "$Id$")

const char *ior = "file://test.ior";

int
parse_args (int argc, char *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, "k:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'k':
        ior = get_opts.opt_arg ();
        break;
      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-k <ior>"
                           "\n",
                           argv [0]),
                          -1);
      }
  // Indicates sucessful parsing of the command line
  return 0;
}

int
main (int argc, char *argv[])
{
  try
    {
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv);

      CORBA::Object_var object =
        orb->resolve_initial_references("RootPOA");

      if (CORBA::is_nil (object.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           " (%P|%t) Unable to initialize the POA.\n"),
                          1);

      PortableServer::POA_var root_poa =
        PortableServer::POA::_narrow (object.in ());

      PortableServer::POAManager_var poa_manager =
        root_poa->the_POAManager ();

      if (parse_args (argc, argv) != 0)
        return 1;

      Controller controller_impl;

      Test::Controller_var controller =
        controller_impl._this ();

      object = orb->string_to_object (ior);

      Test::Manager_var manager =
        Test::Manager::_narrow (object.in ());

      if (CORBA::is_nil (manager.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           "Manager is nil\n"),
                          1);


      poa_manager->activate ();

      const CORBA::Short worker_count = 10;
      manager->start_workers (worker_count,
                              CORBA::Long (1000),
                              controller.in ());

      controller_impl.dump_results ();

      manager->shutdown ();

      root_poa->destroy (1, 1);

      orb->destroy ();
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught:");
      return 1;
    }

  return 0;
}
