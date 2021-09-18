#!/bin/bash

# 実行時に $source ./quick_setup.sh で実行

MASTER_IP="192.168.2.100"
export ROS_MASTER_URI=http://$MASTER_IP:11311
export ROS_HOSTNAME=`hostname -I | cut -d' ' -f1`
export ROS_IP=`hostname -I | cut -d' ' -f1`