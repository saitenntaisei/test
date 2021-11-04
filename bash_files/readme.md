# 起動手順まとめ
＜ビルド済の場合は手順4から実施＞
※PCには事前に5つ程度のタブを立ち上げて置き，全てに
```
source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_setup.sh
```
を施しておくと楽である

1. ラズパイにディスプレイ，マウスを刺す．
2. ラズパイに電源を入れログインし，```source ~/catkin_kurione_ws/src/2021_Clione/bash_files/robot_build.sh```をターミナルで実行する．
3. ```sudo shutdown now```等で一旦ラズパイの電源を落とす
4. ラズパイにカメラ，Nucleoを接続する．
5. ラズパイとPCをLANで接続する．**ホストPCのwifiを切断する**．
6. ラズパイにモバイルバッテリーを接続し，電源を入れる．
7. PC側にて```source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_setup.sh```を実行する．
8. PCにジョイスティックが刺さっていることを確認する
9. ラズパイにて```source ~/catkin_kurione_ws/src/2021_Clione/bash_files/robot_setup_and_start.sh```を実行し，処理を開始する．
10. PCにて```source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_start.sh```を実行し，処理を開始する．
11. PCにて画像出力を確認する．かくつく場合は手順3に戻る．
12. ラズパイからディスプレイ，マウスを取り外し，機械班は封入を開始する．
13. PCにて新たにタブを立ち上げ，
```
source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_setup.sh
rostopic echo /robot_info
```
を実行する．
14. PCにて新たにタブを立ち上げ，
```
source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_setup.sh
roslaunch kurione_qr_reader/qr_reader/launch
```
を実行する．
15. PCにて新たにタブを立ち上げ，
```
source ~/catkin_kurione_ws/src/2021_Clione/bash_files/remote_setup.sh
rviz
```
を実行し．qrのイメージを追加する
