
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Int8.h>
#include <sstream>

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");

  std_msgs::Int8 msg;
  msg.data = 1;
  
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("chatter", 5000);

  while (ros::ok())
  {
  
    ROS_INFO("%d", msg.data);
    chatter_pub.publish(msg);


    if (msg.data == 1){
      msg.data = 2;
    } else{
      msg.data = 1;
    }


    ros::spinOnce();
    ros::Duration(20).sleep();

  }


  return 0;
}