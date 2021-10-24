#include "nucleo_driver.hpp"

// TODO : エラー解決
// TODO : 入ってきた入力値をデューティーに変換
// TODO : 返り電圧値を適切な型でパブリッシュ

int main(int argc, char* argv[]) {
    
    ros::init(argc, argv, "nucleo_driver");

    kurione::Motor motors[6];
    kurione::SerialInterface serial;

    kurione::Communication communication(&serial);
    kurione::NucleoDriver nucleo(&communication, motors);

    ros::Rate loop_rate(100);
    int t = 0;

    while(ros::ok()) {
        
        nucleo.communication_ptr->receive();
        nucleo.updateCommunication();
        t++;
        if(t>=100) {
            t = 0;
            if (nucleo.operation_command == 0) {    // 特に大事な命令はない
                nucleo.calcMotorsDuty();
                nucleo.communication_ptr->send_command_dat = kurione::Command::SIGNAL_LAND_TO_MAIN;  // 入力命令
                for(int i=0; i<nucleo.MOTOR_NUM; i++){
                    nucleo.communication_ptr->send_num_dat.push(nucleo.u[i]);
                }
                ROS_INFO("u : %d,%d,%d,%d,%d,%d",nucleo.u[0],nucleo.u[1],nucleo.u[2],nucleo.u[3],nucleo.u[4],nucleo.u[5]);
            }else{
                nucleo.communication_ptr->send_command_dat = nucleo.operation_command; // 大事な命令を送信
                nucleo.operation_command = 0;
            }
            nucleo.communication_ptr->encode();
            nucleo.communication_ptr->sendDat();
        }
        //nucleo.sendPacket();
        //nucleo.publishData();
        ros::spinOnce();
        loop_rate.sleep();
        
    }

    return 0;
}

namespace kurione {
    NucleoDriver::NucleoDriver(Communication* cp, Motor* mp){
        communication_ptr = cp;
        motors_ptr = mp;

        info_sub_ = nh_.subscribe<std_msgs::Int8MultiArray>("/serial_data/to_maindriver", 100, &NucleoDriver::updateInfo, this);
        info_pub_ = nh_.advertise<std_msgs::Int8MultiArray>("/serial_data/from_maindriver", 100);

        std::string port_name_;
        port_name_.empty();
        nh_.getParam("/nucleo_driver/port_name", port_name_);
        communication_ptr->serial_ptr->setPortName(port_name_);
        //receive_data.data.resize(2);
        communication_ptr->serial_ptr->initializePort();
        initMotors();

        operation_command = 0;

        communication_ptr->init(Communication::ROLL_LAND);
    }

    NucleoDriver::~NucleoDriver(){

    }

    /* rs485まわり */
    void NucleoDriver::updateCommunication(void) {
        if (communication_ptr->flag_rdat_check){
            communication_ptr->decode();
            communication_ptr->flag_rdat_check = false;
            switch (communication_ptr->receive_command_dat){
                case Command::SIGNAL_BATT_TO_LAND:
                    voltage_int = communication_ptr->receive_num_dat.front();
                    communication_ptr->receive_num_dat.pop();
                    current_int = communication_ptr->receive_num_dat.front();
                    communication_ptr->receive_num_dat.pop();
                    power_supply = communication_ptr->receive_num_dat.front();
                    communication_ptr->receive_num_dat.pop();
                    // pc.printf("BATT:%2.1f V,%2.1f A, POWER:%2d\n", (float)(voltage_int)/10.0f, (float)(current_int)/10.0f, power_supply);
                    ROS_INFO("BATT:%2.1f V,%2.1f A, POWER:%2d\n", (float)(voltage_int)/10.0f, (float)(current_int)/10.0f, power_supply);
                    break;
                default:
                    break;
            }
        }
    }

    void NucleoDriver::initMotors() {   // モータの設定はここ
        /**** BLDC ******/
        // migimae
        motors_ptr[0].setInputConfigs(0,100);  // mid, range
        motors_ptr[0].setDutyConfigs(1480,200,100);   // mid, range, init
        motors_ptr[0].setSign(1);
        // hidarimae
        motors_ptr[1].setInputConfigs(0,100);  // mid, range
        motors_ptr[1].setDutyConfigs(1480,200,100);   // mid, range, init
        motors_ptr[1].setSign(-1);
        // ushiro
        motors_ptr[2].setInputConfigs(0,100);  // mid, range
        motors_ptr[2].setDutyConfigs(1480,200,100);   // mid, range, init
        motors_ptr[2].setSign(1);
        /**** Servo *****/
        // migimae
        motors_ptr[3].setInputConfigs(0,100);  // mid, range
        motors_ptr[3].setDutyConfigs(1500,950,100);   // mid, range, init
        motors_ptr[3].setSign(1);
        // hidarimae
        motors_ptr[4].setInputConfigs(0,100);  // mid, range
        motors_ptr[4].setDutyConfigs(1500,950,100);   // mid, range, init
        motors_ptr[4].setSign(-1);
        // ushiro
        motors_ptr[5].setInputConfigs(0,100);  // mid, range
        motors_ptr[5].setDutyConfigs(1500,950,100);   // mid, range, init
        motors_ptr[5].setSign(1);

        for (int i = 0; i<MOTOR_NUM; i++){
            u[i] = motors_ptr[i].initialize();
        }
    }

    void NucleoDriver::updateInfo(const std_msgs::Int8MultiArray::ConstPtr& info_ptr) { // topic受信
        int num = info_ptr->data.size();
        if (num!=MOTOR_NUM){
            ROS_ERROR("mismatch the input size = %d", num);
        }
        for(int i=0; i<num; i++){
            data_.info[i] = info_ptr->data[i];
        }
        return;
    }

    void NucleoDriver::calcMotorsDuty() {   // 入力値からデューティーを計算
        for(int i=0; i<MOTOR_NUM; i++){
            u[i] = motors_ptr[i].inputToDuty(data_.info[i]);
        }
        return;
    }

    void NucleoDriver::publishData() {
        
        receive_data.data[0] = r_packet_[0];
        receive_data.data[1] = r_packet_[1];

        info_pub_.publish(receive_data);
        return;

    }
        

}