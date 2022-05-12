#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int32.h"

const int motor_vel0 = 0, motor_vel1 = 50, motor_vel2 = 100, motor_vel3 = 250;

int position; // -2 -1 0 1 2
float distance_sub;

void sonicCallback(const std_msgs::Float64 dis){
    ROS_INFO("Distance: %f\n", dis.data);
    distance_sub = dis.data;
}

void cameraCallback(const std_msgs::Int32 pos){
    ROS_INFO("Position: %d\n", pos.data);
    position = pos.data;
}

int main(int argc, char **argv){
    
    ros::init(argc, argv, "sonic_chatter"); // distance sub
    ros::init(argc, argv, "camera_chatter"); // position sub
    ros::init(argc, argv, "motorL_chatter"); // motorL pub
    ros::init(argc, argv, "motorR_chatter"); // motorR pub

    ros::NodeHandle nh;    

    ros::Subscriber camera_subscriber = nh.subscribe("sonic_chatter", 100, sonicCallback);
    ros::Subscriber sonic_subscriber = nh.subscribe("camera_chatter", 100, cameraCallback);
    
    ros::Publisher motorL_publisher = nh.advertise<std_msgs::Int32>("motorL_chatter", 100);
    ros::Publisher motorR_publisher = nh.advertise<std_msgs::Int32>("motorR_chatter", 100);

    std_msgs::Int32 velocity_L;
    std_msgs::Int32 velocity_R;

    ros::Rate loop_rate(5);
    while(ros::ok()){
        if(distance_sub < 10){
            velocity_L.data = motor_vel0;
            velocity_R.data = motor_vel0;
            motorL_publisher.publish(velocity_L);
            motorR_publisher.publish(velocity_R);
        }
        else{
            if(position == -2){
                velocity_L.data = motor_vel1;
                velocity_R.data = motor_vel3;
                motorL_publisher.publish(velocity_L);
                motorR_publisher.publish(velocity_R);
            }
            else if(position == -1){
                velocity_L.data = motor_vel2;
                velocity_R.data = motor_vel3;
                motorL_publisher.publish(velocity_L);
                motorR_publisher.publish(velocity_R);
            }
            else if(position == 0){
                velocity_L.data = motor_vel3;
                velocity_R.data = motor_vel3;
                motorL_publisher.publish(velocity_L);
                motorR_publisher.publish(velocity_R);
            }
            else if(position == 1){
                velocity_L.data = motor_vel3;
                velocity_R.data = motor_vel2;
                motorL_publisher.publish(velocity_L);
                motorR_publisher.publish(velocity_R);
            }
            else if(position == 2){
                velocity_L.data = motor_vel3;
                velocity_R.data = motor_vel1;
                motorL_publisher.publish(velocity_L);
                motorR_publisher.publish(velocity_R);
            }
            else{ // 10
                velocity_L.data = motor_vel0;
                velocity_R.data = motor_vel0;
                motorL_publisher.publish(velocity_L);
                motorR_publisher.publish(velocity_R);
            }          
        }
        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::spin();

    return 0;
}