// Generated by gencpp from file extract_pose_service/object_and_target_positionRequest.msg
// DO NOT EDIT!


#ifndef EXTRACT_POSE_SERVICE_MESSAGE_OBJECT_AND_TARGET_POSITIONREQUEST_H
#define EXTRACT_POSE_SERVICE_MESSAGE_OBJECT_AND_TARGET_POSITIONREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace extract_pose_service
{
template <class ContainerAllocator>
struct object_and_target_positionRequest_
{
  typedef object_and_target_positionRequest_<ContainerAllocator> Type;

  object_and_target_positionRequest_()
    {
    }
  object_and_target_positionRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> const> ConstPtr;

}; // struct object_and_target_positionRequest_

typedef ::extract_pose_service::object_and_target_positionRequest_<std::allocator<void> > object_and_target_positionRequest;

typedef boost::shared_ptr< ::extract_pose_service::object_and_target_positionRequest > object_and_target_positionRequestPtr;
typedef boost::shared_ptr< ::extract_pose_service::object_and_target_positionRequest const> object_and_target_positionRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace extract_pose_service

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "extract_pose_service/object_and_target_positionRequest";
  }

  static const char* value(const ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct object_and_target_positionRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::extract_pose_service::object_and_target_positionRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // EXTRACT_POSE_SERVICE_MESSAGE_OBJECT_AND_TARGET_POSITIONREQUEST_H