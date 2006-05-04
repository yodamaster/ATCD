// $Id$

#include "tao/GIOP_Message_State.h"
#include "tao/debug.h"
#include "tao/GIOP_Message_Base.h"

#include "ace/Log_Msg.h"

#if !defined (__ACE_INLINE__)
# include "tao/GIOP_Message_State.inl"
#endif /* __ACE_INLINE__ */

ACE_RCSID (tao,
           GIOP_Message_State,
           "$Id$")

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

TAO_GIOP_Message_State::TAO_GIOP_Message_State (void)
  : giop_version_ (TAO_DEF_GIOP_MAJOR,
                   TAO_DEF_GIOP_MINOR),
    byte_order_ (0),
    message_type_ (0),
    message_size_ (0),
    more_fragments_ (0),
    missing_data_ (0)
{
}


int
TAO_GIOP_Message_State::parse_message_header (ACE_Message_Block &incoming)
{
  if (incoming.length () >= TAO_GIOP_MESSAGE_HEADER_LEN)
    {
      // Parse the GIOP header
      return this->parse_message_header_i (incoming);
    }

  // One indicates that we didn't have enough data in the message to
  // parse the header
  return 1;
}

int
TAO_GIOP_Message_State::parse_message_header_i (ACE_Message_Block &incoming)
{
  if (TAO_debug_level > 8)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "TAO (%P|%t) - GIOP_Message_State::parse_message_header_i\n"
                  ));
    }

  // Grab the rd_ptr_ from the message block..
  char *buf = incoming.rd_ptr ();

  // Parse the magic bytes first
  if (this->parse_magic_bytes (buf) == -1)
    {
      return -1;
    }

  // Get the version information
  if (this->get_version_info (buf) == -1)
    return -1;

  // Get the byte order information...
  if (this->get_byte_order_info (buf) == -1)
    return -1;

  // Get the message type
  this->message_type_ = buf[TAO_GIOP_MESSAGE_TYPE_OFFSET];

  // Get the size of the message..
  this->get_payload_size (buf);

  if (this->message_size_ == 0)
    {
      if (this->message_type_ == TAO_GIOP_MESSAGERROR)
        {
          if (TAO_debug_level > 0)
            {
              ACE_DEBUG ((LM_DEBUG,
                          "TAO (%P|%t) -"
                          "GIOP_MESSAGE_ERROR received \n"));
            }
          return 0;
        }
      else
        {
          if (TAO_debug_level > 0)
            ACE_DEBUG ((LM_DEBUG,
                        "TAO (%P|%t) - "
                        "Message of  size zero recd. \n"));
          return -1;
        }
    }

  return 0; // success
}




int
TAO_GIOP_Message_State::parse_magic_bytes (char *buf)
{
  // The values are hard-coded to support non-ASCII platforms.
  if (!(buf [0] == 0x47      // 'G'
        && buf [1] == 0x49   // 'I'
        && buf [2] == 0x4f   // 'O'
        && buf [3] == 0x50)) // 'P'
    {
      if (TAO_debug_level > 0)
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("TAO (%P|%t) - ")
                    ACE_TEXT ("TAO_GIOP_Message_State::parse_magic_bytes")
                    ACE_TEXT ("bad header: ")
                    ACE_TEXT ("magic word [%02x,%02x,%02x,%02x]\n"),
                    buf[0],
                    buf[1],
                    buf[2],
                    buf[3]));
      return -1;
    }

 return 0;
}

