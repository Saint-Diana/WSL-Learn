// Copyright 2021 Perception Engine, Inc. All rights reserved.
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

#ifndef ARS408_ROS__ARS408_ROS_NODE_HPP_
#define ARS408_ROS__ARS408_ROS_NODE_HPP_

#include "ars408_ros/ars408_driver.hpp"
#include "rclcpp/rclcpp.hpp"

#include "can_msgs/msg/frame.hpp"
#include "radar_msgs/msg/radar_scan.hpp"
#include "radar_msgs/msg/radar_tracks.hpp"
#include "unique_identifier_msgs/msg/uuid.hpp"

#include <random>
#include <string>
#include <unordered_map>
#include <vector>

class PeContinentalArs408Node : public rclcpp::Node
{
private:
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr subscriber_can_raw_;            // 订阅未经处理的 CAN 消息
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr subscription_;                  // 订阅经过处理的 CAN 消息
  rclcpp::Publisher<radar_msgs::msg::RadarTracks>::SharedPtr publisher_radar_tracks_;   // 发布雷达跟踪数据
  rclcpp::Publisher<radar_msgs::msg::RadarScan>::SharedPtr publisher_radar_scan_;       // 发布雷达扫描数据

  can_msgs::msg::Frame::ConstSharedPtr can_data_;                                       // 存储从 CAN 总线接收到的 CAN 消息数据

  std::string output_frame_;    // 输出雷达数据的坐标系名称
  bool publish_radar_track_;    // 是否发布雷达跟踪数据
  bool publish_radar_scan_;     // 是否发布雷达扫描数据
  bool sequential_publish_;     // 是否按顺序发布雷达数据
  double size_x_;               // 雷达覆盖区域的x坐标
  double size_y_;               // 雷达覆盖区域的y坐标

  const uint8_t max_radar_id = 255;                               // 雷达的最大 ID
  std::vector<unique_identifier_msgs::msg::UUID> UUID_table_;     // 用于存储雷达对象的唯一标识符（UUID）表
  std::string topic_type_;                                        // 存储发布的雷达数据的消息类型

  ars408::Ars408Driver ars408_driver_{};                          // ARS408 雷达驱动类对象，用于读取和写入 ARS408 雷达数据

  /**
   * @brief 当订阅者收到 CAN 消息时调用的回调函数
   *
   * @param can_msg CAN消息
   */
  void CanFrameCallback(const can_msgs::msg::Frame::SharedPtr can_msg);
  /**
   * @brief 生成 UUID 表的函数
   *
   */
  void GenerateUUIDTable();

  /**
   * @brief 将雷达对象转换为雷达跟踪数据
   *
   * @param in_object 雷达对象
   * @return radar_msgs::msg::RadarTrack 雷达跟踪数据
   */
  radar_msgs::msg::RadarTrack ConvertRadarObjectToRadarTrack(const ars408::RadarObject & in_object);

  /**
   * @brief 将雷达对象转换为雷达返回数据
   *
   * @param in_object 雷达对象
   * @return radar_msgs::msg::RadarReturn 雷达返回数据
   */
  radar_msgs::msg::RadarReturn ConvertRadarObjectToRadarReturn(
    const ars408::RadarObject & in_object);

  static uint32_t ConvertRadarClassToAwSemanticClass(
    const ars408::Obj_3_Extended::ObjectClassProperty & in_radar_class);
  static unique_identifier_msgs::msg::UUID GenerateRandomUUID();

public:
  explicit PeContinentalArs408Node(const rclcpp::NodeOptions & node_options);
  /**
   * @brief 用于处理检测到的雷达对象的回调函数
   *
   * @param detected_objects 测到的雷达对象
   */
  void RadarDetectedObjectsCallback(
    const std::unordered_map<uint8_t, ars408::RadarObject> & detected_objects);
  /**
   * @brief 运行节点的函数
   *
   */
  void Run();
};

#endif  // ARS408_ROS__ARS408_ROS_NODE_HPP_
