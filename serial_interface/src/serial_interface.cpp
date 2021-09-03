#include "serial_interface.hpp"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "serial_interface");

    uwrai19::SerialInterface serial_if;

    ros::Rate loop_rate(100);

    while(ros::ok()) {
        serial_if.sendPacket();

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

namespace uwrai19 {

    SerialInterface::SerialInterface(){
        motor_power_sub_ = nh_.subscribe<std_msgs::Int8MultiArray>("/command/motor_power", 100, &SerialInterface::updateMotorPower, this );

        port_name_.empty();

        nh_.getParam("/serial_interface/port_name", port_name_);

        fd_ = open(port_name_.data(), O_WRONLY);

        if(fd_ < 0){
            ROS_ERROR("failed to open the port(%s): (%s)", port_name_.data(), std::strerror(errno));
            std::exit(-1);
        }

        initializePort();
        initializeData();
    }

    SerialInterface::~SerialInterface() {
        initializeData();

        for(int i = 0; i < 3; i++) {
            sendPacket();
        }

        // resets terminal-io status
        tcsetattr(fd_, TCSANOW, &tio_backup_);

        // closes the port
        close(fd_);
    }
    
    void SerialInterface::initializePort() {
        // saves the current port status
        tcgetattr(fd_, &tio_backup_);
        
        // initializes terminal-io status
        std::memset(&tio_, 0, sizeof(tio_));
        tio_.c_cc[VMIN]  = 0;
        tio_.c_cc[VTIME] = 1;
        tio_.c_cflag     = B115200 | CS8 | CLOCAL;
        tio_.c_iflag     = IGNBRK | IGNPAR;

        // clears flush of the port
        tcflush(fd_, TCIOFLUSH);

        // applies new terminal-io status
        tcsetattr(fd_, TCSANOW, &tio_);

        // lowers latency
        struct serial_struct serial_settings;
        serial_settings.flags |= ASYNC_LOW_LATENCY;
        ioctl(fd_, TIOCSSERIAL, &serial_settings);

        // displays a message
        ROS_INFO("Communication established.");

        return;
    }

    void SerialInterface::initializeData(){
        std::memset(data_.motor_power, 0, sizeof(data_.motor_power));
        std::memset(packet_, 0, sizeof(packet_));
        packet_[6] = 0x7E;
        packet_[7] = 0x7F;
        
        return ;
        
    }

    void SerialInterface::generatePacket() {
        for(int i=0; i<6; i++){
            packet_[i] = data_.motor_power[i];
        }

        packet_[6] = 0x7E;
        packet_[7] = 0x7F;  //stop byte 127

        return;
    }

    void SerialInterface::sendPacket() {
        // generates packets
        generatePacket();

        // sends packets
        int status = write(fd_, packet_, sizeof(packet_));
        
        if(status < 0) {
            ROS_ERROR("Failed to send data (%s)", std::strerror(errno));
            
            std::exit(-1);
        }

        return;
    }

    void SerialInterface::updateMotorPower(const std_msgs::Int8MultiArray::ConstPtr& motor_power_ptr){
        int num = motor_power_ptr->data.size();
        for(int i=0; i<num; i++){
            data_.motor_power[i] = motor_power_ptr->data[i];
        }
        return;
    }
        
}