#pragma once


#include"kalman_filter.hpp"

namespace aqua{
    class KF_node:public KF{
    public:
        KF_node();    
        ~KF_node();

    private:
        ros::NodeHandle nh;
        ros::Publisher kf_pub;
        ros::Subscriber kf_motor_sub;
    
    private:
        std_msgs::Int8MultiArray motor_power_data;

    public:
        void msg_pub();

    private:
        void return_motor_data(const std_msgs::Int8MultiArray::ConstPtr& data);
    };
}