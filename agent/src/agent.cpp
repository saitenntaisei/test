#include "agent_node.hpp"

namespace clione_gm = clione_gradient_method;

namespace aqua{

    Agent::Agent(){
        
    }

    Agent::~Agent(){

    }

    // debug determining_input_value.hpp
    void Agent::debug_determining_input_value(){
        float q[6] = {0,0,0,0,0,0};
        clione_gm::debug(q);
    }

}