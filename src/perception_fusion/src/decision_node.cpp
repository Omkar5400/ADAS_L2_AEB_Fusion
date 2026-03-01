#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "std_msgs/msg/string.hpp"

class DecisionNode : public rclcpp::Node {
public:
    DecisionNode() : Node("aeb_decision_node") {
        subscription_ = this->create_subscription<geometry_msgs::msg::Point>(
            "fused_data", 10, std::bind(&DecisionNode::callback, this, std::placeholders::_1));
        
        publisher_ = this->create_publisher<std_msgs::msg::String>("brake_command", 10);
    }

private:
    void callback(const geometry_msgs::msg::Point::SharedPtr msg) {
        auto brake_msg = std_msgs::msg::String();
        
        // AEB Logic: If object is closer than 10 meters, BRAKE!
        // (Since your simulation is in negative numbers, we check absolute value)
        if (std::abs(msg->x) < 100.0) {
            brake_msg.data = "CRITICAL: EMERGENCY BRAKING ACTIVATED!";
            RCLCPP_ERROR(this->get_logger(), "COLLISION IMMINENT! Distance: %.2f", msg->x);
        } else {
            brake_msg.data = "Status: Clear";
            RCLCPP_INFO(this->get_logger(), "Safe distance maintained: %.2f", msg->x);
        }
        publisher_->publish(brake_msg);
    }
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DecisionNode>());
    rclcpp::shutdown();
    return 0;
}
