execute_process(COMMAND "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/build/universal_robot/ur_kinematics/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/build/universal_robot/ur_kinematics/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
