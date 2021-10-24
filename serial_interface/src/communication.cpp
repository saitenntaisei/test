
    #include "communication.hpp"
    #include<ros/ros.h>

namespace kurione {
    /*Communication::Communication(PinName txd, PinName rxd, PinName de_pin, PinName nre_pin) : serial(txd,rxd), de(de_pin), nre(nre_pin) {
        serial_ptr->baud(9600);
        status = STATUS_SLEEPING; // 初期化前状態に戻る
        flag_rdat_check = false;
    }*/
    Communication::Communication(SerialInterface* sp) {
        serial_ptr = sp;
        //serial_ptr->baud(9600);
        status = STATUS_SLEEPING; // 初期化前状態に戻る
        flag_rdat_check = false;
    }
    
    void Communication::init(int r) {
        role = r;
        status = STATUS_IDLING;
        //serial_ptr->attach(this, &Communication::receive ,Serial::RxIrq); 割り込みなどない
        //de = 0;
        //nre = 0;    // 受信許可
    }
    
    void Communication::receive(void){  // データ受け取り関数
        while(serial_ptr->readable()) {
            unsigned char c = serial_ptr->getc();
            if (status == STATUS_RECEIVING) { // 受信中
                if ( c==Command::END ){   // 終了コマンドなら，データ読み取り要求
                //printf("size:%d\n",receive_dat.size());
                    flag_rdat_check = true;
                    status = STATUS_IDLING; // 待機状態に戻る
                }else{
                    receive_dat.push(c);    // データ格納
                }
            }
            if (c==Command::START) {    // スタートコマンドなら，一旦受信バッファクリアして受け取りモード
                status = STATUS_RECEIVING;
                freshReceiveDat();
                return;
            }
        }
    }
    
    void Communication::sendDat(void){  // 格納されているデータを送信
        //de = 1;     // 送信許可
        status = STATUS_SENDING;
        serial_ptr->putc(Command::START);
        //wait_ms(1);
        ros::Duration(0.001).sleep(); // sleep for 1ms
        while(!send_dat.empty()) {
            serial_ptr->putc(send_dat.front());
            send_dat.pop();
            //wait_ms(1);
            ros::Duration(0.001).sleep(); // sleep for 1ms
        }
        serial_ptr->putc(Command::END);
        //wait_ms(1);
        ros::Duration(0.001).sleep(); // sleep for 1ms
    }
    
    int Communication::decode(void) {
        if (receive_dat.empty()){
            return 0;
        }
        receive_command_dat = receive_dat.front();
        receive_dat.pop();
        freshReceiveNumDat();
        while(!receive_dat.empty()){
            int dh = receive_dat.front();   // 上位桁が必ず先
            receive_dat.pop();
            if(receive_dat.empty())
                return -1;                  // データ個数エラー
            
            int dl = receive_dat.front();   //　下位桁が必ず後
            receive_dat.pop();
            
            int d = 1;
            unsigned char dhp = 0;
            dhp = dh;
            if (dh>=100){   // 符号マイナス
                dhp = dhp-100;
                d = -1;
            }
            d = d*(100*dhp+dl);
            receive_num_dat.push(d);
        }
        return 0;
    }
    
    int Communication::encode(void) {
        freshSendDat();
        send_dat.push(send_command_dat);
        while(!send_num_dat.empty()){
            int d = send_num_dat.front();
            send_num_dat.pop();
            if((d>9999)||(d<-9999))
                return -1;  // 値範囲エラー
            unsigned char dh,dl;
            dh = abs(d)/100;
            dl = abs(d)-100*dh;
            if(d<0)
                dh = dh+100;
            send_dat.push(dh);  // 上位が先
            send_dat.push(dl);  // 下位が後
        }
        return 0;
    }
    
    void Communication::freshReceiveDat(void) {
        while(!receive_dat.empty()) {
            receive_dat.pop();
        }
    }
    
    void Communication::freshSendDat(void) {
        while(!receive_dat.empty()) {
            receive_dat.pop();
        }
    }
    
    void Communication::freshSendNumDat(void) {
        while(!send_num_dat.empty()) {
            send_num_dat.pop();
        }
    }
    
    void Communication::freshReceiveNumDat(void) {
        while(!receive_num_dat.empty()) {
            receive_num_dat.pop();
        }
    }
    
    int Communication::abs(int x) {
        if (x>0)
        return x;
    if (x<=0)
        return -x;
    }
}