export ROS_MASTER_URI=http://192.168.2.100:11311
export ROS_IP=192.168.2.100
sudo chmod 777 /dev/ttyACM0
source ~/catkin_kurione_ws/devel/setup.bash
cd ~/catkin_kurione_ws/src/2021_Clione

roslaunch main/launch/rov_robot.launch