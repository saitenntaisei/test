#include "serial_interface.hpp"



namespace kurione {

    SerialInterface::SerialInterface(){
        //motor_power_sub_ = nh_.subscribe<std_msgs::Int8MultiArray>("/command/motor_power", 100, &SerialInterface::updateDataToUSB, this );

        //port_name_.empty();

        //nh_.getParam("/serial_interface/port_name", port_name_);

        //initializePort();
        //initializeData();
    }

    SerialInterface::~SerialInterface() {
        //initializeData();

        for(int i = 0; i < 3; i++) {
            //sendPacket();
        }

        // resets terminal-io status
        tcsetattr(fd_, TCSANOW, &tio_backup_);

        // closes the port
        close(fd_);
    }
    
    void SerialInterface::initializePort() {
        fd_ = open(port_name_.data(), O_WRONLY);

        if(fd_ < 0){
            ROS_ERROR("failed to open the port(%s): (%s)", port_name_.data(), std::strerror(errno));
            std::exit(-1);
        }
        
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
/*
    void SerialInterface::initializeData(){
        std::memset(data_.motor_power, 0, sizeof(data_.motor_power));
        std::memset(packet_, 0, sizeof(packet_));
        packet_[6] = 0xFF;
        packet_[7] = 0xFF;
        
        return ;
        
    }
*/
/*
    void SerialInterface::generatePacket() {
        data_.motor_power[0] *= -1;
        data_.motor_power[1] *= -1;
        data_.motor_power[2] *= -1;
        //data_.motor_power[3] *= -1;
        data_.motor_power[4] *= -1;
        data_.motor_power[5] *= -1;
        for(int i=0; i<6; i++){
            packet_[i] = data_.motor_power[i];
        }
        //packet_[0] *= -1;
        //packet_[1] *= -1;
        //packet_[2] *= -1;
        //packet_[3] *= -1;
        //packet_[4] = 10;
        //packet_[5] *= -1;
        packet_[6] = 0xFF;
        packet_[7] = 0x88;  //stop byte -120

        return;
    }
*/
/*
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

    void SerialInterface::readPacket() {
        int available_size = 0;
        ioctl(fd_, FIONREAD, &available_size);

        if(read_req_size > available_size) {
            read_size = read(fd_, r_packet_, available_size);
        } else {
            read_size = read(fd_, r_packet_, read_req_size);
        }
    }
*/
    void SerialInterface::setPortName(std::string name){
        port_name_ = name;
        return;
    }

    void SerialInterface::putc(unsigned char dat) {
        // sends packets
        int status = write(fd_, &dat, 1);

        if(status < 0) {
            ROS_ERROR("Failed to send data (%s)", std::strerror(errno));
            
            std::exit(-1);
        }

        return;
    }

    bool SerialInterface::readable() {
        int available_size = 0;
        ioctl(fd_, FIONREAD, &available_size);
        return available_size>0;
    }

    unsigned char SerialInterface::getc() {
        unsigned char ret = 0;
        int available_size = 0;
        ioctl(fd_, FIONREAD, &available_size);
        if (available_size>0){
            read(fd_, &ret, 1);
        }
    }
/*
    void SerialInterface::updateDataToUSB(const std_msgs::Int8MultiArray::ConstPtr& motor_power_ptr){
        int num = motor_power_ptr->data.size();
        for(int i=0; i<num; i++){
            data_.motor_power[i] = motor_power_ptr->data[i];
        }
        return;
    }*/
}
