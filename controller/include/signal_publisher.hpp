#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <kurione_msgs/ModeCommand.h>

namespace aqua{
    class Signal_Publisher{
    
    public:
        Signal_Publisher();
        ~Signal_Publisher();
        void convert_joy2twist();
        void convert_joy2mode_command();
        void send_msg();
    
    private:
        ros::NodeHandle nh;
        void joy_callback(const sensor_msgs::Joy::ConstPtr &joy_msg);
    
    private:
        ros::Subscriber joy_sub;
        ros::Publisher signal_pub;
        ros::Publisher mode_command_pub;
        geometry_msgs::Twist controller_msg;
        sensor_msgs::Joy joy_data;
        kurione_msgs::ModeCommand mode_command;
    };
}