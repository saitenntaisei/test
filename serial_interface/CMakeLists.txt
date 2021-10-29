cmake_minimum_required(VERSION 2.8.3)
project(serial_interface)

add_compile_options(-std=c++14)

############
# Packages #
############

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  kurione_msgs
)

#################################
# Catkin specific configuration #
#################################

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs
)

#########
# Build #
#########

### include ###

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

### node ###

add_executable(${PROJECT_NAME} 
  src/nucleo_driver.cpp
  src/communication.cpp
  src/serial_interface.cpp
)

target_link_libraries(${PROJECT_NAME} 
  ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

###########
# Install #
###########

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install(DIRECTORY include/
#  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#  FILES_MATCHING PATTERN "*.hpp"
# )

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)