cmake_minimum_required(VERSION 3.0.2)
project(extract_pose_service)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  cv_bridge
  image_transport
  tf2_ros
  message_generation
)

find_package(OpenCV 4 REQUIRED)

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   object_and_target_position.srv
 )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs  # Or other packages containing msgs
   geometry_msgs
 )

catkin_package(
  INCLUDE_DIRS
  CATKIN_DEPENDS roscpp
                 sensor_msgs
                 std_msgs
                 cv_bridge
                 image_transport
                 tf2_ros
                 message_runtime
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(extract_object_pose src/extract_object_pose.cpp)

add_dependencies(extract_object_pose extract_pose_service_generate_messages_cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(extract_object_pose ${catkin_LIBRARIES} ${OpenCV_LIBS})

