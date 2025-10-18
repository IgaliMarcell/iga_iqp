#include <chrono>
#include <vector>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"

using namespace std::chrono_literals;

class GpsPublisher : public rclcpp::Node
{
public:
  GpsPublisher()
  : Node("gps_publisher_node"), index_(0)
  {
    pub_ = this->create_publisher<geometry_msgs::msg::Point>("/gps_points", 10);

    points_ = {
      make_point(0.0, 0.0),
      make_point(0.0, 1.0),
      make_point(1.0, 1.0),
      make_point(2.0, 1.0),
      make_point(2.0, 3.0)
    };

    timer_ = this->create_wall_timer(1s, std::bind(&GpsPublisher::timer_cb, this));
    RCLCPP_INFO(this->get_logger(), "[iga_iqp] gps_publisher_node started");
  }

private:
  geometry_msgs::msg::Point make_point(double x, double y)
  {
    geometry_msgs::msg::Point p;
    p.x = x; p.y = y; p.z = 0.0;
    return p;
  }

  void timer_cb()
  {
    auto msg = points_[index_];
    pub_->publish(msg);
    index_++;
    if (index_ >= static_cast<int>(points_.size())) {
      RCLCPP_INFO(this->get_logger(), "No more points!");
      index_ = 0;
    }
  }

  rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::vector<geometry_msgs::msg::Point> points_;
  int index_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GpsPublisher>());
  rclcpp::shutdown();
  return 0;
}