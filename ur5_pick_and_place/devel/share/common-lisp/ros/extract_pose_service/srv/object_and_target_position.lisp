; Auto-generated. Do not edit!


(cl:in-package extract_pose_service-srv)


;//! \htmlinclude object_and_target_position-request.msg.html

(cl:defclass <object_and_target_position-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass object_and_target_position-request (<object_and_target_position-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <object_and_target_position-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'object_and_target_position-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name extract_pose_service-srv:<object_and_target_position-request> is deprecated: use extract_pose_service-srv:object_and_target_position-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <object_and_target_position-request>) ostream)
  "Serializes a message object of type '<object_and_target_position-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <object_and_target_position-request>) istream)
  "Deserializes a message object of type '<object_and_target_position-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<object_and_target_position-request>)))
  "Returns string type for a service object of type '<object_and_target_position-request>"
  "extract_pose_service/object_and_target_positionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'object_and_target_position-request)))
  "Returns string type for a service object of type 'object_and_target_position-request"
  "extract_pose_service/object_and_target_positionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<object_and_target_position-request>)))
  "Returns md5sum for a message object of type '<object_and_target_position-request>"
  "d051dd672e8e1f075426d8f6143b08a6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'object_and_target_position-request)))
  "Returns md5sum for a message object of type 'object_and_target_position-request"
  "d051dd672e8e1f075426d8f6143b08a6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<object_and_target_position-request>)))
  "Returns full string definition for message of type '<object_and_target_position-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'object_and_target_position-request)))
  "Returns full string definition for message of type 'object_and_target_position-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <object_and_target_position-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <object_and_target_position-request>))
  "Converts a ROS message object to a list"
  (cl:list 'object_and_target_position-request
))
;//! \htmlinclude object_and_target_position-response.msg.html

(cl:defclass <object_and_target_position-response> (roslisp-msg-protocol:ros-message)
  ((object_position
    :reader object_position
    :initarg :object_position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (target_position
    :reader target_position
    :initarg :target_position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (is_no_obj
    :reader is_no_obj
    :initarg :is_no_obj
    :type cl:boolean
    :initform cl:nil)
   (yaw_ang
    :reader yaw_ang
    :initarg :yaw_ang
    :type cl:float
    :initform 0.0))
)

(cl:defclass object_and_target_position-response (<object_and_target_position-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <object_and_target_position-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'object_and_target_position-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name extract_pose_service-srv:<object_and_target_position-response> is deprecated: use extract_pose_service-srv:object_and_target_position-response instead.")))

(cl:ensure-generic-function 'object_position-val :lambda-list '(m))
(cl:defmethod object_position-val ((m <object_and_target_position-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader extract_pose_service-srv:object_position-val is deprecated.  Use extract_pose_service-srv:object_position instead.")
  (object_position m))

(cl:ensure-generic-function 'target_position-val :lambda-list '(m))
(cl:defmethod target_position-val ((m <object_and_target_position-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader extract_pose_service-srv:target_position-val is deprecated.  Use extract_pose_service-srv:target_position instead.")
  (target_position m))

(cl:ensure-generic-function 'is_no_obj-val :lambda-list '(m))
(cl:defmethod is_no_obj-val ((m <object_and_target_position-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader extract_pose_service-srv:is_no_obj-val is deprecated.  Use extract_pose_service-srv:is_no_obj instead.")
  (is_no_obj m))

(cl:ensure-generic-function 'yaw_ang-val :lambda-list '(m))
(cl:defmethod yaw_ang-val ((m <object_and_target_position-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader extract_pose_service-srv:yaw_ang-val is deprecated.  Use extract_pose_service-srv:yaw_ang instead.")
  (yaw_ang m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <object_and_target_position-response>) ostream)
  "Serializes a message object of type '<object_and_target_position-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'object_position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target_position) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_no_obj) 1 0)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'yaw_ang))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <object_and_target_position-response>) istream)
  "Deserializes a message object of type '<object_and_target_position-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'object_position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target_position) istream)
    (cl:setf (cl:slot-value msg 'is_no_obj) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yaw_ang) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<object_and_target_position-response>)))
  "Returns string type for a service object of type '<object_and_target_position-response>"
  "extract_pose_service/object_and_target_positionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'object_and_target_position-response)))
  "Returns string type for a service object of type 'object_and_target_position-response"
  "extract_pose_service/object_and_target_positionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<object_and_target_position-response>)))
  "Returns md5sum for a message object of type '<object_and_target_position-response>"
  "d051dd672e8e1f075426d8f6143b08a6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'object_and_target_position-response)))
  "Returns md5sum for a message object of type 'object_and_target_position-response"
  "d051dd672e8e1f075426d8f6143b08a6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<object_and_target_position-response>)))
  "Returns full string definition for message of type '<object_and_target_position-response>"
  (cl:format cl:nil "geometry_msgs/Point object_position~%geometry_msgs/Point target_position~%bool is_no_obj~%float64 yaw_ang~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'object_and_target_position-response)))
  "Returns full string definition for message of type 'object_and_target_position-response"
  (cl:format cl:nil "geometry_msgs/Point object_position~%geometry_msgs/Point target_position~%bool is_no_obj~%float64 yaw_ang~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <object_and_target_position-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'object_position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target_position))
     1
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <object_and_target_position-response>))
  "Converts a ROS message object to a list"
  (cl:list 'object_and_target_position-response
    (cl:cons ':object_position (object_position msg))
    (cl:cons ':target_position (target_position msg))
    (cl:cons ':is_no_obj (is_no_obj msg))
    (cl:cons ':yaw_ang (yaw_ang msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'object_and_target_position)))
  'object_and_target_position-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'object_and_target_position)))
  'object_and_target_position-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'object_and_target_position)))
  "Returns string type for a service object of type '<object_and_target_position>"
  "extract_pose_service/object_and_target_position")