cmake_minimum_required(VERSION 3.0.2)
project(ur5_pick_and_place)

find_package(catkin REQUIRED
  COMPONENTS
    extract_pose_service
    interactive_markers
    moveit_core
    moveit_ros_planning
    moveit_ros_planning_interface
    moveit_ros_perception
    rviz_visual_tools
    moveit_visual_tools
    pluginlib
    geometric_shapes
    pcl_ros
    pcl_conversions
    rosbag
    tf2_ros
    tf2_eigen
    tf2_geometry_msgs
    actionlib_msgs
    control_msgs
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs trajectory_msgs control_msgs  # Or other packages containing msgs
)

catkin_package(
  LIBRARIES
  INCLUDE_DIRS
  CATKIN_DEPENDS
    moveit_core
    moveit_visual_tools
    moveit_ros_planning_interface
    interactive_markers
    tf2_geometry_msgs
    actionlib_msgs
    control_msgs
    extract_pose_service
)

include_directories(SYSTEM ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIRS})

add_executable(ur5_pick_and_place src/ur5_pick_and_place.cpp)
target_link_libraries(ur5_pick_and_place ${catkin_LIBRARIES} ${Boost_LIBRARIES})

#install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
