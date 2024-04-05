// Auto-generated. Do not edit!

// (in-package extract_pose_service.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class object_and_target_positionRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type object_and_target_positionRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type object_and_target_positionRequest
    let len;
    let data = new object_and_target_positionRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'extract_pose_service/object_and_target_positionRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new object_and_target_positionRequest(null);
    return resolved;
    }
};

class object_and_target_positionResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.object_position = null;
      this.target_position = null;
      this.is_no_obj = null;
      this.yaw_ang = null;
    }
    else {
      if (initObj.hasOwnProperty('object_position')) {
        this.object_position = initObj.object_position
      }
      else {
        this.object_position = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('target_position')) {
        this.target_position = initObj.target_position
      }
      else {
        this.target_position = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('is_no_obj')) {
        this.is_no_obj = initObj.is_no_obj
      }
      else {
        this.is_no_obj = false;
      }
      if (initObj.hasOwnProperty('yaw_ang')) {
        this.yaw_ang = initObj.yaw_ang
      }
      else {
        this.yaw_ang = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type object_and_target_positionResponse
    // Serialize message field [object_position]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.object_position, buffer, bufferOffset);
    // Serialize message field [target_position]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.target_position, buffer, bufferOffset);
    // Serialize message field [is_no_obj]
    bufferOffset = _serializer.bool(obj.is_no_obj, buffer, bufferOffset);
    // Serialize message field [yaw_ang]
    bufferOffset = _serializer.float64(obj.yaw_ang, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type object_and_target_positionResponse
    let len;
    let data = new object_and_target_positionResponse(null);
    // Deserialize message field [object_position]
    data.object_position = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [target_position]
    data.target_position = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [is_no_obj]
    data.is_no_obj = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [yaw_ang]
    data.yaw_ang = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 57;
  }

  static datatype() {
    // Returns string type for a service object
    return 'extract_pose_service/object_and_target_positionResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd051dd672e8e1f075426d8f6143b08a6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new object_and_target_positionResponse(null);
    if (msg.object_position !== undefined) {
      resolved.object_position = geometry_msgs.msg.Point.Resolve(msg.object_position)
    }
    else {
      resolved.object_position = new geometry_msgs.msg.Point()
    }

    if (msg.target_position !== undefined) {
      resolved.target_position = geometry_msgs.msg.Point.Resolve(msg.target_position)
    }
    else {
      resolved.target_position = new geometry_msgs.msg.Point()
    }

    if (msg.is_no_obj !== undefined) {
      resolved.is_no_obj = msg.is_no_obj;
    }
    else {
      resolved.is_no_obj = false
    }

    if (msg.yaw_ang !== undefined) {
      resolved.yaw_ang = msg.yaw_ang;
    }
    else {
      resolved.yaw_ang = 0.0
    }

    return resolved;
    }
};

module.exports = {
  Request: object_and_target_positionRequest,
  Response: object_and_target_positionResponse,
  md5sum() { return 'd051dd672e8e1f075426d8f6143b08a6'; },
  datatype() { return 'extract_pose_service/object_and_target_position'; }
};
