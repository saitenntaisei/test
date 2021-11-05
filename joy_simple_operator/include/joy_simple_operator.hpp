#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
//#include <geometry_msgs/Twist.h>
#include <kurione_msgs/ModeCommand.h>
#include <std_msgs/Int8MultiArray.h>
#include <vector>

namespace aqua{

    class MotorOperation {  // 入力からモータ出力を計算するためのクラス
    public:
        static const int MOTOR_N = 6;
    private:
        std::vector<int> weight_each;
        std::vector<int> my_mpower;
        double weight_all;
    public:
        MotorOperation(){
            weight_each.resize(MOTOR_N);
            my_mpower.resize(MOTOR_N);
        }
        //~MotorOperation();
        void setWeights(double w_all, int w1, int w2, int w3, int w4, int w5, int w6){
            // -1<w_all<1, -100<wn<100
            weight_all = w_all;
            weight_each[0] = w1; weight_each[1] = w2; weight_each[2] = w3;
            weight_each[3] = w4; weight_each[4] = w5; weight_each[5] = w6;
        }
        void sumPower(std::vector<int>& mpower) {
            //if (mpower_ptr == nullptr) {
            //    ROS_ERROR("Null Pointer :sumPower");
            //   return;
            //}
            for (int i=0; i<MOTOR_N; i++){
                //ROS_INFO("moto : %d, tsugi : %d", mpower[i], my_mpower[i]);   // ここ２回で死ぬ
                mpower[i]+=my_mpower[i];   
            }
        }
        void calcMotorPowerAnalog(double input) {
            std::vector<int> _mpower;
            _mpower.resize(MOTOR_N);
            for (int i = 0; i<MOTOR_N; i++) {
                _mpower[i] = (int)(weight_all*weight_each[i]*input); 
            }
            my_mpower = _mpower;
            //ROS_INFO("in:%f,%d,%d,%d",input, my_mpower[0], my_mpower[1], my_mpower[2]);
            return ;
        }
        void calcMotorPowerDigital(int input) {
            std::vector<int> _mpower;
            _mpower.resize(MOTOR_N);
            for (int i = 0; i<MOTOR_N; i++) {
                _mpower[i] = (int)(weight_all*weight_each[i]*input); 
            }
            my_mpower = _mpower;
            //ROS_INFO("in:%d,%d,%d,%d",input, my_mpower[3], my_mpower[4], my_mpower[5]);
            return ;
        }
        /*
        std::vector<int> calcMotorPowerAnalog(double input) {
            std::vector<int> _mpower;
            _mpower.resize(MOTOR_N);
            for (int i = 0; i<MOTOR_N; i++) {
                _mpower[i] = (int)(weight_all*weight_each[i]*input); 
            }
            my_mpower = _mpower;
            return _mpower;
        }
        std::vector<int> calcMotorPowerDigital(int input) {
            std::vector<int> _mpower;
            _mpower.resize(MOTOR_N);
            for (int i = 0; i<MOTOR_N; i++) {
                _mpower[i] = (int)(weight_all*weight_each[i]*input); 
            }
            my_mpower = _mpower;
            return _mpower;
        }*/
    };

    class Joy_Simple_Operator{
    
    public:
        Joy_Simple_Operator();
        ~Joy_Simple_Operator();
        void convert_joy2mpower();
        void convert_joy2mode_command();
        void send_msg();
        void zeromize(std::vector<int>&, int);
        int maxAbs(std::vector<int>&, int);
        int connection_matrix[6][6]={
            {1, 0, 0, 0, 0, 0,},
            {0, -1, 0, 0, 0, 0,},
            {0, 0, 1, 0, 0, 0,},
            {0, 0, 0, 1, 0, 0,},
            {0, 0, 0, 0, -1, 0,},
            {0, 0, 0, 0, 0, 1,},
        };
    
    private:
        ros::NodeHandle nh;
        void joy_callback(const sensor_msgs::Joy::ConstPtr &joy_msg);
        //void joy_callback(const sensor_msgs::Joy& joy_msg);
        //bool is_drone_mode;
        double drone_param;    
    private:
        ros::Subscriber joy_sub;
        ros::Publisher motor_data_pub;
        ros::Publisher mode_command_pub;
        //geometry_msgs::Twist controller_msg;
        std_msgs::Int8MultiArray motor_data;
        sensor_msgs::Joy joy_data;
        //sensor_msgs::Joy& joy_data_ptr;
        kurione_msgs::ModeCommand mode_command;
        MotorOperation surge_linx, sway_liny, heave_linz, pitch_roty, yaw_rotz, set_form;
        std::vector<int> _mpower;
        //int connection_matrix;

    };

}