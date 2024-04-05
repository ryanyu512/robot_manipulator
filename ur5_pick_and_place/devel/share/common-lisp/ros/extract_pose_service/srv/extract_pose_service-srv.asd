
(cl:in-package :asdf)

(defsystem "extract_pose_service-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "object_and_target_position" :depends-on ("_package_object_and_target_position"))
    (:file "_package_object_and_target_position" :depends-on ("_package"))
  ))