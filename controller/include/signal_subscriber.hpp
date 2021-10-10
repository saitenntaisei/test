#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int8MultiArray.h>

namespace aqua{
    class Signal_Subscriber{
    
    public:
        Signal_Subscriber();
        ~Signal_Subscriber();

    private:
        ros::NodeHandle nh;
        void signal_callback(const geometry_msgs::Twist &msg);

    private:
        ros::Subscriber signal_sub;
        ros::Publisher motor_data_pub;
    };
}