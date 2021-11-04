#include<ros/ros.h>
#include<stdio.h>
#include<cv_bridge/cv_bridge.h>
#include<image_transport/image_transport.h>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>

namespace{
    cv::Mat img1, img2;
}

void imageCallback1(const sensor_msgs::ImageConstPtr& msg){
    try{
        img1 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    }
    catch(cv_bridge::Exception& e){
        ROS_ERROR("cv_bridge exception: %s",e.what());
    }
    cv::imshow("image_1",img1);
    cv::waitKey(1);
}
void imageCallback2(const sensor_msgs::ImageConstPtr& msg){
    try{
        img2 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    }
    catch(cv_bridge::Exception& e){
        ROS_ERROR("cv_bridge exception: %s",e.what());
    }
    cv::imshow("image_2",img2);
    cv::waitKey(1);
}

int main(int argc, char **argv){

    ros::init(argc, argv, "img_subscriber");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber image_sub_1 = it.subscribe("/image_1_exp",3,imageCallback1);
    image_transport::Subscriber image_sub_2 = it.subscribe("/image_2_exp",3,imageCallback2);

    ros::spin();
    return 0;
}