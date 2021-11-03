source ~/catkin_kurione_ws/devel/setup.bash
roslaunch main/launch/rov_remote.launch
rostopic echo /robot_info
#rosbag record -a
#rosbag record /image /robot_info
#rosbag record /image /command/mode /command/motor_power /robot_info
#rosbag record /command/mode /command/motor_power /robot_info