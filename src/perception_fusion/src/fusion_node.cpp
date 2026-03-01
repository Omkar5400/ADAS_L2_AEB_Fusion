#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "perception_fusion/kalman_filter.hpp"

class FusionNode : public rclcpp::Node {
public:
    FusionNode() : Node("perception_fusion_node") {
        // 1. Initialize our Kalman Filter brain
        kf_.init(20.0); // Assume object starts at 20m

        // 2. Subscribe to Radar (Low noise/High trust)
        radar_sub_ = this->create_subscription<geometry_msgs::msg::Point>(
            "radar_data", 10, std::bind(&FusionNode::radar_callback, this, std::placeholders::_1));

        // 3. Subscribe to Camera (Higher noise/Lower trust)
        camera_sub_ = this->create_subscription<geometry_msgs::msg::Point>(
            "camera_data", 10, std::bind(&FusionNode::camera_callback, this, std::placeholders::_1));

        // 4. Publisher for the "Clean" fused data
        fused_pub_ = this->create_publisher<geometry_msgs::msg::Point>("fused_data", 10);

        // 5. Timer for the Prediction step (10Hz)
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&FusionNode::predict_step, this));
    }

private:
    void predict_step() {
        kf_.predict(0.1); // Predict movement over 0.1 seconds
        publish_fused();
    }

    void radar_callback(const geometry_msgs::msg::Point::SharedPtr msg) {
        kf_.update(msg->x, 0.05); // Radar variance is small (0.05)
    }

    void camera_callback(const geometry_msgs::msg::Point::SharedPtr msg) {
        kf_.update(msg->x, 0.5);  // Camera variance is large (0.5)
    }

    void publish_fused() {
        auto message = geometry_msgs::msg::Point();
        message.x = kf_.get_state();
        fused_pub_->publish(message);
        RCLCPP_INFO(this->get_logger(), "Fused Position: %.2f meters", message.x);
    }

    KalmanFilter kf_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr radar_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr camera_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr fused_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FusionNode>());
    rclcpp::shutdown();
    return 0;
}
