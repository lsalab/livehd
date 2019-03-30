//  This file is distributed under the BSD 3-Clause License. See LICENSE for details.
#pragma once

#include <vector>

#include "node_pin.hpp"

using XEdge_iterator = std::vector<XEdge>;

class LGraph;
class Node_Type;

class Node {
private:
  const Index_ID nid;
  const Hierarchy_id hid;
  LGraph *g;

protected:
  friend LGraph;
  friend Node_pin;
  friend XEdge;

  Index_ID get_nid() const { return nid; }

  Node(LGraph *_g, Hierarchy_id _hid, Index_ID _nid)
    :nid(_nid)
    ,hid(_hid)
    ,g(_g) {
      I(nid);
      I(g);
    };
public:
  struct __attribute__((packed)) Compact {
    const uint32_t nid  : Index_bits;

    constexpr size_t operator()(const Compact &obj) const { return obj.nid; }
    constexpr operator size_t() const { return nid; }

    Compact(const Index_ID &_nid) :nid(_nid) { I(nid); };
    Compact(size_t raw) :nid((uint32_t)raw) { };
    Compact() :nid(0) { };
    Compact &operator=(const Compact &obj) {
      I(this != &obj);
      *((uint32_t *)this)  = *((uint32_t *)&obj); // NASTY, but how else to preserve the const???

      I(nid  == obj.nid);

      return *this;
    };
  };
  Node()
    :nid(0)
    ,hid(0)
    ,g(0) {
  };
  Node(LGraph *_g, Hierarchy_id _hid, Compact comp)
    :nid(comp.nid)
    ,hid(_hid)
    ,g(_g) {
      I(nid);
      I(g);
  };

  inline Compact get_compact() const {
    return Compact(nid);
  }

  LGraph *get_lgraph() const { return g; }
  Hierarchy_id  get_hid()    const { return hid; }

  Node_pin get_driver_pin() const;
  Node_pin get_driver_pin(Port_ID pid) const;
  Node_pin get_sink_pin(Port_ID pid) const;
  Node_pin get_sink_pin() const;

  bool has_inputs () const;
  bool has_outputs() const;

  bool is_root() const;

  const Node_Type &get_type() const;
  void set_type(const Node_Type_Op op);

  void set_type_subgraph(Lg_type_id subid);
  Lg_type_id get_type_subgraph() const;


  Node_pin setup_driver_pin(std::string_view name);
  Node_pin setup_driver_pin(Port_ID pid);
  Node_pin setup_driver_pin() const;

  Node_pin setup_sink_pin(std::string_view name);
  Node_pin setup_sink_pin(Port_ID pid);
  Node_pin setup_sink_pin() const;

  XEdge_iterator inp_edges() const;
  XEdge_iterator out_edges() const;

  void del_node();

  // BEGIN ATTRIBUTE ACCESSORS
  void set_name(std::string_view iname);
  std::string_view get_name() const;
  bool has_name() const;

  // END ATTRIBUTE ACCESSORS
};