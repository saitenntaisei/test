#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int8MultiArray.h>
#include "determining_input_value.hpp"

namespace aqua{
    class Signal_Subscriber{
    
    public:
        Signal_Subscriber();
        ~Signal_Subscriber();
        void cal_motor_input_val();
        void send_msg();

    private:
        ros::NodeHandle nh;
        void signal_callback(const geometry_msgs::Twist::ConstPtr &msg);

    private:
        ros::Subscriber signal_sub;
        ros::Publisher motor_data_pub;
        std_msgs::Int8MultiArray motor_data;
        float u[6];
        float xd[6];
    };
}