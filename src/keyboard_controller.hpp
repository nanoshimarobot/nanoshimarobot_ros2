#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <chrono>
#include <algorithm>
// #include 
// #include 

using namespace std::chrono_literals;

namespace nanoshimarobot_ros2{
    std::map<char, std::vector<float>> key_map{
        {'w', { 0,  1,  0}},
        {'a', {-1,  0,  0}},
        {'s', { 0, -1,  0}},
        {'d', { 1,  0,  0}}
    };

    class keyboard_controller : public rclcpp::Node{
        public:
            keyboard_controller(
                const std::string& name_space="",
                const rclcpp::NodeOptions& options=rclcpp::NodeOptions()
            ): Node("keyboard_controller", name_space, options){
                publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("keyboard_twist", 10);
                // timer_main_ = this->create_wall_timer(500ms, std::bind(&));
                timer_main_ = this->create_wall_timer(10ms, std::bind(&keyboard_controller::timer_main,this));
            }

            int getch(void){
                int ch;
                struct termios oldt;
                struct termios newt;

                // Store old settings, and copy to new settings
                tcgetattr(STDIN_FILENO, &oldt);
                newt = oldt;

                // Make required changes and apply the settings
                newt.c_lflag &= ~(ICANON | ECHO);
                newt.c_iflag |= IGNBRK;
                newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
                newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
                newt.c_cc[VMIN] = 1;
                newt.c_cc[VTIME] = 0;
                tcsetattr(fileno(stdin), TCSANOW, &newt);

                // Get the current character
                ch = getchar();

                // Reapply old settings
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

                return ch;
            }

            void publish_keyTwist(){
                char key = getch();
                geometry_msgs::msg::Twist key_twist;
                if(key_map.find(key) != key_map.end()){
                    key_twist.linear.x = key_map.at(key)[0];
                    key_twist.linear.y = key_map.at(key)[1];
                    key_twist.linear.z = key_map.at(key)[2];
                }
                publisher_->publish(key_twist);
            }

            void timer_main(){
                publish_keyTwist();
            }

        private:
            rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
            rclcpp::TimerBase::SharedPtr timer_main_;
    };
}