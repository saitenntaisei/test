
## ROV手順
### 手元pc
1. ジョイコンの接続
2. ジョイコンの接続確認
3. `$ ./ros_setup.sh`
4. `$ ROSCORE`
5. `$ roslaunch main rov_remote.launch`
### ラズパイ
1. `$sudo chmod 777 /dev//ttyACM0`
2. `$ ./ros_setup.sh`<-**絶対パスで指定**
3. `$ roslaunch main rov_robot.launch`

## メモ
- [USBシリアル接続時に自動で書込権限を付与する](https://www.robotech-note.com/entry/2018/07/23/ubuntu%E3%81%A7USB%E3%82%B7%E3%83%AA%E3%82%A2%E3%83%AB%E3%83%87%E3%83%90%E3%82%A4%E3%82%B9%EF%BC%88/dev/ttyACM0%E7%AD%89%EF%BC%89%E6%8E%A5%E7%B6%9A%E6%99%82%E3%81%AB%E8%87%AA%E5%8B%95%E3%81%A7%E6%9B%B8)
