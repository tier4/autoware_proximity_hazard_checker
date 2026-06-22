cmake_minimum_required(VERSION 3.14)
project(autoware_proximity_hazard_checker_msgs)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ProximityHazardObject.msg"
  "msg/ProximityHazardObjects.msg"
  DEPENDENCIES
  builtin_interfaces
  std_msgs
)

ament_auto_package()
