#include <rclcpp/rclcpp.hpp>
#include "keyboard_controller.hpp"

int main(int argc, char *argv[]){
    using namespace nanoshimarobot_ros2;
    rclcpp::init(argc, argv);
    while(rclcpp::ok()){
        rclcpp::spin(std::make_shared<keyboard_controller>());
    }
    rclcpp::shutdown();
}