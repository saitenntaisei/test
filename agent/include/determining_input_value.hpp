#pragma once

#include <cmath>
#include<iostream>

namespace /* 定数 */{

    /* 慣性モーメント */
    float Ixx = 1;
    float Iyy = 1;
    float Izz = 1;

    /* 重心からの位置 */
    float l1 = 0;
    float l2 = 0.2;

    /* 重さ */
    float M = 1;    

    /* 勾配法定数 */
    float e = 0.01; //ステップ幅
    float gamma = 0.66; //再決定用定数
    
    /* 補助定数 */
    float f1 = sqrt(3)/(2*M);
    float f2 = 1/(2*M);
    float f4_1_1 = M*l1/(2*Ixx);
    float f4_1_2 = M*0.2/Ixx;
    float f4_2_1 = M*l1/(2*Ixx);
    float f4_2_2 = M*0.2/Ixx;
    float f4_3 = M*l1/Ixx;
    float f5_1_1 = M*sqrt(3)*l1/(2*Iyy);
    float f5_1_2 = M*l2/Iyy;
    float f5_2_1 = M*(-sqrt(3)*l1)/(2*Iyy);
    float f5_2_2 = M*l2/Iyy;
    float f5_3 = M*(l2-0.587)/Iyy;
    float f6_1_1 = M*(-l2)/(2*Izz);
    float f6_1_2 = M*(-sqrt(3)*0.2)/(2*Izz);
    float f6_2_1 = M*(-l2)/(2*Izz);
    float f6_2_2 = M*(-sqrt(3)*0.2)/(2*Izz);
    float f6_3 = M*(l2-0.587)/Izz;
    
}

namespace /* 変数 */{
    //float f[6];
    float J[6][6];

    /* 補助変数 */
    float u1cos1, u1sin1, u2cos2, u2sin2, u3cos3, u3sin3;
}

inline void state_function(float f[6],float q[6]){
    u1cos1 = q[0]*cos(q[3]);
    u1sin1 = q[0]*sin(q[3]);
    u2cos2 = q[1]*cos(q[4]);
    u2sin2 = q[1]*sin(q[4]);
    u3cos3 = q[2]*cos(q[5]);
    u3sin3 = q[2]*sin(q[5]);

    f[0] = f1*(u1cos1-u2cos2);
    f[1] = (-u1cos1-u2cos2)/2+u3cos3;
    f[2] = -u1sin1-u2sin2-u3sin3;
    f[3] = f4_1_1*u1cos1+f4_1_2*u2sin2+f4_2_1*u2cos2+f4_2_2*u2sin2+f4_3*u3cos3;
    f[4] = f5_1_1*u1cos1+f5_1_2*u2sin2+f5_2_1*u2cos2+f5_2_2*u2sin2+f5_3*u3sin3;
    f[5] = f6_1_1*u1cos1+f6_1_2*u2sin2+f6_2_1*u2cos2+f6_2_2*u2sin2+f6_3*u3cos3;

}

inline void determining_input_value(float q[6], float u[6]){

}