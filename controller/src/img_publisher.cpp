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

    int camera_id = 0;
    double fps = 5.0;
    double width = 32.0;
    double height = 32.0;

    cv::VideoCapture camera(camera_id);
//    bool ret = camera.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H','2','6','4'));
//    if(!ret){
//        ROS_ERROR("codec setting missed");
//    }else{
//	ROS_INFO("codec setting succeed!");
//    }

    if(!camera.isOpened()){
        ROS_ERROR("failed to open camera : %d", camera_id);
        return -1;
    }
    if (!camera.set(cv::CAP_PROP_FPS, fps)){
        ROS_ERROR("camera set fps error");
        return -1;
    }
    ROS_INFO("width : %d, height : %d", (int)camera.get(cv::CAP_PROP_FRAME_WIDTH), (int)camera.get(cv::CAP_PROP_FRAME_HEIGHT));
    
    if (!camera.set(cv::CAP_PROP_FRAME_WIDTH, width)){
        ROS_ERROR("camera set width error");
        return -1;
    }
    if (!camera.set(cv::CAP_PROP_FRAME_HEIGHT, height)){
        ROS_ERROR("camera set height error");
        return -1;
    }

    ros::Rate loop_rate(30);
    while(ros::ok()){
        camera.read(img);
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",img).toImageMsg();
        img_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
