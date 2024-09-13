#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h> 

using namespace std;

class Controller : public rclcpp::Node 
{
public:

    Controller() {
        subscriber =  this->create_subscription<nav_msgs::msg::Odometry>("odom", 10, bind(&Controller::odometry_callback, this, placeholders::_1));
        publisher = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        timer = this->create_wall_timer(chrono::milliseconds(100), bind(&Controller::control_loop, this));

    }
private:
    void odometry_callback(const nav_msgs::msg::Odometry::SharedPtr msg)
    {
        x_1 = msg->pose.pose.position.x;
        y_1 = msg->pose.pose.position.y;

        tf2::Quaternion q(
            msg->pose.pose.orientation.x,
            msg->pose.pose.orientation.y,
            msg->pose.pose.orientation.z,
            msg->pose.pose.orientation.w);

        tf2::Matrix3x3 m(q);
        double roll, pitch, yaw;
        m.getRPY(roll, pitch, yaw);

        theta_1 = yaw;
    }

    void control_loop()
    {
        
    }
};

int main(int argc, char * argv[]) 
{
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<Controller>());
    rclcpp::shutdown();
    return 0;
}
