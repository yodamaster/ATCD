#include "ami_msm_i.h"
#include "tao/debug.h"

ACE_RCSID(AMI, ami_test_i, "$Id$")

AMI_Msm_i::AMI_Msm_i (CORBA::ORB_ptr orb)
    :  orb_ (CORBA::ORB::_duplicate (orb)),
       answer_count_ (0)
{
}

void
AMI_Msm_i::foo (const char* string, ::CORBA::String_out answer)
{
  try
    {
      ACE_OS::sleep (1);
      ++answer_count_;
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%N:%l:(%P:%t):AMI_Msm_i::foo:  %d %C\n"),
                  answer_count_,
                  string));
      char tmp[255] = {0};
      ACE_OS::sprintf(tmp, "Hello World %d", answer_count_);
      answer = CORBA::string_dup (tmp);
    }
  catch (const CORBA::Exception& e)
    {
      throw A::InternalError (123, ACE_TEXT ("CORBA exception"));
    }
  catch (...)
    {
      throw A::InternalError (456, ACE_TEXT ("Unknow exception"));
    }
  //answer = answer_count_;
}

void
AMI_Msm_i::shutdown (void)
{
  this->orb_->shutdown (0);
}
