#ifndef _KURIONE_SERIAL_INTERFACE_
#define _KURIONE_SERIAL_INTERFACE_

#include<string>
#include<cmath>
#include<cstdlib>
#include<cerrno>

#include<fcntl.h>
#include<termios.h>
#include<unistd.h>
#include<linux/serial.h>
#include<sys/ioctl.h>

#include<ros/ros.h>
#include<std_msgs/Int8MultiArray.h>


#include"packet.hpp"

namespace kurione {
    class SerialInterface {
    private:
        ros::NodeHandle nh_;
        // node handle

        std::string port_name_;

        int fd_;
        int read_req_size = 2;      // 未使用
        int read_size;
        
        struct termios tio_;
        struct termios tio_backup_;

        //struct PacketData data_;

        //unsigned char packet_[8];   // 未使用
        // packets sent in USB_UART
        //unsigned char r_packet_[8]; // 未使用
        // packets read in USB_UART
        

        
        //void initializeData();  // 未使用
        //void generatePacket();  // 未使用

    public:
        SerialInterface();
        ~SerialInterface();
        void initializePort();
        //void sendPacket();  // 未使用
        //void readPacket();  // 未使用

        void setPortName(std::string);

        // 以下nucleo代用
        int freshReadBuffer();
        void putc(unsigned char);   //１文字送信
        bool readable();            // 読み取り可？
        int readable_size();
        unsigned char getc();       // １文字受信

        //void updateDataToUSB(const std_msgs::Int8MultiArray::ConstPtr&);    // 多分未使用
        // when subscribe data from ROS node, update data sent to USB module.

    };
}

#endif