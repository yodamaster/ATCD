// -*- C++ -*-
// $Id$

#include "dds4ccm/impl/DataReaderStateListener_T.h"
#include "dds4ccm/impl/Updater_T.h"
#include "dds4ccm/impl/logger/Log_Macros.h"

#if (CIAO_DDS4CCM_OPENDDS==1)
#include "dds/DCPS/Marked_Default_Qos.h"
#endif

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::DDS_Update_T (void)
{
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::~DDS_Update_T (void)
{
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
void
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::set_component (::CORBA::Object_ptr component)
{
  this->dds_update_->_set_component (component);
  this->ccm_data_writer_->_set_component (component);
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
void
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::configuration_complete (
  ::DDS::Topic_ptr topic,
  ::DDS::Publisher_ptr publisher,
  const char * qos_profile,
  DDS_XML_QOS_PARSER_TYPE* qos_xml)
{
  DDS4CCM_TRACE ("DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::configuration_complete");
  ::DDS::DataWriter_var dw = this->dds_update_->get_dds_writer ();
  if (::CORBA::is_nil (dw.in ()))
    {
      ::DDS::DataWriter_var dwv_tmp;
#if (CIAO_DDS4CCM_NDDS==1)
      if (qos_profile)
        {
          dwv_tmp = publisher->create_datawriter_with_profile (
              topic,
              qos_profile,
              ::DDS::DataWriterListener::_nil (),
              0);
        }
      else
#endif
        {
          ::DDS::DataWriterQos dwqos;
          DDS::ReturnCode_t const retcode =
            publisher->get_default_datawriter_qos (dwqos);

          if (retcode != DDS::RETCODE_OK)
            {
              DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_ERROR, (LM_ERROR, DDS4CCM_INFO
                  "DDS_Update_T::configuration_complete - "
                  "Error: Unable to retrieve get_default_datawriter_qos: <%C>\n",
                  ::CIAO::DDS4CCM::translate_retcode (retcode)));
              throw ::CCM_DDS::InternalError (retcode, 0);
            }

          if (qos_profile && qos_xml)
            {
              CORBA::String_var name = topic->get_name ();
              DDS::ReturnCode_t const retcode_dw_qos = qos_xml->get_datawriter_qos (
                                          dwqos,
                                          qos_profile,
                                          name.in ());
              if (retcode_dw_qos != DDS::RETCODE_OK)
                {
                  DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_ERROR, (LM_ERROR, DDS4CCM_INFO
                      "DDS_Update_T::configuration_complete - "
                      "Error: Unable to retrieve datawriter QOS from XML: <%C>\n",
                      ::CIAO::DDS4CCM::translate_retcode (retcode_dw_qos)));
                  throw ::CCM_DDS::InternalError (retcode_dw_qos, 0);
                }
            }

#if defined GEN_OSTREAM_OPS
          if (DDS4CCM_debug_level >= DDS4CCM_LOG_LEVEL_DDS_STATUS)
            {
              std::stringstream output;
              output << dwqos;
              std::string message = output.str();
              DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_DDS_STATUS, (LM_INFO, DDS4CCM_INFO
                            ACE_TEXT ("DDS_Update_T::configuration_complete - ")
                            ACE_TEXT ("Using datawriter QOS <%C>\n"), message.c_str()));
            }
#endif

          dwv_tmp = publisher->create_datawriter (
              topic,
              dwqos,
              ::DDS::DataWriterListener::_nil (),
              0);
        }
      if (!::CORBA::is_nil (dwv_tmp.in ()))
        {
          DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_ACTION, (LM_TRACE, DDS4CCM_INFO
                      "DDS_Update_T::configuration_complete - "
                      "Created datawriter "
                      DDS_ENTITY_FORMAT_SPECIFIER
                      " using publisher "
                      DDS_ENTITY_FORMAT_SPECIFIER
                      "\n",
                      DDS_ENTITY_LOG (dwv_tmp.in ()),
                      DDS_ENTITY_LOG (publisher)));
        }
      else
        {
          DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_DDS_NIL_RETURN, (LM_ERROR, DDS4CCM_INFO
                        "DDS_Update_T::configuration_complete - "
                        "Error: DDS returned a nil datawriter.\n"));
          throw ::CORBA::INTERNAL ();
        }

      this->dds_update_->set_dds_writer (dwv_tmp.in ());
      this->ccm_data_writer_->set_dds_entity (dwv_tmp.in ());

      DDS::ReturnCode_t const retcode = dwv_tmp->enable ();
      if (retcode != ::DDS::RETCODE_OK)
        {
          DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_ERROR, (LM_ERROR, DDS4CCM_INFO
                        "DDS_Update_T::configuration_complete - "
                        "Error: Unable to enable the datawriter: <%C>\n",
                        ::CIAO::DDS4CCM::translate_retcode (retcode)));
          throw ::CORBA::INTERNAL ();
        }
    }
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
void
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::activate ()
{
  DDS4CCM_TRACE ("DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::activate");
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
void
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::passivate ()
{
  DDS4CCM_TRACE ("DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::passivate");
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
void
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::remove (
  ::DDS::Publisher_ptr publisher)
{
  DDS4CCM_TRACE ("DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::remove");

  ::DDS::DataWriter_var writer = this->dds_update_->get_dds_writer ();

  this->dds_update_->set_dds_writer (::DDS::DataWriter::_nil ());
  this->ccm_data_writer_->set_dds_entity (::DDS::DataWriter::_nil ());

  if (!::CORBA::is_nil (writer.in ()))
    {
      DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_ACTION_STARTING, (LM_TRACE, DDS4CCM_INFO
                  "DDS_Update_T::remove - "
                  "Going to delete DataWriter "
                  DDS_ENTITY_FORMAT_SPECIFIER
                  " from publisher "
                  DDS_ENTITY_FORMAT_SPECIFIER
                  "\n",
                  DDS_ENTITY_LOG (writer.in ()),
                  DDS_ENTITY_LOG (publisher)));

      DDS::ReturnCode_t const retval =
          publisher->delete_datawriter (writer.in ());

      if (retval != ::DDS::RETCODE_OK)
        {
          DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_ERROR, (LM_ERROR, DDS4CCM_INFO
              "DDS_Update_T::remove - "
              "Unable to delete DataWriter: <%C>\n",
              ::CIAO::DDS4CCM::translate_retcode (retval)));
          throw ::CORBA::INTERNAL ();
        }
      else
        {
          DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_DDS_STATUS, (LM_INFO, DDS4CCM_INFO
              "DDS_Update_T::remove - "
              "Deleted DataWriter: <%C>\n",
              ::CIAO::DDS4CCM::translate_retcode (retval)));
        }
    }
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
typename CCM_TYPE::data_type::_ptr_type
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::get_data (void)
{
  DDS4CCM_TRACE ("DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::get_data");

  return CCM_TYPE::data_type::_duplicate (this->dds_update_);
}

template <typename CCM_TYPE, typename TYPED_WRITER, typename VALUE_TYPE, typename SEQ_VALUE_TYPE>
typename CCM_TYPE::dds_entity_type::_ptr_type
DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::get_dds_entity (void)
{
  DDS4CCM_TRACE ("DDS_Update_T<CCM_TYPE, TYPED_WRITER, VALUE_TYPE, SEQ_VALUE_TYPE>::get_dds_entity");

  return ::DDS::CCM_DataWriter::_duplicate (this->ccm_data_writer_);
}

