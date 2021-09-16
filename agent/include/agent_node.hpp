#pragma once

#include <std_msgs/Int8MultiArray.h>
#include "agent.hpp"
#include "determining_input_value.hpp"

namespace aqua{

    class Agent_node:public Agent{
    public:
        Agent_node();
        ~Agent_node();


    private:
        ros::NodeHandle nh_;
        ros::Subscriber agent_sub;
        ros::Publisher agent_pub;
        
    private:
        std_msgs::Int8MultiArray motor_power_data;
    
    public:
        void generate_motor_power();
        void msg_pub();

        void debug_determining_input_value();

    private:
        void set_data(const std_msgs::Int8MultiArray::ConstPtr& data);
    };

}