int
TAO_GIOP_Message_State::get_version_info (char *buf)
{
  if (TAO_debug_level > 8)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "TAO (%P|%t) - GIOP_Message_State::get_version_info\n"));
    }

  // We have a GIOP message on hand. Get its revision numbers
  CORBA::Octet incoming_major =
    buf[TAO_GIOP_VERSION_MAJOR_OFFSET];
  CORBA::Octet incoming_minor =
    buf[TAO_GIOP_VERSION_MINOR_OFFSET];

  // Check the revision information
  if (TAO_GIOP_Message_Generator_Parser_Impl::check_revision (
          incoming_major,
          incoming_minor) == 0)
    {
      if (TAO_debug_level > 0)
        {
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("TAO (%P|%t) - bad version <%d.%d>\n"),
                      incoming_major, incoming_minor));
        }

      return -1;
    }

  // Set the version
  this->giop_version_.minor = incoming_minor;
  this->giop_version_.major = incoming_major;

  return 0;
}

int
TAO_GIOP_Message_State::get_byte_order_info (char *buf)
{
  if (TAO_debug_level > 8)
    {
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("TAO (%P|%t) - GIOP_Message_State::get_byte_order_info\n") ));
    }

    // Let us be specific that this is for 1.0
  if (this->giop_version_.minor == 0 &&
      this->giop_version_.major == 1)
    {
      this->byte_order_ =
        buf[TAO_GIOP_MESSAGE_FLAGS_OFFSET];

      if (this->byte_order_ != 0 &&
          this->byte_order_ != 1)
        {
          if (TAO_debug_level > 2)
            {
              ACE_DEBUG ((LM_DEBUG,
                          ACE_TEXT ("TAO (%P|%t) - GIOP_Message_State::get_byte_order_info, ")
                          ACE_TEXT ("invalid byte order <%d> for version <1.0>\n"),
                          this->byte_order_));
            }
          return -1;
        }
    }
  else
    {
      // Read the byte ORDER
      this->byte_order_ =
        (CORBA::Octet) (buf[TAO_GIOP_MESSAGE_FLAGS_OFFSET]& 0x01);

      // Read the fragment bit
      this->more_fragments_ =
        (CORBA::Octet) (buf[TAO_GIOP_MESSAGE_FLAGS_OFFSET]& 0x02);

      if ((buf[TAO_GIOP_MESSAGE_FLAGS_OFFSET] & ~0x3) != 0)
        {
          if (TAO_debug_level > 2)
            {
              ACE_DEBUG ((LM_DEBUG,
                          ACE_TEXT ("TAO (%P|%t) - invalid flags for <%d> ")
                          ACE_TEXT ("for version <%d %d> \n"),
                          buf[TAO_GIOP_MESSAGE_FLAGS_OFFSET],
                          this->giop_version_.major,
                          this->giop_version_.minor));
            }
          return -1;
        }
    }

  return 0;
}

void
TAO_GIOP_Message_State::get_payload_size (char *rd_ptr)
{
  // Move the read pointer
  rd_ptr += TAO_GIOP_MESSAGE_SIZE_OFFSET;

  this->message_size_ =  this->read_ulong (rd_ptr);
}

CORBA::ULong
TAO_GIOP_Message_State::read_ulong (const char *rd_ptr) const
{
  CORBA::ULong x = 0;

  // We don't need to do this sort of copy. But some compilers (read it
  // as SunCC) have a problem in deferencing from the
  // reinterpret_cast pointer of the <rd_ptr>, as the <rd_ptr> can be
  // on stack. So let us go ahead with this copying...
  char buf[] =
    {
      *rd_ptr,
      *(rd_ptr + 1),
      *(rd_ptr + 2),
      *(rd_ptr + 3)
    };

#if !defined (ACE_DISABLE_SWAP_ON_READ)
  if (!(this->byte_order_ != ACE_CDR_BYTE_ORDER))
    {
      x = *reinterpret_cast<ACE_CDR::ULong*> (buf);
    }
  else
    {
      ACE_CDR::swap_4 (buf, reinterpret_cast<char*> (&x));
    }
#else
  x = *reinterpret_cast<ACE_CDR::ULong*> (buf);
#endif /* ACE_DISABLE_SWAP_ON_READ */

  return x;
}

TAO_END_VERSIONED_NAMESPACE_DECL
