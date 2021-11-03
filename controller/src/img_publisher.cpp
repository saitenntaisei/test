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
    image_transport::Publisher img_pub_1 = it.advertise("image_1_raw",10);
    image_transport::Publisher img_pub_2 = it.advertise("image_2_raw",10);
    cv::Mat img_1, img_2;

    int camera_1_id = 0;
    int camera_2_id = 2;
    double fps = 15.0;
    double width = 32.0;
    double height = 32.0;

    cv::VideoCapture camera_1(camera_1_id);
    cv::VideoCapture camera_2(camera_2_id);
/*
    bool ret = camera_1.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H','2','6','4'));
    if(!ret){
        ROS_ERROR("codec setting missed");
    }else{
	ROS_INFO("codec setting succeed!");
    }
*/
    if(!camera_1.isOpened()){
        ROS_ERROR("failed to open camera1 : %d", camera_1_id);
        return -1;
    }
    if(!camera_2.isOpened()){
        ROS_ERROR("failed to open camera2 : %d", camera_2_id);
        return -1;
    }
    if (!camera_1.set(cv::CAP_PROP_FPS, fps)){
        ROS_ERROR("camera1 set fps error");
        return -1;
    }
    if (!camera_2.set(cv::CAP_PROP_FPS, fps)){
        ROS_ERROR("camera2 set fps error");
        return -1;
    }
    ROS_INFO("camera1: width : %d, height : %d", (int)camera_1.get(cv::CAP_PROP_FRAME_WIDTH), (int)camera_1.get(cv::CAP_PROP_FRAME_HEIGHT));
    ROS_INFO("camera2: width : %d, height : %d", (int)camera_2.get(cv::CAP_PROP_FRAME_WIDTH), (int)camera_2.get(cv::CAP_PROP_FRAME_HEIGHT));
    /*
    if (!camera_1.set(cv::CAP_PROP_FRAME_WIDTH, width)){
        ROS_ERROR("camera set width error");
        return -1;
    }
    if (!camera_1.set(cv::CAP_PROP_FRAME_HEIGHT, height)){
        ROS_ERROR("camera set height error");
        return -1;
    }
    */
    ros::Rate loop_rate(30);
    while(ros::ok()){
        camera_1.read(img_1);
        sensor_msgs::ImagePtr msg1 = cv_bridge::CvImage(std_msgs::Header(),"bgr8",img_1).toImageMsg();
        img_pub_1.publish(msg1);
        camera_2.read(img_2);
        sensor_msgs::ImagePtr msg2 = cv_bridge::CvImage(std_msgs::Header(),"bgr8",img_2).toImageMsg();
        img_pub_2.publish(msg2);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
