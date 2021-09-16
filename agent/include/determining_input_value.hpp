#pragma once

#include <cmath>
#include<iostream>
#include <stdio.h>

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
    float loop_differencial = 1e-3; // 終了判定
    float trial_num = 1000; //試行回数
    
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

    float j1_ = sqrt(3)/(2*M);
    float j2 = 1/(2*M);
    float j4_1 = M*l1/(2*Ixx);
    float j4_2 = M*0.4/(2*Ixx);
    float j4_3 = M*l1/Ixx;
    float j5_1 = M*sqrt(3)*l1/(2*Iyy);
    float j5_2 = M*l2/Iyy;
    float j5_3 = M*(l2-0.587)/Iyy;
    float j6_1 = M*(l2+sqrt(3)*0.2)/(2*Izz);
    float j6_2 = M*(l2-0.587)/Izz;

}

namespace /* 変数 */{
    float f[6];
    float J[6][6];
    float delta_q[6];

    /* 補助変数 */
    float u1cos1, u1sin1, u2cos2, u2sin2, u3cos3, u3sin3;
}

namespace clione_gradient_method{
    inline void state_function(float q[6]){
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

    inline void jacobian_matrix(float q[6]){
        J[0][0] = j1_*cos(q[0]);
        J[0][1] = -j1_*cos(q[1]);
        J[0][2] = 0;
        J[0][3] = -j1_*u1sin1;
        J[0][4] = j1_*u2sin2;
        J[0][5] = 0;
        J[1][0] = -j2*cos(q[0]);
        J[1][1] = -j2*cos(q[1]);
        J[1][2] = cos(q[2])/M;
        J[1][3] = j2*u1sin1;
        J[1][4] = j2*u2sin2;
        J[1][5] = -u3cos3/M;
        J[2][0] = -sin(q[0])/M;
        J[2][1] = -sin(q[1])/M;
        J[2][2] = -sin(q[2])/M;
        J[2][3] = -u1cos1/M;
        J[2][4] = -u2cos2/M;
        J[2][5] = -u3cos3/M;
        J[3][0] = j4_1*cos(q[0])-j4_2*sin(q[0]);
        J[3][1] = -j4_1*cos(q[1])+j4_2*sin(q[1]);
        J[3][2] = j4_3*cos(q[2]);
        J[3][3] = -j4_1*u1sin1+j4_2*u1cos1;
        J[3][4] = j4_1*u2sin2+j4_2*u2cos2;
        J[3][5] = -j4_3*u3sin3;
        J[4][0] = j5_1*cos(q[0])+j5_2*sin(q[0]);
        J[4][1] = -j5_1*cos(q[1])+j5_2*sin(q[1]);
        J[4][2] = j5_3*sin(q[2]);
        J[4][3] = -j5_1*u1sin1+j5_2*u1cos1;
        J[4][4] = j5_2*u2sin2+j5_2*u2cos2;
        J[4][5] = j5_3*u3cos3;
        J[5][0] = -j6_1*cos(q[0]);
        J[5][1] = -j6_1*cos(q[1]);
        J[5][2] = j6_2*cos(q[2]);
        J[5][3] = j6_1*u1sin1;
        J[5][4] = j6_1*u2sin2;
        J[5][5] = -j6_2*u3sin3;
    }

    inline void determining_input_value(float q[6], float u[6]){

    }

    inline void debug(float q[6]){
        state_function(q);
        jacobian_matrix(q);

        printf("state_function >>\n");
        for(int i=0;i<6;i++){
            printf("%f\n",f[i]);
        }
        printf("\n");

        printf("jacobian_matrix >>\n");
        for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                printf("%f ",J[i][j]);
            }
            printf("\n");
        }
    }
}