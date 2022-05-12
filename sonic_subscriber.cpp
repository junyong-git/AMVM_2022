#include "ros/ros.h"
#include "std_msgs/Float64.h"

void subscriberCallback(const std_msgs::Float64 msg){
    ROS_INFO("Received: %f\n", msg.data);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "sonic_chatter");
    ros::NodeHandle nh;

    ros::Subscriber i_am_the_subscriber = nh.subscribe("sonic_chatter",100,subscriberCallback);
    ros::spin();
    return 0;
}