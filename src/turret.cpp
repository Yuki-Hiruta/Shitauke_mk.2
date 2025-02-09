#include "turret.hpp"

Turret::Turret()
{
    //マイコンに砲塔の諸元を送る
    publisher_micon = this->create_publisher<std_msgs::msg::Float64MultiArray>("rogilink_flex", 100);

    //rogidriveに砲塔の諸元を送る
    publisher_odrive = this->create_publisher<rogidrive_msg::msg::RogidriveMessage>("odrive_cmd", 100);

    int turret_drive_system = this->get_parameter("turret_drive_system").as_int();
}

void Turret::publish_turret(float _pitch, float _yaw){
    if(turret_drive_system == 0)
    {
        auto message_odrive_pitch = rogidrive_msg::msg::RogidriveMessage();
        message_odrive_pitch.name = "pitch";
        message_odrive_pitch.mode = POSITION_CONTROL;
        message_odrive_pitch.vel = 50;
        message_odrive_pitch.pos = _pitch / (2*M_PI);

        auto message_odrive_yaw = rogidrive_msg::msg::RogidriveMessage();
        message_odrive_yaw.name = "yaw";
        message_odrive_yaw.mode = POSITION_CONTROL;
        message_odrive_yaw.vel = 50;
        message_odrive_yaw.pos = _yaw / (2*M_PI);

        publisher_odrive->publish(message_odrive_pitch);
        publisher_odrive->publish(message_odrive_yaw);
    }
    if(turret_drive_system == 1)
    {
        auto message_micon = std_msgs::msg::Float64MultiArray();
        message_micon.data = {_pitch, _yaw};
        publisher_micon->publish(message_micon);
    }
}
