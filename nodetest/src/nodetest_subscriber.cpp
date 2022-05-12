#include "ros/ros.h"
#include "std_msgs/Float64.h"

/**
 * 받은 메시지 데이터를 터미널에 출력하는 함수
 * 매개변수: std_msgs::int32 type 객체 smg
 */
void subscriberCallback(const std_msgs::Float64 msg){
    ROS_INFO("Received: %f\n", msg.data);

}

int main(int argc, char **argv){
    ros::init(argc, argv, "name_of_sub_node");
    ros::NodeHandle nh;

    ros::Subscriber i_am_the_subscriber = nh.subscribe("name_of_topic",100,subscriberCallback);
    ros::spin();
    return 0;

}