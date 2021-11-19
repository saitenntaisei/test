#ifndef _TOPIC_PROCESSOR_HPP_
#define _TOPIC_PROCESSOR_HPP_

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <kurione_msgs/RobotInfo.h>

namespace aqua{

    class TopicProcessor{
    
    public:
        TopicProcessor();
        ~TopicProcessor();
        bool judgeBattVoltage();
        ros::Publisher operator_msg_pub;//class
    
    private:
        ros::NodeHandle nh;//ノードにアクセスるためのもの
        ros::Subscriber robot_info_sub;//class
        const double BATT_VOLTAGE_MIN = 23.0;
        kurione_msgs::RobotInfo robot_info;
        
        void robotInfoCallback(const kurione_msgs::RobotInfo::ConstPtr&);
    };

}

#endif