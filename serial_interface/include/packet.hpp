#ifndef _KURIONE_PACKET_HPP_
#define _KURIONE_PACKET_HPP_

#include <cstdint>

namespace kurione {
    struct PacketData {
        int8_t motor_power[6];
        // moteor_power: motor power -100 ~ 100 [%]
    };
}

#endif