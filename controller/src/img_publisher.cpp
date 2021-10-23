#include<ros/ros.h>
#include<stdio.h>
#include<cv_bridge/cv_bridge.h>
#include<image_transport/image_transport.h>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include "cv_camera/driver.h"

int main(int argc, char **argv){
    
    ros::init(argc,argv,"img_publisher");
    ros::NodeHandle private_node("~");
    cv_camera::Driver driver(private_node, private_node);
    
    image_transport::ImageTransport it(nh);
    image_transport::Publisher img_pub = it.advertise("image",10);

    try{
        driver.setup();
        while (ros::ok()){
            driver.proceed();
            ros::spinOnce();
        }
    }catch (cv_camera::DeviceError &e){
        ROS_ERROR_STREAM("cv camera open failed: " << e.what());
        return 1;
    }

    return 0;
}