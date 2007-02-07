//$Id$
//
// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    remote_proxy_broker_ch.h
//
// = DESCRIPTION
//     Concrete visitor for the Interface node. This
//     visitor generates the declaration for the remote
//     ProxyBroker class.
//
// = AUTHOR
//     Angelo Corsaro <corsaro@cs.wustl.edu>
//
// ============================================================================

#ifndef BE_REMOTE_PROXY_BROKER_CH_H_
#define BE_REMOTE_PROXY_BROKER_CH_H_

class be_visitor_interface_remote_proxy_broker_ch : public be_visitor_interface
{
  // = TITLE
  //   Generates the declaration for the base proxy
  //   broker class.

public:
  // -- Ctor/Dtor Decl. --
  be_visitor_interface_remote_proxy_broker_ch (be_visitor_context *ctx);

  virtual ~be_visitor_interface_remote_proxy_broker_ch (void);

  virtual int visit_interface (be_interface *node);
  // visit an interface

  virtual int visit_component (be_component *node);
  // This will just call the above method - no need to create
  // another set of visitors for this stuff.
};

#endif /* BE_REMOTE_PROXY_BROKER_CH_H_ */
