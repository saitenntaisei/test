#pragma once

#include <std_msgs/Int8MultiArray.h>
#include "agent.hpp"

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

    private:
        void set_data(const std_msgs::Int8MultiArray::ConstPtr& data);
    };

}