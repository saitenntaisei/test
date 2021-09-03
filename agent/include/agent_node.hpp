#pragma once

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
        void set_data(const std_msgs::Int8MultiArray::ConstPtr& data);
    };

}