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
        signal_pub = nh.advertise<geometry_msgs::Twist>("/command/robot_twist",10);
        mode_command_pub = nh.advertise<kurione_msgs::ModeCommand>("/command/mode",10);
        mode_command.is_motor_init_mode = true;
        mode_command.is_power_off_mode = false;
        joy_data.axes.resize(4);
        joy_data.buttons.resize(10);
    
    }
    
    Signal_Publisher::~Signal_Publisher(){

    }

    void Signal_Publisher::joy_callback(const sensor_msgs::Joy::ConstPtr &joy_msg){

        int num_axes = joy_msg->axes.size();
        int num_buttons = joy_msg->buttons.size();

        for(int i=0;i<num_axes;i++)joy_data.axes[i] = joy_msg->axes[i];
        for(int i=0;i<num_buttons;i++)joy_data.buttons[i] = joy_msg->buttons[i];
        convert_joy2twist();
        convert_joy2mode_command();
    }

    void Signal_Publisher::convert_joy2mode_command(){
        static int pre_joy7 = 0;
        mode_command.is_motor_init_mode = (joy_data.buttons[6]!=1);
        if ((joy_data.buttons[7]==1)&&(pre_joy7==0)) {                          // 押し込まれたら反転
            mode_command.is_power_off_mode =~ mode_command.is_power_off_mode;
        }
        pre_joy7 = joy_data.buttons[7];
    }

    void Signal_Publisher::convert_joy2twist(){
        if(joy_data.buttons[6]==1){
            controller_msg.linear.x = joy_data.axes[1];
            controller_msg.linear.y = -1*joy_data.axes[0];
            controller_msg.linear.z = (joy_data.buttons[5]-joy_data.buttons[4])*0.7;
            controller_msg.angular.y = -1*joy_data.axes[3];
            controller_msg.angular.z = joy_data.axes[2];
            controller_msg.angular.x = 0;
        }
        else{
            controller_msg.linear.x = 0;
            controller_msg.linear.y = 0;
            controller_msg.linear.z = 0;
            controller_msg.angular.y = 0;
            controller_msg.angular.z = 0;
            controller_msg.angular.x = 0;
        }
    }

    void Signal_Publisher::send_msg(){
        signal_pub.publish(controller_msg);
        mode_command_pub.publish(mode_command);
    }
    
}