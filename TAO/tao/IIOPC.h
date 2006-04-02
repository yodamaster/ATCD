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
// be\be_codegen.cpp:154

#ifndef _TAO_IDL_IIOPC_H_
#define _TAO_IDL_IIOPC_H_

#include /**/ "ace/pre.h"


#include "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/TAO_Export.h"
#include "tao/ORB.h"
#include "tao/Environment.h"
#include "tao/Sequence_T.h"
#include "tao/String_Manager_T.h"
#include "tao/Seq_Var_T.h"
#include "tao/Seq_Out_T.h"
#include "tao/VarOut_T.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO TAO_Export

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#endif /* _MSC_VER */

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// TAO_IDL - Generated from
// be\be_visitor_module/module_ch.cpp:49

namespace IIOP
{

  // TAO_IDL - Generated from
  // be\be_type.cpp:258

  struct ListenPoint;

  typedef
    TAO_Var_Var_T<
        ListenPoint
      >
    ListenPoint_var;

  typedef
    TAO_Out_T<
        ListenPoint,
        ListenPoint_var
      >
    ListenPoint_out;

  // TAO_IDL - Generated from
  // be\be_visitor_structure/structure_ch.cpp:57

  struct TAO_Export ListenPoint
  {
    typedef ListenPoint_var _var_type;

    static void _tao_any_destructor (void *);
    TAO::String_Manager host;
    CORBA::UShort port;
  };

  // TAO_IDL - Generated from
  // be\be_visitor_sequence/sequence_ch.cpp:101

#if !defined (_IIOP_LISTENPOINTLIST_CH_)
#define _IIOP_LISTENPOINTLIST_CH_

  class ListenPointList;

  typedef
    TAO_VarSeq_Var_T<
        ListenPointList
      >
    ListenPointList_var;

  typedef
    TAO_Seq_Out_T<
        ListenPointList
      >
    ListenPointList_out;

  class TAO_Export ListenPointList
    : public
        TAO::unbounded_value_sequence<
            ListenPoint
          >
  {
  public:
    ListenPointList (void);
    ListenPointList (CORBA::ULong max);
    ListenPointList (
        CORBA::ULong max,
        CORBA::ULong length,
        ListenPoint* buffer,
        CORBA::Boolean release = false
      );
    ListenPointList (const ListenPointList &);
    ~ListenPointList (void);

    static void _tao_any_destructor (void *);

    typedef ListenPointList_var _var_type;
  };

#endif /* end #if !defined */

  // TAO_IDL - Generated from
  // be\be_type.cpp:258

  struct BiDirIIOPServiceContext;

  typedef
    TAO_Var_Var_T<
        BiDirIIOPServiceContext
      >
    BiDirIIOPServiceContext_var;

  typedef
    TAO_Out_T<
        BiDirIIOPServiceContext,
        BiDirIIOPServiceContext_var
      >
    BiDirIIOPServiceContext_out;

  // TAO_IDL - Generated from
  // be\be_visitor_structure/structure_ch.cpp:57

  struct TAO_Export BiDirIIOPServiceContext
  {
    typedef BiDirIIOPServiceContext_var _var_type;

    static void _tao_any_destructor (void *);
    IIOP::ListenPointList listen_points;
  };

// TAO_IDL - Generated from
// be\be_visitor_module/module_ch.cpp:78

} // module IIOP

// TAO_IDL - Generated from
// be\be_visitor_traits.cpp:61

// Traits specializations.
namespace TAO
{
}

// TAO_IDL - Generated from
// be\be_visitor_structure/cdr_op_ch.cpp:54

TAO_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const IIOP::ListenPoint &);
TAO_Export CORBA::Boolean operator>> (TAO_InputCDR &, IIOP::ListenPoint &);

// TAO_IDL - Generated from
// be\be_visitor_sequence/cdr_op_ch.cpp:71

#if !defined _TAO_CDR_OP_IIOP_ListenPointList_H_
#define _TAO_CDR_OP_IIOP_ListenPointList_H_

TAO_Export CORBA::Boolean operator<< (
    TAO_OutputCDR &,
    const IIOP::ListenPointList &
  );
TAO_Export CORBA::Boolean operator>> (
    TAO_InputCDR &,
    IIOP::ListenPointList &
  );

#endif /* _TAO_CDR_OP_IIOP_ListenPointList_H_ */

// TAO_IDL - Generated from
// be\be_visitor_structure/cdr_op_ch.cpp:54

TAO_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const IIOP::BiDirIIOPServiceContext &);
TAO_Export CORBA::Boolean operator>> (TAO_InputCDR &, IIOP::BiDirIIOPServiceContext &);

// TAO_IDL - Generated from
// be\be_codegen.cpp:1062

TAO_END_VERSIONED_NAMESPACE_DECL

#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */

#include /**/ "ace/post.h"

#endif /* ifndef */


