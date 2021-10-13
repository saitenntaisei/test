# ROV
## pc間通信接続確認
#### 手元pc,ラズパイ共通
[PC間通信備忘録](https://hackmd.io/ORA8CH5KTneoDHa3rMpYUQ?view)を参考にGUIで設定を行う
`ping`が両方から通ればとりあえずok!
#### 手元pc
1. [ジョイコンの接続](https://hackmd.io/Fw1-WYqvSIeGnvVnLXzVtg)を参考にジョイコンの接続確認を行う
3. `$ source ./ros_setup.sh`
4. `$ roscore`<-順序的に手元pcから操作し始める場合は手元pcでマスタを起動したほうがいいが、実験で行う際にはラズパイで起動したほうが都合がいい([PC間通信備忘録](https://hackmd.io/ORA8CH5KTneoDHa3rMpYUQ))
5. `$ source ./ros_setup.sh`
6. `$ roslaunch main rov_remote.launch`
#### ラズパイ
1. `$ sudo chmod 777 /dev//ttyACM0`
2. `$ source ./ros_setup.sh`<-**絶対パスで指定**
3. `$ roslaunch main rov_robot.launch`

## 実験用手順
前提:ラズパイ側が起動時にマスターと諸々のスクリプトを実行している&&IPの設定が保存されている
#### 手元pc
1. [ジョイコンの接続](https://hackmd.io/Fw1-WYqvSIeGnvVnLXzVtg)を参考にジョイコンの接続確認を行う
2. `$ source ./ros_setup.sh`
3. `$ roslaunch main rov_remote.launch`
## メモ
- [USBシリアル接続時に自動で書込権限を付与する](https://www.robotech-note.com/entry/2018/07/23/ubuntu%E3%81%A7USB%E3%82%B7%E3%83%AA%E3%82%A2%E3%83%AB%E3%83%87%E3%83%90%E3%82%A4%E3%82%B9%EF%BC%88/dev/ttyACM0%E7%AD%89%EF%BC%89%E6%8E%A5%E7%B6%9A%E6%99%82%E3%81%AB%E8%87%AA%E5%8B%95%E3%81%A7%E6%9B%B8)
