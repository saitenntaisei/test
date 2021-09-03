#ifndef _UWRAI19_SERIAL_INTERFACE_
#define _UWRAI19_SERIAL_INTERFACE_

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


#include "packet.hpp"

namespace uwrai19 {
    class SerialInterface {
    private:
        ros::NodeHandle nh_;
        // node handle
        ros::Subscriber motor_power_sub_;
        //subscribers

        std::string port_name_;

        int fd_;
        
        struct termios tio_;
        struct termios tio_backup_;

        struct PacketData data_;

        unsigned char packet_[8];
        //a packet sent in USB_UART

        void initializePort();
        void initializeData();
        void generatePacket();

    public:
        SerialInterface();
        ~SerialInterface();

        void sendPacket();

        void updateMotorPower(const std_msgs::Int8MultiArray::ConstPtr&);
        
    };
}

#endif
