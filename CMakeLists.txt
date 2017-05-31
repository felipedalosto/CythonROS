cmake_minimum_required(VERSION 2.8.3)
project(cython)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(send_pose src/send_pose.cpp)
target_link_libraries(send_pose ${catkin_LIBRARIES})
add_dependencies(send_pose cython_generate_messages_cpp)


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(send_pose ${OpenCV_LIBRARIES})
