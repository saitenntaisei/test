#pragma once

#include <ros/ros.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include<std_msgs/Int8MultiArray.h>


namespace aqua{
    class Agent{
    public:
        Agent();
        ~Agent();

    

    public:
        float input_variable[6];
    };
}