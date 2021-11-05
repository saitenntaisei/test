# 起動手順まとめ

## ラズパイのbビルド
2. ラズパイにディスプレイ，マウスを刺す．
3. ラズパイに電源を入れログインし，```source ~/catkin_kurione_ws/src/2021_Clione/bash_files/robot_build.sh```をターミナルで実行する．
4. **ラズパイのWifiをきる**
4. ```sudo shutdown now```等で一旦ラズパイの電源を落とす

## 本番
1. PCにて5つのタブを立ち上げ，全てに
```
source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_setup.sh
```
を施す
2. ラズパイにカメラ，Nucleoを接続する．
3. ラズパイとPCをLANで接続する．**ホストPCのwifiを切断する**．
4. ラズパイにモバイルバッテリーを接続し，電源を入れる．**ラズパイのWifiがきれている事を確認する**
5. PCにジョイスティックが刺さっていることを確認する
6. ラズパイにて```source ~/catkin_kurione_ws/src/2021_Clione/bash_files/robot_setup_and_start.sh```を実行し，処理を開始する．
7. PCにて```source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_start.sh```を実行し，処理を開始する．
8. PCにて画像出力を確認する．かくつく場合はラズパイの**Wifiがきれている事を確認**した上でシャットダウン．手順1に戻る．
9. ラズパイからディスプレイ，マウスを取り外し，機械班は封入を開始する．
10. PCのタブにて
```
rostopic echo /robot_info
```
を実行する．
11. PCのタブにて
```
roslaunch kurione_qr_reader/qr_reader/launch
```
を実行する．
12. PCのタブにて
```
rviz
```
を実行し．qrのイメージを追加する
13. PCのタブにて
```
rosbag record /image_1_raw /image_2_raw /qr_image /qr_info /qr_info /robot_info /command/mode /command/motor_power
```
を実行し．rosbagの記録を取る