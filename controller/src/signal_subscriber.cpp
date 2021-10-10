#include "signal_subscriber.hpp"

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
        signal_sub = nh.subscribe("/command/motor_power",10,&Signal_Subscriber::signal_callback,this);
        motor_data_pub = nh.advertise<std_msgs::Int8MultiArray>("/command/motor_power",10);

        motor_data.data.resize(8);
        memset(motor_data.data,0,sizeof(motor_data.data));
    }

    Signal_Subscriber::~Signal_Subscriber(){

    }

    void Signal_Subscriber::signal_callback(const geometry_msgs::TwistPtr &msg){
        int num = msg->data.size();
        for(int i=0;i<num;i++){
            xd[i] = msg->data[i];
        }
    }

    void Signal_Subscriber::send_msg(){
        motor_data_pub.publish(motor_data);
    }

    void Signal_Subscriber::cal_motor_input_val(){
        clione_gradient_method::determining_input_value(u,xd);
        for(int i=0;i<6;i++){
            motor_data.data[i] = (int)(u[i]*100);
        }
        send_msg();
    }
}
