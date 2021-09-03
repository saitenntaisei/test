#ifndef _UWRAI19_PACKET_HPP_
#define _UWRAI19_PACKET_HPP_

#include <cstdint>

namespace uwrai19 {
    struct PacketData {
        int8_t motor_power[6];
        // moteor_power: motor power -100 ~ 100 [%]
    };
}

#endif