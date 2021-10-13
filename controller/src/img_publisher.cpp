#include<ros/ros.h>
#include<stdio.h>
#include<cv_bridge/cv_bridge.h>
#include<image_transport/image_transport.h>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>

int main(int argc, char **argv){
    
    ros::init(argc,argv,"img_publisher");
    ros::NodeHandle nh;
    
    image_transport::ImageTransport it(nh);
    image_transport::Publisher img_pub = it.advertise("image",10);
    
    cv::Mat img;
    cv::VideoCapture camera(0);
    if(!camera.isOpened()){
        ROS_ERROR("failed to open camera");
        return -1;
    }

    ros::Rate loop_rate(100);
    while(ros::ok()){
        camera.read(img);
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",img).toImageMsg();
        img_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}