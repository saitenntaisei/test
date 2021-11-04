#include<ros/ros.h>
#include<stdio.h>
#include<cv_bridge/cv_bridge.h>
#include<image_transport/image_transport.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgcodecs/imgcodecs.hpp>

namespace{
    cv::Mat img, img_proc, img_bin;
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg){
    try{
        img = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    }
    catch(cv_bridge::Exception& e){
        ROS_ERROR("cv_bridge exception: %s",e.what());
    }
    cv::imshow("image",img);
    namedWindow( "image2", cv::WINDOW_AUTOSIZE );
    img_proc = img;
    cv::cvtColor(img, img_proc, cv::COLOR_BGR2GRAY);    // グレスケに変換
    //cv::cvtColor(img, img_proc, cv::COLOR_BGR2);
    //cv::inRange(img, cv::Scalar(175,0,0), cv::Scalar(185, 255, 255), img_proc);
    cv::threshold(img_proc, img_bin, 100,255,cv::THRESH_BINARY);
    std::vector<std::string> decode_info;
    
    cv::imshow("image2",img_proc);
    
    cv::waitKey(1);
    return;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "qr_reader");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber image_sub = it.subscribe("/image",3,imageCallback);
    ros::spin();
    return 0;
}