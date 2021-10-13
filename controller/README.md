
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
