#include "signal_publisher.hpp"

int main(int argc, char** argv){
    ros::init(argc, argv, "signal_publisher");

    aqua::Signal_Publisher signal_publisher;

    ros::Rate loop_rate(10);
    while(ros::ok()){
        signal_publisher.send_msg();
        ros::spinOnce();
        loop_rate.sleep();
    }
}

namespace aqua{
    Signal_Publisher::Signal_Publisher(){
        joy_sub = nh.subscribe("joy",10,&Signal_Publisher::joy_callback,this);
        signal_pub = nh.advertise<geometry_msgs::Twist>("signal",10);
    
    }
    
    Signal_Publisher::~Signal_Publisher(){

    }

    void Signal_Publisher::joy_callback(const sensor_msgs::Joy::ConstPtr &joy_msg){
        ROS_ERROR("catch!%f",joy_msg->axes[0]);
    }

    void Signal_Publisher::send_msg(){
        
    }
    
}