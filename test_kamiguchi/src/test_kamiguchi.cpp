#include "../include/test_kamiguchi.hpp"

int main(int argc, char** argv){
    /*************************moderated************/
    ros::init(argc, argv, "test_kamiguchi");

    aqua::TopicProcessor topic_processor;
    std_msgs::String msg;
/*************************moderated************/
    ros::Rate loop_rate(10);//ループ周期
    while(ros::ok()){
        ROS_INFO("Hello");
        if(topic_processor.judgeBattVoltage()) {
            msg.data = "work";
        }else{
            msg.data = "stop";
        }
        topic_processor.operator_msg_pub.publish(msg);
        /*************************moderated************/
        ros::spinOnce();//実行反映
        loop_rate.sleep();//9行目での10Hz待機
        /************************************************/
    }
    return 0;
}

namespace aqua{
    TopicProcessor::TopicProcessor(){
        robot_info_sub = nh.subscribe("/robot_info",10,&TopicProcessor::robotInfoCallback/*割り込み*/,this);
        operator_msg_pub = nh.advertise<std_msgs::String>("/operation/msg",10);
        robot_info.batt_voltage = 0.0;
    }
    
    TopicProcessor::~TopicProcessor(){
    }

    void TopicProcessor::robotInfoCallback(const kurione_msgs::RobotInfo::ConstPtr &info){ 
        robot_info.batt_voltage = info->batt_voltage;
    }

    bool TopicProcessor::judgeBattVoltage() {
        return robot_info.batt_voltage>BATT_VOLTAGE_MIN;
    }
}