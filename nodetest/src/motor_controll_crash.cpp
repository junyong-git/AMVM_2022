#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int32.h"

float distance;

void subscriberCallback(const std_msgs::Float64 msg){
    ROS_INFO("Received: %f\n", msg.data);
    distance = msg.data;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "sonic_chatter");
    ros::NodeHandle nh;

    ros::Subscriber i_am_the_subscriber = nh.subscribe("sonic_chatter", 100, subscriberCallback);

    ros::init(argc, argv, "motor_chatter");
    ros::Publisher i_am_the_publisher = nh.advertise<std_msgs::Int32>("motor_chatter", 100);

    ros::Rate loop_rate(5); // loop 주기 5hz
    std_msgs::Int32 velocity;
    while(ros::ok()){
        if(distance < 10){
            velocity.data = 0;
            i_am_the_publisher.publish(velocity);
        }
        else{
            velocity.data = 100;
            i_am_the_publisher.publish(velocity);
        }
        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::spin();

    return 0;
}