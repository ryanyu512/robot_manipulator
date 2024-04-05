;; Auto-generated. Do not edit!


(when (boundp 'extract_pose_service::object_and_target_position)
  (if (not (find-package "EXTRACT_POSE_SERVICE"))
    (make-package "EXTRACT_POSE_SERVICE"))
  (shadow 'object_and_target_position (find-package "EXTRACT_POSE_SERVICE")))
(unless (find-package "EXTRACT_POSE_SERVICE::OBJECT_AND_TARGET_POSITION")
  (make-package "EXTRACT_POSE_SERVICE::OBJECT_AND_TARGET_POSITION"))
(unless (find-package "EXTRACT_POSE_SERVICE::OBJECT_AND_TARGET_POSITIONREQUEST")
  (make-package "EXTRACT_POSE_SERVICE::OBJECT_AND_TARGET_POSITIONREQUEST"))
(unless (find-package "EXTRACT_POSE_SERVICE::OBJECT_AND_TARGET_POSITIONRESPONSE")
  (make-package "EXTRACT_POSE_SERVICE::OBJECT_AND_TARGET_POSITIONRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass extract_pose_service::object_and_target_positionRequest
  :super ros::object
  :slots ())

(defmethod extract_pose_service::object_and_target_positionRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass extract_pose_service::object_and_target_positionResponse
  :super ros::object
  :slots (_object_position _target_position _is_no_obj _yaw_ang ))

(defmethod extract_pose_service::object_and_target_positionResponse
  (:init
   (&key
    ((:object_position __object_position) (instance geometry_msgs::Point :init))
    ((:target_position __target_position) (instance geometry_msgs::Point :init))
    ((:is_no_obj __is_no_obj) nil)
    ((:yaw_ang __yaw_ang) 0.0)
    )
   (send-super :init)
   (setq _object_position __object_position)
   (setq _target_position __target_position)
   (setq _is_no_obj __is_no_obj)
   (setq _yaw_ang (float __yaw_ang))
   self)
  (:object_position
   (&rest __object_position)
   (if (keywordp (car __object_position))
       (send* _object_position __object_position)
     (progn
       (if __object_position (setq _object_position (car __object_position)))
       _object_position)))
  (:target_position
   (&rest __target_position)
   (if (keywordp (car __target_position))
       (send* _target_position __target_position)
     (progn
       (if __target_position (setq _target_position (car __target_position)))
       _target_position)))
  (:is_no_obj
   (&optional (__is_no_obj :null))
   (if (not (eq __is_no_obj :null)) (setq _is_no_obj __is_no_obj)) _is_no_obj)
  (:yaw_ang
   (&optional __yaw_ang)
   (if __yaw_ang (setq _yaw_ang __yaw_ang)) _yaw_ang)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _object_position
    (send _object_position :serialization-length)
    ;; geometry_msgs/Point _target_position
    (send _target_position :serialization-length)
    ;; bool _is_no_obj
    1
    ;; float64 _yaw_ang
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _object_position
       (send _object_position :serialize s)
     ;; geometry_msgs/Point _target_position
       (send _target_position :serialize s)
     ;; bool _is_no_obj
       (if _is_no_obj (write-byte -1 s) (write-byte 0 s))
     ;; float64 _yaw_ang
       (sys::poke _yaw_ang (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _object_position
     (send _object_position :deserialize buf ptr-) (incf ptr- (send _object_position :serialization-length))
   ;; geometry_msgs/Point _target_position
     (send _target_position :deserialize buf ptr-) (incf ptr- (send _target_position :serialization-length))
   ;; bool _is_no_obj
     (setq _is_no_obj (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float64 _yaw_ang
     (setq _yaw_ang (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass extract_pose_service::object_and_target_position
  :super ros::object
  :slots ())

(setf (get extract_pose_service::object_and_target_position :md5sum-) "d051dd672e8e1f075426d8f6143b08a6")
(setf (get extract_pose_service::object_and_target_position :datatype-) "extract_pose_service/object_and_target_position")
(setf (get extract_pose_service::object_and_target_position :request) extract_pose_service::object_and_target_positionRequest)
(setf (get extract_pose_service::object_and_target_position :response) extract_pose_service::object_and_target_positionResponse)

(defmethod extract_pose_service::object_and_target_positionRequest
  (:response () (instance extract_pose_service::object_and_target_positionResponse :init)))

(setf (get extract_pose_service::object_and_target_positionRequest :md5sum-) "d051dd672e8e1f075426d8f6143b08a6")
(setf (get extract_pose_service::object_and_target_positionRequest :datatype-) "extract_pose_service/object_and_target_positionRequest")
(setf (get extract_pose_service::object_and_target_positionRequest :definition-)
      "---
geometry_msgs/Point object_position
geometry_msgs/Point target_position
bool is_no_obj
float64 yaw_ang

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")

(setf (get extract_pose_service::object_and_target_positionResponse :md5sum-) "d051dd672e8e1f075426d8f6143b08a6")
(setf (get extract_pose_service::object_and_target_positionResponse :datatype-) "extract_pose_service/object_and_target_positionResponse")
(setf (get extract_pose_service::object_and_target_positionResponse :definition-)
      "---
geometry_msgs/Point object_position
geometry_msgs/Point target_position
bool is_no_obj
float64 yaw_ang

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")



(provide :extract_pose_service/object_and_target_position "d051dd672e8e1f075426d8f6143b08a6")


