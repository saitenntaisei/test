#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>

namespace aqua{
    class Signal_Publisher{
    
    public:
        Signal_Publisher();
        ~Signal_Publisher();
        void send_msg();
    
    private:
        ros::NodeHandle nh;
        void joy_callback(const sensor_msgs::Joy::ConstPtr &joy_msg);
    
    private:
        ros::Subscriber joy_sub;
        ros::Publisher signal_pub;
        geometry_msgs::Twist controller_msg;
    };
}