#include "limo_control.hpp"
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
        double dx = goal_x - x_1;
        double dy = goal_y - y_1;
        double distance_error = sqrt(dx*dx + dy*dy);
        double theta_error = (goal_theta - theta_1) % M_PI;

  
        double velocity = k_v * distance_error;
        double angular_velocity = k_w * theta_error;

        if (distance_error < 0.05) {
            velocity = 0.0
        }

        if (theta_error < 0.1) {
            angular_velocity = 0.0
        }

        auto twist_msg = geometry_msgs::msg::Twist();
        twist_msg.linear.x = velocity;
        twist_msg.angular.z = angular_velocity;
        cmd_vel_pub_->publish(twist_msg);
    }
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr publisher;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscriber;
    rclcpp::TimerBase::SharedPtr timer;
};

int main(int argc, char * argv[]) 
{
    rclcpp::init(argc, argv);
    rclcpp::spin(make_shared<Controller>());
    rclcpp::shutdown();
    return 0;
}
