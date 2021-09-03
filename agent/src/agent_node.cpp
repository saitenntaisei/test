#include "agent_node.hpp"

int main(int argc, char** argv){

    ros::init(argc,argv,"agent_node");

    aqua::Agent_node agent;

    ros::Rate looprate(10);
    while(ros::ok()){

        ros::spinOnce();
        looprate.sleep();
    }

    return 0;
}

namespace aqua{

    Agent_node::Agent_node(){
        agent_pub = nh_.advertise<std_msgs::Int8MultiArray>("/command/motor_power",100);
        agent_sub = nh_.subscribe<std_msgs::Int8MultiArray>("/data", 100, &Agent_node::set_data, this);
    
        motor_power_data.data.resize(8);

    }
    Agent_node::~Agent_node(){

    }
    void Agent_node::set_data(const std_msgs::Int8MultiArray::ConstPtr& data){

    }

    void Agent_node::msg_pub(){
        motor_power_data.data[6] = 0x7E;
        motor_power_data.data[6] = 0x7F;

        agent_pub.publish(motor_power_data);
    }
} 