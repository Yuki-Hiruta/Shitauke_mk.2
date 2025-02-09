#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "rogidrive_msg/msg/rogidrive_message.hpp"

class Turret : public rclcpp::Node
{
public:
    Turret();
private:
    void publish_turret(float _pitch, float _yaw);

    rclcpp::Publisher<rogidrive_msg::msg::RogidriveMessage>::SharedPtr publisher_odrive;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher_micon;

    this->declare_parameter<int>("turret_drive_system", 0);
}