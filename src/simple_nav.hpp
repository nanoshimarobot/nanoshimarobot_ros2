#include <rclcpp/rclcpp.hpp>
#include "geometry_msgs/msg/twist.hpp"

namespace nanoshimarobot_ros2{
    using std::placeholders::_1;
    class simple_nav : public rclcpp::Node{
        public:
            simple_nav(
                const std::string& name_space="",
                const rclcpp::NodeOptions& options=rclcpp::NodeOptions()
            ): Node("simple_nav", name_space, options)
            {
                subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
                    "keyboard_twist", 10, std::bind(&simple_nav::topic_callback, this, _1)
                );

            }
        
        private:
            void topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const{
                RCLCPP_INFO(this->get_logger(), "keyboard_twist: linear_x : %f, linear_y : %f, linear_z : %f", msg->linear.x, msg->linear.y, msg->linear.z);
            }
            rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    };
}