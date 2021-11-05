#ifndef _KURIONE_NUCLEO_DRIVER_
#define _KURIONE_NUCLEO_DRIVER_

#include "communication.hpp"
#include "packet.hpp"
#include <kurione_msgs/ModeCommand.h>
#include <kurione_msgs/RobotInfo.h>

namespace kurione {

    struct PacketMainDriverData
    {
        int8_t info[6];  // 初期データを
    };

    class Motor {
        private:
            int input_range;   // 入力range
            int input_mid;   // 入力０点
            int duty_range;
            int duty_mid;
            int duty_init;
            int sign;           // 極性(+1 or -1）
            int u;
        public:
            void setInputRange(int m){input_range = m;}
            void setInputMid(int m){input_mid = m;}
            void setDutyRange(int m){duty_range = m;}
            void setDutyMid(int m){duty_mid = m;}
            void setDutyInit(int i){duty_init = i;}
            void setSign(int s = 1){sign = s;}
            void setInputConfigs(int mid, int range){
                setInputMid(mid);
                setInputRange(range);
            }
            void setDutyConfigs(int mid, int range, int init){
                setDutyMid(mid);
                setDutyRange(range);
                setDutyInit(init);
            }
            int inputToDuty(int input){
                if((input<=input_mid+input_range)&&(input>=input_mid-input_range)){   // 
                    u = (int)(((double)(input-input_mid)/input_range)*duty_range*sign+duty_mid);
                }else{
                    u = duty_init;
                }
                return u;
            }
            int initialize(void) {
                u = duty_init;
                return u;
            }
    };

    class NucleoDriver {
        private:
            ros::NodeHandle nh_;
            // node handle
            ros::Subscriber info_sub_;
            ros::Subscriber command_sub_;
            // Subscribers
            //ros::Publisher info_pub_;
            ros::Publisher roboinfo_pub_;
            // Publishers
            struct PacketMainDriverData data_;

            std_msgs::Int8MultiArray receive_data;

            void generatePacket();
            void initializeData(); // over ride
            Motor* motors_ptr;

        public:
            Communication* communication_ptr;
            NucleoDriver(Communication*, Motor*);
            ~NucleoDriver();
            kurione_msgs::ModeCommand mode_command;
            kurione_msgs::RobotInfo robot_info;

            void updateInfo(const std_msgs::Int8MultiArray::ConstPtr&);
            void updateModeCommand(const kurione_msgs::ModeCommand::ConstPtr&);
            void publishRobotInfo();
            void calcMotorsDuty();
            void updateCommunication(void);
            void initMotors();

            static const int MOTOR_NUM = 6;    // モータ数
            static const int WDT_MAX = 5;   // wdtのカウンタ初期値（s）
            int operation_command;
            int voltage_int;        // バッテリー電圧整数値
            int current_int;        // バッテリー電流整数値
            int power_supply;       // 強電供給状態
            int u[MOTOR_NUM];           // モータへのデューティ入力
            int motors_input_min[MOTOR_NUM];
            int motors_input_mid[MOTOR_NUM];
            int motors_input_max[MOTOR_NUM];
            int motors_duty_min[MOTOR_NUM];
            int motors_duty_mid[MOTOR_NUM];
            int motors_duty_max[MOTOR_NUM];
            int motors_sign[MOTOR_NUM];
            int wdt_count;

            unsigned char r_packet_[8];
            // packets read in USB_UART
    };

    

}

#endif