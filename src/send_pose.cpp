
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Int8.h>
#include <sstream>

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
int color_state = 0;

int count_white(Mat input_image){

  int black_pixels = 0;
  int white_pixels = 0;

  for( int y = 0; y < input_image.rows; y++ ) {
    for( int x = 0; x < input_image.cols; x++ ) {
      if ( input_image.at<cv::Vec3b>(y,x) == cv::Vec3b(255,255,255) ) {
        white_pixels++;
      } 
      else if ( input_image.at<cv::Vec3b>(y,x) == cv::Vec3b(0,0,0) ) {
        black_pixels++;
      }               
    }

  }
  return white_pixels;
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "send_pose");
  
  //Mat cap = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  //waitKey(30);
  VideoCapture cap;

  if(!cap.open(1))
        return 0;
  
  Mat frame;
  Mat output_red;
  Mat output_green;

  int color_state = 0;

  std_msgs::Int8 msg;
  msg.data = 1;
  
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("pose", 5000);

  while (ros::ok())
  {
  
    

    cap >> frame;
    //frame = cap.clone();
    if( frame.empty() ) break; // end of video stream
      imshow("this is you, smile! :)", frame);
          //imwrite("test_images/image.png", frame);
      inRange(frame, cv::Scalar(0, 115, 0), cv::Scalar(255, 255, 105), output_green); // green segmentation
      inRange(frame, cv::Scalar(0, 0, 150), cv::Scalar(255, 123, 255), output_red); // green segmentation

          /*
          cout << "count green: " << count_white(output_green) << "\n";
          cout << "count red: " << count_white(output_red)  << "\n";*/

          if (count_white(output_green) > 40000 && color_state != 1){
            cout << " Its Green! \n";
            color_state = 1;
            ROS_INFO("%d", msg.data);
            msg.data = color_state;
            chatter_pub.publish(msg);
          } 

          if (count_white(output_red) > 30000 && color_state != 2)  {
            cout << " Its Red! \n ";
            color_state = 2;
            ROS_INFO("%d", msg.data);
            msg.data = color_state;
            chatter_pub.publish(msg);

          } if (count_white(output_green) < 40000 && count_white(output_red) < 30000 ) {
            //cout << " i cant see \n ";
            color_state = 0;
          }

          imshow("output_gree", output_green);
          imshow("output_red", output_red);

    if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }

    ros::spinOnce();
    if (color_state == 1 || color_state == 2){
      //ros::Duration(16).sleep();
    }

  }


  return 0;
}