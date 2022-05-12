#include "ros/ros.h" // ROS 관련 헤더 포함
#include "std_msgs/Float64.h" // 표준 자료형 메시지 패키지 포함

// ros::NodeHandle nh;
// std_msgs::Float64 Distance;
// ros::Publisher chatter("chatter",&Distance);

int main(int argc, char **argv){
    ros::init(argc, argv, "name_of_pub_node");//ROS 초기화. node 이름 지정
    ros::NodeHandle nh;
    ros::Publisher i_am_the_publisher = nh.advertise<std_msgs::Float64>("name_of_topic", 100);

    ros::Rate loop_rate(5); // loop 주기 5hz

    // nh.initNode(); //노드 핸들 초기화
    // nh.advertise(chatter); //chatter토픽 publish

    float count = 0;
    // float distance = 0;

    while(ros::ok()){
        std_msgs::Float64 testmsg;

        testmsg.data = count;
        ROS_INFO("value: %f\n", testmsg.data);//터미널 출력

        i_am_the_publisher.publish(testmsg);//실제 메시지 publish 부분
        ros::spinOnce();
        loop_rate.sleep();//loop주기외에 남은시간동안 sleep
        count++;

        // Distance.data = distance; 
        // chatter.publish(&Distance);
        // distance ++;
        // nh.spinOnce();
        
    }
    return 0;
}

// int main(){
//     ros::NodeHandle nh;
//     std_msgs::Float64 Distance;
//     ros::Publisher chatter("chatter",&Distance);
//     nh.initNode(); //노드 핸들 초기화
//     nh.advertise(chatter); //chatter토픽 publish

//     float count = 0;
//     // float distance = 0;

//     while(ros::ok()){

//         Distance.data = distance; 
//         chatter.publish(&Distance);
//         ros::spinOnce();
//         loop_rate.sleep();
//         count ++
        
//     }
//     return 0;
// }