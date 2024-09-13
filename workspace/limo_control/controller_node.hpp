#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

using namespace std;

class Controller : public rclcpp::Node 
{
public:
    const double k_v = 0.5;
    const double k_w = 0.5;
    const double max_v = 0.5; 
    const double max_w = 1.0; 
    const double goal_x = 5;
    const double goal_y = 5;
    const double goal_theta = 0.8;
    double x_1, y_1, theta_1;

    Controller();

private:
    void odometry_callback(const nav_msgs::msg::Odometry::SharedPtr msg);
    void control_loop();
};
