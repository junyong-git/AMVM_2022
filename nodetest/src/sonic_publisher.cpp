#include "ros/ros.h" // ROS 관련 헤더 포함
#include "std_msgs/Float64.h" // 표준 자료형 메시지 패키지 포함

int main(int argc, char **argv){
    ros::init(argc, argv, "name_of_pub_node");//ROS 초기화. node 이름 지정
    ros::NodeHandle nh;
    ros::Publisher i_am_the_publisher = nh.advertise<std_msgs::Float64>("sonic_listener", 100);

    ros::Rate loop_rate(5); // loop 주기 5hz

    float count = 0;

    while(ros::ok()){
        std_msgs::Float64 testmsg;

        testmsg.data = count;
        ROS_INFO("value: %f\n", testmsg.data);

        i_am_the_publisher.publish(testmsg);
        ros::spinOnce();
        loop_rate.sleep();
        count++;
        if(count == 20) count = 0;        
    }
    return 0;
}
