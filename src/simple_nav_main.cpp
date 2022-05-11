#include <rclcpp/rclcpp.hpp>
#include "simple_nav.hpp"

using namespace nanoshimarobot_ros2;

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    while(rclcpp::ok()){
        rclcpp::spin(std::make_shared<simple_nav>());
    }
    rclcpp::shutdown();
}