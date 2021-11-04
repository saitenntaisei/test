cd ~/catkin_kurione_ws/src/2021_Clione
git checkout .
git pull origin develop
catkin build -DCATKIN_BLACKLIST_PACKAGES="kurione_qr_reader"
source ../../devel/setup.bash