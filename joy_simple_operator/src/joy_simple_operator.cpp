#include "joy_simple_operator.hpp"

int main(int argc, char** argv){
    ros::init(argc, argv, "joy_simple_operator");

    aqua::Joy_Simple_Operator joy_simple_operator;

    ros::Rate loop_rate(10);
    while(ros::ok()){
        joy_simple_operator.convert_joy2mode_command();
        joy_simple_operator.convert_joy2mpower();
        joy_simple_operator.send_msg();
        ros::spinOnce();
        //ros::spin();
        loop_rate.sleep();
    }
    return 0;
}

namespace aqua{
    Joy_Simple_Operator::Joy_Simple_Operator(){
        joy_sub = nh.subscribe("joy",10,&Joy_Simple_Operator::joy_callback,this);
        motor_data_pub = nh.advertise<std_msgs::Int8MultiArray>("/command/motor_power",10);
        mode_command_pub = nh.advertise<kurione_msgs::ModeCommand>("/command/mode",10);
        mode_command.is_motor_init_mode = true;
        mode_command.is_power_off_mode = false;
        is_drone_mode = false;
        joy_data.axes.resize(4);
        joy_data.buttons.resize(10);
        motor_data.data.resize(MotorOperation::MOTOR_N);
        _mpower.resize(MotorOperation::MOTOR_N);

        surge_linx.setWeights(1.0, 100, 100, 0, 0, 0, 0);
        sway_liny.setWeights(1.0, -80, 80, -80, 0, 0, 0);
        heave_linz.setWeights(1.0, 30, -30, 30, 0, 0, 0);
        pitch_roty.setWeights(1.0, 30, -30, -30, 0, 0, 0);
        yaw_rotz.setWeights(1.0, 50, -50, -50, 0, 0, 0);

        set_form.setWeights(1.0, 0, 0, 0, 100, -100, 100);   
    }
    
    Joy_Simple_Operator::~Joy_Simple_Operator(){

    }

    //void Joy_Simple_Operator::joy_callback(const sensor_msgs::Joy::ConstPtr &joy_msg){ 
    void Joy_Simple_Operator::joy_callback(const sensor_msgs::Joy& joy_msg){
        //if (joy_msg == nullptr) {
        //    ROS_ERROR("Null Pointer :joy_callback");
        //    return;
        //}
        /*
        int num_axes = joy_msg->axes.size();
        int num_buttons = joy_msg->buttons.size();
        
        for(int i=0;i<num_axes;i++)joy_data.axes[i] = joy_msg->axes[i];
        for(int i=0;i<num_buttons;i++)joy_data.buttons[i] = joy_msg->buttons[i];
        */
        //joy_data_ptr = joy_msg;
        //joy_data.axes = joy_msg->axes;
        //joy_data.buttons = joy_msg->buttons;
    }

    void Joy_Simple_Operator::convert_joy2mode_command(){
        static int pre_joy7 = 0;
        static int pre_joy0 = 0;
        static int pre_joy1 = 0;
        mode_command.is_motor_init_mode = (joy_data.buttons[6]!=1);
        if ((joy_data.buttons[7]==1)&&(pre_joy7==0)) {                          // 押し込まれたら反転
            mode_command.is_power_off_mode =~ mode_command.is_power_off_mode;
        }
        if ((joy_data.buttons[0]==1)&&(pre_joy0==0)) {
            is_drone_mode = 1;
        }
        if ((joy_data.buttons[1]==1)&&(pre_joy1==0)) {
            is_drone_mode = 0;
        }
        pre_joy0 = joy_data.buttons[0];
        pre_joy1 = joy_data.buttons[1];
        pre_joy7 = joy_data.buttons[7];
    }

    void Joy_Simple_Operator::convert_joy2mpower(){
        zeromize(&_mpower,_mpower.size());
        if(joy_data.buttons[6]==1){
            

            heave_linz.calcMotorPowerDigital(joy_data.buttons[5]-joy_data.buttons[4]);
            //ROS_INFO("button : %d", joy_data.buttons[5]-joy_data.buttons[4]);

            heave_linz.sumPower(&_mpower);
            //ROS_INFO("ushiro");

            surge_linx.calcMotorPowerAnalog(joy_data.axes[1]);           
            surge_linx.sumPower(&_mpower);
            sway_liny.calcMotorPowerAnalog(joy_data.axes[0]);
            sway_liny.sumPower(&_mpower);
            
            pitch_roty.calcMotorPowerAnalog(joy_data.axes[4]);
            pitch_roty.sumPower(&_mpower);
          
            yaw_rotz.calcMotorPowerAnalog(joy_data.axes[3]);
            yaw_rotz.sumPower(&_mpower);
            set_form.calcMotorPowerDigital(is_drone_mode);
            set_form.sumPower(&_mpower);

            int _max = maxAbs(&_mpower, 3); // BLDCの入力で100超えてないか？
            if (_max<100){
                _max = 100;
            }
            for (int i = 0; i<_mpower.size(); i++){
                motor_data.data[i] = 0;
                for (int j = 0; j<3; j++){
                    motor_data.data[i] += (int)((double)connection_matrix[i][j]*_mpower[j]/_max);
                }
                for (int j = 3; j<6; j++){
                    motor_data.data[i] += connection_matrix[i][j]*_mpower[j];
                }
            }
        }else{
            for (int i = 0; i<_mpower.size(); i++){
                motor_data.data[i] = 0;
            }
        }
    }
/*
    void Joy_Simple_Operator::convert_joy2twist(){
        if(joy_data.buttons[6]==1){
            controller_msg.linear.x = joy_data.axes[1];
            controller_msg.linear.y = -1*joy_data.axes[0];
            controller_msg.linear.z = (joy_data.buttons[5]-joy_data.buttons[4])*0.7;
            controller_msg.angular.y = -1*joy_data.axes[3];
            controller_msg.angular.z = joy_data.axes[2];
            controller_msg.angular.x = 0;
        }
        else{
            controller_msg.linear.x = 0;
            controller_msg.linear.y = 0;
            controller_msg.linear.z = 0;
            controller_msg.angular.y = 0;
            controller_msg.angular.z = 0;
            controller_msg.angular.x = 0;
        }
    }
*/
    void Joy_Simple_Operator::send_msg(){
        motor_data_pub.publish(motor_data);
        mode_command_pub.publish(mode_command);
    }
    
    void Joy_Simple_Operator::zeromize(std::vector<int>* dat_ptr, int num){
        if (dat_ptr == nullptr) {
            ROS_ERROR("Null Pointer :zeromize");
            return;
        }
        for (int i=0; i<num; i++){
            (*dat_ptr)[i] = 0;
        }
    }

    int Joy_Simple_Operator::maxAbs(std::vector<int>* dat_ptr, int num){
        if (dat_ptr == nullptr) {
            ROS_ERROR("Null Pointer :maxAbs");
            return 1;
        }
        int itr=0; int _max=1;
        for (int i=0; i<num; i++) {
            if(_max<(*dat_ptr)[i]) {
                itr = i;
                _max=(*dat_ptr)[i];
            }
        }
        return _max;
    }
}