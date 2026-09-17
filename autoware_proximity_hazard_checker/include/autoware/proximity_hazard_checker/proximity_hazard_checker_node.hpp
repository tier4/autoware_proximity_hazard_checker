// Copyright 2026 TIER IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef AUTOWARE__PROXIMITY_HAZARD_CHECKER__PROXIMITY_HAZARD_CHECKER_NODE_HPP_
#define AUTOWARE__PROXIMITY_HAZARD_CHECKER__PROXIMITY_HAZARD_CHECKER_NODE_HPP_

#include "autoware/proximity_hazard_checker/proximity_hazard_checker.hpp"

#include <autoware/agnocast_wrapper/node.hpp>
#include <autoware/agnocast_wrapper/polling_subscriber.hpp>
#include <autoware/agnocast_wrapper/tf2.hpp>
#include <rclcpp/rclcpp.hpp>

#include <autoware_perception_msgs/msg/predicted_objects.hpp>
#include <autoware_proximity_hazard_checker_msgs/msg/proximity_hazard_objects.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <memory>
#include <string>

namespace autoware::proximity_hazard_checker
{
using autoware_perception_msgs::msg::PredictedObjects;
using autoware_proximity_hazard_checker_msgs::msg::ProximityHazardObjects;
using nav_msgs::msg::Odometry;

class ProximityHazardCheckerNode : public autoware::agnocast_wrapper::Node
{
public:
  explicit ProximityHazardCheckerNode(const rclcpp::NodeOptions & options);

private:
  void on_timer();
  void publish_sector_markers(const std::string & frame_id);

  autoware::agnocast_wrapper::polling::PollingSubscriber<Odometry>::SharedPtr sub_odometry_ =
    autoware::agnocast_wrapper::polling::create_polling_subscriber<Odometry>(
      this, "~/input/odometry");
  autoware::agnocast_wrapper::polling::PollingSubscriber<PredictedObjects>::SharedPtr sub_objects_ =
    autoware::agnocast_wrapper::polling::create_polling_subscriber<PredictedObjects>(
      this, "~/input/objects");
  AUTOWARE_PUBLISHER_PTR(ProximityHazardObjects) pub_hazards_;
  AUTOWARE_PUBLISHER_PTR(visualization_msgs::msg::MarkerArray) pub_debug_markers_;
  AUTOWARE_TIMER_PTR timer_;

  std::unique_ptr<autoware::agnocast_wrapper::Buffer> tf_buffer_;
  std::unique_ptr<autoware::agnocast_wrapper::TransformListener> tf_listener_;

  std::shared_ptr<proximity_hazard_object::ParamListener> param_listener_;
  autoware_utils_geometry::LinearRing2d vehicle_footprint_;

  std::unique_ptr<ProximityHazardChecker> impl_;
};

}  // namespace autoware::proximity_hazard_checker

#endif  // AUTOWARE__PROXIMITY_HAZARD_CHECKER__PROXIMITY_HAZARD_CHECKER_NODE_HPP_
