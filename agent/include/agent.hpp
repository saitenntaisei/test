#pragma once

#include <ros/ros.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include<std_msgs/Int8MultiArray.h>
#include "determining_input_value.hpp"


namespace aqua{
    class Agent{
    public:
        Agent();
        ~Agent();
        void debug_determining_input_value();

    public:
        float input_variable[6];
    };
}