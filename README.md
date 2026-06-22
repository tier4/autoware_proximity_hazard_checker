# autoware_proximity_hazard_checker

Publishes per-sector proximity hazards for the L2 HMI alert function.

The node subscribes to the Autoware predicted-objects topic and ego odometry, classifies each
nearby object into one of eight angular sectors around the vehicle, and publishes a fixed-size
`ProximityHazardObjects` message. A downstream HMI node consumes this message to drive
directional proximity alerts.

## Messages

Both message types are defined inside this package (no separate msgs package).

### `ProximityHazardObject`

| Field              | Type                                       | Description                                                            |
| ------------------ | ------------------------------------------ | ---------------------------------------------------------------------- |
| `has_object`       | `bool`                                     | `true` if a nearby object is present in this sector                    |
| `distance_m`       | `float32`                                  | Polygon-to-polygon distance [m]; valid iff `has_object`                |
| `predicted_object` | `autoware_perception_msgs/PredictedObject` | Source perception object, propagated unchanged; valid iff `has_object` |

### `ProximityHazardObjects`

An array of exactly 8 `ProximityHazardObject` entries, one per sector:

| Index constant | Value | Direction     |
| -------------- | ----- | ------------- |
| `FRONT`        | 0     | Forward       |
| `FRONT_RIGHT`  | 1     | Forward-right |
| `RIGHT`        | 2     | Right         |
| `REAR_RIGHT`   | 3     | Rear-right    |
| `REAR`         | 4     | Rearward      |
| `REAR_LEFT`    | 5     | Rear-left     |
| `LEFT`         | 6     | Left          |
| `FRONT_LEFT`   | 7     | Forward-left  |

## Topics

| Direction | Topic                                                                 | Type                                                       |
| --------- | --------------------------------------------------------------------- | ---------------------------------------------------------- |
| Input     | `~/input/objects` (default: `/perception/object_recognition/objects`) | `autoware_perception_msgs/PredictedObjects`                |
| Input     | `~/input/odometry` (default: `/localization/kinematic_state`)         | `nav_msgs/Odometry`                                        |
| Output    | `~/output/proximity_hazards` (default: `/hmi/proximity_hazards`)      | `autoware_proximity_hazard_checker/ProximityHazardObjects` |
| Debug     | `~/debug/sector_markers`                                              | `visualization_msgs/MarkerArray`                           |

## Parameters

{{ json_to_markdown("perception/autoware_proximity_hazard_checker/schema/autoware_proximity_hazard_checker.schema.json") }}

## Usage

```bash
ros2 launch autoware_proximity_hazard_checker proximity_hazard_checker.launch.xml \
    input_objects:=/perception/object_recognition/objects \
    input_odometry:=/localization/kinematic_state \
    output_hazards:=/hmi/proximity_hazards
```

## Building

```bash
# Import build dependencies
vcs import src < build_depends.repos

# Install ROS dependencies
rosdep install --from-paths src --ignore-src -r -y

# Build
colcon build --packages-up-to autoware_proximity_hazard_checker
```
