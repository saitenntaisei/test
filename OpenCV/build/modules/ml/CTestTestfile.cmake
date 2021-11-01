# CMake generated Testfile for 
# Source directory: /home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/modules/ml
# Build directory: /home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/build/modules/ml
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_ml "/home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/build/bin/opencv_test_ml" "--gtest_output=xml:opencv_test_ml.xml")
set_tests_properties(opencv_test_ml PROPERTIES  LABELS "Main;opencv_ml;Accuracy" WORKING_DIRECTORY "/home/yukiorigane/catkin_kurione_ws/src/2021_Clione/OpenCV/build/test-reports/accuracy")
