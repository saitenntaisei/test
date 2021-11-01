# CMake generated Testfile for 
# Source directory: /home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/modules/flann
# Build directory: /home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/build/modules/flann
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_flann "/home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/build/bin/opencv_test_flann" "--gtest_output=xml:opencv_test_flann.xml")
set_tests_properties(opencv_test_flann PROPERTIES  LABELS "Main;opencv_flann;Accuracy" WORKING_DIRECTORY "/home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/build/test-reports/accuracy")
