#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"

using namespace std::chrono_literals;

class RadarPublisher : public rclcpp::Node
{
public:
  RadarPublisher() : Node("radar_mock"), count_(0)
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Point>("radar_data", 10);
    timer_ = this->create_wall_timer(100ms, std::bind(&RadarPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = geometry_msgs::msg::Point();
    
    // Simulate a car 20m away, moving closer by 0.5m every 100ms
    double true_x = 20.0 - (count_ * 0.5);
    
    // Add Gaussian Noise (The "German Touch" for realism)
    std::default_random_engine generator;
    std::normal_distribution<double> dist(0.0, 0.2); // 20cm of jitter
    
    message.x = true_x + dist(generator);
    message.y = 0.0 + dist(generator);
    message.z = 0.0;

    RCLCPP_INFO(this->get_logger(), "Radar detected object at: '%.2f' meters", message.x);
    publisher_->publish(message);
    count_++;
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RadarPublisher>());
  rclcpp::shutdown();
  return 0;
}
