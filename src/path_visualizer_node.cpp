#include <chrono>
#include <memory>
#include <vector>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "visualization_msgs/msg/marker.hpp"

using namespace std::chrono_literals;

class PathVisualizer : public rclcpp::Node
{
public:
  PathVisualizer() : Node("path_visualizer_node")
  {
    sub_ = this->create_subscription<geometry_msgs::msg::Point>(
      "/gps_points", 10,
      std::bind(&PathVisualizer::point_callback, this, std::placeholders::_1));

    marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("visualization_marker", 10);
    frame_id_ = "map";
    RCLCPP_INFO(this->get_logger(), "[iga_iqp] path_visualizer_node started");
  }

private:
  void point_callback(const geometry_msgs::msg::Point::SharedPtr msg)
  {
    bool is_start = (std::fabs(msg->x) < 1e-6) && (std::fabs(msg->y) < 1e-6);
    if (is_start && !points_.empty()) {
      clear_markers();
      points_.clear();
      RCLCPP_INFO(this->get_logger(), "New cycle detected, clearing path.");
    }
    points_.push_back(*msg);
    publish_markers();
  }

  void publish_markers()
  {
    visualization_msgs::msg::Marker line, spheres;
    line.header.frame_id = spheres.header.frame_id = frame_id_;
    line.header.stamp = spheres.header.stamp = this->now();
    line.ns = "path"; line.id = 0; line.type = visualization_msgs::msg::Marker::LINE_STRIP;
    line.action = visualization_msgs::msg::Marker::ADD;
    line.scale.x = 0.05;
    line.color.g = 1.0; line.color.a = 1.0;

    spheres.ns = "points"; spheres.id = 1; spheres.type = visualization_msgs::msg::Marker::SPHERE_LIST;
    spheres.action = visualization_msgs::msg::Marker::ADD;
    spheres.scale.x = spheres.scale.y = spheres.scale.z = 0.12;
    spheres.color.b = 1.0; spheres.color.a = 1.0;

    for (auto &p : points_) {
      line.points.push_back(p);
      spheres.points.push_back(p);
    }
    marker_pub_->publish(line);
    marker_pub_->publish(spheres);
  }

  void clear_markers()
  {
    visualization_msgs::msg::Marker clear;
    clear.header.frame_id = frame_id_;
    clear.header.stamp = this->now();
    clear.ns = "path"; clear.id = 0;
    clear.type = visualization_msgs::msg::Marker::LINE_STRIP;
    clear.action = visualization_msgs::msg::Marker::DELETEALL;
    marker_pub_->publish(clear);
  }

  rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr sub_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
  std::vector<geometry_msgs::msg::Point> points_;
  std::string frame_id_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PathVisualizer>());
  rclcpp::shutdown();
  return 0;
}
