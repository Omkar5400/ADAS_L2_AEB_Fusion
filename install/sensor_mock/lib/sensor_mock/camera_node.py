#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point
import random

class CameraPublisher(Node):
    def __init__(self):
        super().__init__('camera_mock')
        self.publisher_ = self.create_publisher(Point, 'camera_data', 10)
        self.timer = self.create_timer(0.1, self.timer_callback) # 10Hz
        self.count = 0

    def timer_callback(self):
        msg = Point()
        # The camera sees the same object as the radar
        true_x = 20.0 - (self.count * 0.5)
        
        # Camera is "noisier" in distance (x) than radar
        msg.x = true_x + random.uniform(-0.8, 0.8) 
        msg.y = 0.0 + random.uniform(-0.1, 0.1)
        
        self.get_logger().info(f'Camera reporting object at: {msg.x:.2f}m')
        self.publisher_.publish(msg)
        self.count += 1

def main(args=None):
    rclpy.init(args=args)
    node = CameraPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
