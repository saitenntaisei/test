#include "agent_node.hpp"

namespace clione_gm = clione_gradient_method;

namespace aqua{

    Agent::Agent(){
        
    }

    Agent::~Agent(){

    }

    // debug determining_input_value.hpp
    void Agent::debug_determining_input_value(){
        //float q[6] = {1.f/3.f,1.f/4.f,1.f/5.f,1.f,2.f,3.f};
        float u[6];
        float x_d[6] = {0.2,0.4,0.5,0.1,0.1,0.1};
        clione_gm::determining_input_value(u,x_d);
        
        for(int i=0;i<6;i++)std::cout << u[i] << std::endl;
        
        //clione_gm::debug(q);
    }

}