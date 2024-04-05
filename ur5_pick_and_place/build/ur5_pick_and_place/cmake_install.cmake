# Install script for directory: /home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/src/ur5_pick_and_place

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur5_pick_and_place/cmake" TYPE FILE FILES "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/build/ur5_pick_and_place/catkin_generated/installspace/ur5_pick_and_place-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/devel/share/roseus/ros/ur5_pick_and_place")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/devel/lib/python3/dist-packages/ur5_pick_and_place")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/devel/lib/python3/dist-packages/ur5_pick_and_place")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/build/ur5_pick_and_place/catkin_generated/installspace/ur5_pick_and_place.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur5_pick_and_place/cmake" TYPE FILE FILES "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/build/ur5_pick_and_place/catkin_generated/installspace/ur5_pick_and_place-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur5_pick_and_place/cmake" TYPE FILE FILES
    "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/build/ur5_pick_and_place/catkin_generated/installspace/ur5_pick_and_placeConfig.cmake"
    "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/build/ur5_pick_and_place/catkin_generated/installspace/ur5_pick_and_placeConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur5_pick_and_place" TYPE FILE FILES "/home/ryan/github_repository/robot_manipulator/ur5_pick_and_place/src/ur5_pick_and_place/package.xml")
endif()

