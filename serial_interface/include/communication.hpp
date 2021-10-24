
    #include "codebook.hpp"
    #include "serial_interface.hpp"
    #include <queue>

namespace kurione {
    class Communication {
    public:
        std::queue<unsigned char> send_dat;       // 送信データ
        std::queue<int> send_num_dat;             // 送信データの内数値部
        unsigned char send_command_dat;        // 受信データのコマンド部
        std::queue<unsigned char> receive_dat;    // 受信データ
        unsigned char receive_command_dat;        // 受信データのコマンド部
        std::queue<int> receive_num_dat;          // 受信データの内数値部

        int role;                       // 自分の役割を明記
        int status;                     // 現在の状態
        bool flag_rdat_check;           // 受信データ貯まったか
        
        //Serial serial;
        SerialInterface* serial_ptr;
        //DigitalOut de;
        //DigitalOut nre;
        
        enum {
            ROLL_LAND = 0,
            ROLL_BATT,
            ROLL_MAIN,
        };
        enum {
            STATUS_IDLING = 0,
            STATUS_SLEEPING,
            STATUS_RECEIVING,
            STATUS_SENDING,
        };
        
        // Communication(PinName, PinName, PinName, PinName);
        Communication(kurione::SerialInterface*);
        void init(int);         // rollを設定．受信処理開始
        void receive();    // 割り込み時の1バイト受け取り
        void sendDat();     // データ送信
        int decode();
        int encode();        
        void freshSendDat();
        void freshSendNumDat();
        void freshReceiveDat();
        void freshReceiveNumDat();
    
    private:
        int abs(int);
    };
}