#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/planning_scene_monitor/planning_scene_monitor.h>
#include <moveit/move_group_interface/move_group_interface.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include "extract_pose_service/object_and_target_position.h"
#include <tf/LinearMath/Quaternion.h>

bool move_to_pose_target(char* motion_name,
                         moveit::planning_interface::MoveGroupInterface &move_group_interface,
                         geometry_msgs::Pose &target_pose, 
                         moveit::planning_interface::MoveGroupInterface::Plan &my_plan){
    
    move_group_interface.setPoseTarget(target_pose);
    bool success = (move_group_interface.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    ROS_INFO_NAMED("UR5", "Goal position x:%f y:%f z:%f", target_pose.position.x, target_pose.position.y, target_pose.position.z);
    ROS_INFO_NAMED("UR5", "Goal orientation w: %f x:%f y:%f z:%f", target_pose.orientation.w, target_pose.orientation.x, target_pose.orientation.y, target_pose.orientation.z);
    ROS_INFO_NAMED("UR5", "motion: %s", motion_name);
    ROS_INFO_NAMED("UR5", "status: %s", success? "SUCCESS":"FAIL");

    if (success)
      move_group_interface.move();

  return success;
}

bool default_actions(moveit::planning_interface::MoveGroupInterface &move_group_interface,
                     moveit::planning_interface::MoveGroupInterface::Plan &my_plan,
                     char* motion_name){
    
    move_group_interface.setJointValueTarget(move_group_interface.getNamedTargetValues(motion_name));
    
    bool success = (move_group_interface.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    ROS_INFO_NAMED("UR5", "motion: %s", motion_name);
    ROS_INFO_NAMED("UR5", "status: %s", success? "SUCCESS":"FAIL");

    if (success)
      move_group_interface.move();

  return success;
}

void attach_obj_to_gripper(moveit_msgs::CollisionObject &collision_object,
                           moveit_msgs::AttachedCollisionObject &aco, 
                           moveit::planning_interface::PlanningSceneInterface &planning_scene_interface){

    aco.object.id = collision_object.id;
    aco.link_name = "robotiq_85_right_finger_tip_link";
    aco.touch_links.push_back("robotiq_85_left_finger_tip_link");
    aco.object.operation = moveit_msgs::CollisionObject::ADD;
    planning_scene_interface.applyAttachedCollisionObject(aco);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pick_and_place_opencv");
    ros::NodeHandle n;
    
    ros::AsyncSpinner spinner(1);
    spinner.start();

    static const std::string PLANNING_GROUP_ARM = "ur5_arm";
    static const std::string PLANNING_GROUP_GRIPPER = "gripper";
    
    moveit::planning_interface::MoveGroupInterface move_group_interface_arm(PLANNING_GROUP_ARM);
    moveit::planning_interface::MoveGroupInterface move_group_interface_gripper(PLANNING_GROUP_GRIPPER);

    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

    robot_model_loader::RobotModelLoaderPtr robot_model_loader(new robot_model_loader::RobotModelLoader("robot_description"));
    planning_scene_monitor::PlanningSceneMonitorPtr planning_scene_monitor(new planning_scene_monitor::PlanningSceneMonitor(robot_model_loader));

    //initialise planner
    moveit::planning_interface::MoveGroupInterface::Plan my_plan_arm;
    moveit::planning_interface::MoveGroupInterface::Plan my_plan_gripper;

    // initialise service client
    ros::ServiceClient box_and_target_position_srv_client = n.serviceClient<extract_pose_service::object_and_target_position>("object_and_target_position");
    extract_pose_service::object_and_target_position srv;

    // Allow collisions between the gripper and the box to be able to grasp it
    planning_scene_monitor::LockedPlanningSceneRW ls(planning_scene_monitor);
    collision_detection::AllowedCollisionMatrix& acm = ls->getAllowedCollisionMatrixNonConst();
    acm.setEntry("unit_box_blue1", "robotiq_85_left_finger_tip_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_right_finger_tip_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_right_inner_knuckle_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_left_inner_knuckle_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_base_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_left_finger_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_right_finger_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_left_knuckle_link", true);
    acm.setEntry("unit_box_blue1", "robotiq_85_right_knuckle_link", true);
    
    acm.print(std::cout);
    moveit_msgs::PlanningScene diff_scene;
    ls->getPlanningSceneDiffMsg(diff_scene);

    planning_scene_interface.applyPlanningScene(diff_scene); 

    ros::Duration(0.1).sleep();

    // We can get a list of all the groups in the robot:
    std::copy(move_group_interface_arm.getJointModelGroupNames().begin(),
            move_group_interface_arm.getJointModelGroupNames().end(), std::ostream_iterator<std::string>(std::cout, ", "));


    // 1. Move to home position
    bool success = default_actions(move_group_interface_arm, my_plan_arm, "home");

    if (!success)
      return -1;

    while (true){
      if(box_and_target_position_srv_client.call(srv)) {
        ROS_INFO_STREAM("3d target position camera frame: x " << srv.response.target_position.x << " y " << srv.response.target_position.y << " z " << srv.response.target_position.z);
        ROS_INFO_STREAM("3d object position camera frame: x " << srv.response.object_position.x << " y " << srv.response.object_position.y << " z " << srv.response.object_position.z);
      } else {
        ROS_INFO_STREAM("Failed to call box and target position service");
      }

      if (srv.response.is_no_obj == true){
        std::cout << "no more object" << std::endl;
        return 0;
      }

      double yaw_ang = srv.response.yaw_ang;

      // set collision object to the planning scene
      moveit_msgs::CollisionObject collision_object;
      collision_object.header.frame_id = move_group_interface_arm.getPlanningFrame();

      collision_object.id = "unit_box_blue1";

      shape_msgs::SolidPrimitive primitive;
      primitive.type = primitive.BOX;
      primitive.dimensions.resize(3);
      primitive.dimensions[0] = 0.06;
      primitive.dimensions[1] = 0.18;
      primitive.dimensions[2] = 0.06;

      geometry_msgs::Pose box_pose;

      tf::Quaternion box_q;
      box_q.setRPY(0,0,yaw_ang - 1.57);  

      box_pose.orientation.x = box_q.x();
      box_pose.orientation.y = box_q.y();
      box_pose.orientation.z = box_q.z();
      box_pose.orientation.w = box_q.w();

      box_pose.position.x = srv.response.object_position.x;
      box_pose.position.y = srv.response.object_position.y;
      box_pose.position.z = srv.response.object_position.z;

      collision_object.primitives.push_back(primitive);
      collision_object.primitive_poses.push_back(box_pose);
      collision_object.operation = collision_object.ADD;

      std::vector<moveit_msgs::CollisionObject> collision_objects;
      collision_objects.push_back(collision_object);

      planning_scene_interface.applyCollisionObjects(collision_objects);

      ROS_INFO_NAMED("UR5", "Add an object into the world");

      ros::Duration(0.1).sleep();

      // 2. Place the TCP (Tool Center Point, the tip of the robot) above the blue box
      geometry_msgs::Pose target_pose;

      tf::Quaternion q;
      q.setRPY(3.14,1.57,yaw_ang - 3.14);       

      target_pose.orientation.x = q.x();
      target_pose.orientation.y = q.y();
      target_pose.orientation.z = q.z();
      target_pose.orientation.w = q.w();

      target_pose.position.x = srv.response.object_position.x;
      target_pose.position.y = srv.response.object_position.y;
      target_pose.position.z = srv.response.object_position.z + 0.34;


      success = move_to_pose_target("Move to the object (above)", 
                                    move_group_interface_arm, 
                                    target_pose, 
                                    my_plan_arm);

      if (success == false){
        return -1;
      }

      // 3. Open the gripper
      success = default_actions(move_group_interface_gripper, 
                                my_plan_gripper, "open");

      if (success == false){
        return -1;
      }

      // 4. Move the TCP close to the object
      target_pose.position.z = target_pose.position.z - 0.2;
      success = move_to_pose_target("Move close to the object",
                                    move_group_interface_arm, 
                                    target_pose, 
                                    my_plan_arm
                                    );

      if (success == false){
        return -1;
      }

      // 5. Close the  gripper
      success = default_actions(move_group_interface_gripper, 
                                my_plan_gripper, "close");

      if (success == false){
        return -1;
      }

      // Attach the box to the gripper after it was grasped
      moveit_msgs::AttachedCollisionObject aco;
      attach_obj_to_gripper(collision_object, aco, planning_scene_interface);

      // 6. Move the TCP above the plate
      target_pose.position.z = srv.response.target_position.z + 0.5;
      target_pose.position.x = srv.response.target_position.x;
      target_pose.position.y = srv.response.target_position.y;

      success = move_to_pose_target("Move to the target area (above)", 
                                    move_group_interface_arm, 
                                    target_pose, 
                                    my_plan_arm);
      if (success == false){
        return -1;
      }

      // 7. Lower the TCP above the plate
      target_pose.position.z = target_pose.position.z - 0.14;

      success = move_to_pose_target("Move close the target position",
                                    move_group_interface_arm, 
                                    target_pose, 
                                    my_plan_arm);
      if (success == false){
        return -1;
      }

      // 8. Open the gripper
      success = default_actions(move_group_interface_gripper, 
                                my_plan_gripper, "open");

      if (success == false){
        return -1;
      }

      //remove attached object
      ROS_INFO_NAMED("UR5", "Remove the object from the world");
      aco.object.operation = moveit_msgs::CollisionObject::REMOVE; 
      planning_scene_interface.applyAttachedCollisionObject(aco);

      std::vector<std::string> object_ids;
      object_ids.push_back(collision_object.id);
      planning_scene_interface.removeCollisionObjects(object_ids);
    }

  ros::shutdown();
  return 0;
}
