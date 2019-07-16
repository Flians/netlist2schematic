#pragma once

namespace vp
{
    enum NodeType {
        NORMAL, // a normal node is created from a node of the original graph.
        NODE_BIG, // a dummy node originating from a node spanning multiple layers.
        DUMMY_EDGE, // a dummy node created to split a long edge.
        DUMMY_PORT_EXTERNAL, // a node representing an external port.
        DUMMY_PORT_NS, // a dummy node created to cope with ports at the northern or southern side.
        DUMMY_LABEL // a dummy node to represent a mid-label on an edge.
    };
}
