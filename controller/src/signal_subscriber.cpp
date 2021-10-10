#include "signal_subscriber.hpp"
#include "determining_input_value,hpp"

int main(int argc,char **argv){
    ros::init(argc, argv, "signal_subscriber");
    
    aqua::Signal_Subscriber signal_subscriber;

    ros::Rate loop_rate(10);
    while(ros::ok()){
        ros::spinOnce();
        ros::sleep();
    }
}

namespace aqua{
    Signal_Subscriber::Signal_Subscriber(){
        signal_sub = nh.subscribe("signal",10,&Signal_Subscriber::signal_callback,this);
        motor_data_pub = nh.advertise<std_msgs::Int8MultiArray>("/command/motor_power",10);
    }

    Signal_Subscriber::~Signal_Subscriber(){

    }

    void Signal_Subscriber::signal_callback(const geometry_msgs::Twist &msg){

    }

}
