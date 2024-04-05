
https://github.com/ryanyu512/robot_manipulator/assets/19774686/49cc1acd-6efe-4487-b34c-608d256878f1


![Screenshot from 2024-04-05 15-48-59](https://github.com/ryanyu512/robot_manipulator/assets/19774686/d5af2b7f-65cb-4f1b-b676-ff4056b475e8)
![Screenshot from 2024-04-05 15-51-33](https://github.com/ryanyu512/robot_manipulator/assets/19774686/ba6778fb-f21f-4adf-b797-baa818e6bdbb)

Brief:

This project utilise RGB-D sensor (kinect) to capture RGB image and depth image of objects at the picking area. Also, Moveit! and gazebo are utilised for generating collision free trajectories and simulation enviornment respectively. The whole purpose of the project is to demonstrate a simple pipeline of vision - grasping system. Contours of objects are extracted to obtain 2D centroids which are then transformed back to 3D point. And, Principle component analysis is utilised to estimate the yaw angle of the object. These two information could be combined to form the grasping pose of the end effector. 

Environment:
1. Ubuntu 20.04
2. ROS1 Noetic
3. OpenCV >= 4.

Running:
1. roslaunch ur5_gripper_moveit_config demo_gazebo.launch
2. osrun extract_pose_service extract_object_pose
3. rosrun ur5_pick_and_place ur5_pick_and_place

Package:
1. common-sensors: contain urdf.xacro of various common visual sensors
2. extract_pose_service: Service for estimating the poses of objects
3. universal_robot: provide kinematic desrciption of universal robot
4. ur5_gripper_moveit_config: the whole setup is built based on moveit_setup_assistant for adding ur5 and robotiq-85 gripper
5. ur5_pick_And_place: 
6. ur5_world: provide the simulation world setting
