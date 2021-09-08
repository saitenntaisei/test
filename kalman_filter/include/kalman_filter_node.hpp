#pragma once

#include"kalman_filter.hpp"

namespace aqua{
    class KF_node:public KF{
    public:
        KF_node();    
        ~KF_node();
    };
}