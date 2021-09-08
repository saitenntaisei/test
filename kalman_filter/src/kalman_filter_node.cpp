#include "kalman_filter_node.hpp"

int main(int argc, char** argv){

    ros::init(argc,argv,"kalman_filter_node");
    aqua::KF_node KF;

    ros::Rate looprate(10);
    while(ros::ok()){

        ros::spinOnce();
        looprate.sleep();
    }
    return 0;
}

namespace aqua{
    KF_node::KF_node(){
        kf_pub = nh.advertise<std_msgs::Int8MultiArray>("/status/est",100);
        kf_motor_sub = nh.subscribe<std_msgs::Int8MultiArray>("/commnad/motor_power",100,&KF_node::return_motor_data,this);
    }
    KF_node::~KF_node(){

    }

    void KF_node::msg_pub(){

    }

    void KF_node::return_motor_data(const std_msgs::Int8MultiArray::ConstPtr& data){
        int num = data->data.size();
        for(int i=0;i<num;i++){
            motor_power_data.data[i] = data->data[i];
        }
    }
}