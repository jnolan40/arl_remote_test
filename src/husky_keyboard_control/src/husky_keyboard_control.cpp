/*
 * Read keyboard inputs continuosly using the terminal
 * Code to use arrow keys for control and 0 for break
 * */

//CPP headers
#include <stdio.h>
#include <iostream>
#include <termios.h> // terminal config for I/O
#include <ncurses.h> // getch()
#include <unistd.h> // stdin
// ROS headers
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
// variables
double LIN_VEL;
double ANG_VEL;
int BUFFER_SIZE;

int key_read(){
// function takes keyboard input without RETURN key dependency
// Ref:  https://answers.ros.org/question/63491/keyboard-key-pressed/
  int ip_int, count = 1;
  char ip_key;
  bool assign = true;
  std::vector<char> ip_key_vec;
  ip_int = 0;
  system("stty raw");
  system("stty  -echo");
  while (count < 4) {
  // reading values from keyboard
    ip_key = getchar();
    //std::cout << "Key" << ip_key << std::endl; 
    count ++;
    if (ip_key == '0') {
      ip_int = 5;
      assign = false;
      system("stty cooked");
      std::cout << "" << std::endl;
      std::cout << "Keyboard Control Stopped" << std::endl;
      std::cout << "use Ctrl+C to stop all nodes" << std::endl;
      break;
    }
    // Only accept arrow: up, down, right or left
    if (!(int(ip_key) == 27 | int(ip_key) == 91 | int(ip_key) == 65 | int(ip_key) == 66 | int(ip_key) == 67 | int(ip_key) == 68)) {
      std::cout << "Invalid Input" << std::endl;
      assign = false;
      break;
    }
    ip_key_vec.push_back(ip_key); // accumulate the error
  } // end count while loop
  if (assign) {
    switch (ip_key_vec[2]) { // the real value
      case 'A': // up
        ip_int = 1;
        std::cout << "Forward "; 
        break;
      case 'B': // down
        ip_int = 2;
        std::cout << "Back ";
        break;
      case 'C': // right
        ip_int = 3;
        std::cout << "Right ";
        break;
      case 'D': // left
        ip_int = 4;
        std::cout << "Left ";
        break;
    } // end switch
  } // end if block
  // system("stty cooked");
  system("stty echo");
  return ip_int;
} // end function

int main(int argc, char **argv) {
	int dir_ip; // direction input from keyboard
	// ROS intialization
	ros::init (argc, argv, "husky_keyboard_demo");
	ros::NodeHandle hk,private_hk("~");
	private_hk.param<double>("LIN_VEL",LIN_VEL,1.0);
	private_hk.param<double>("ANG_VEL",ANG_VEL,1.0);
	private_hk.param<int>("BUFFER_SIZE",BUFFER_SIZE,1);
	ros::Publisher vel_cmd = hk.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel",BUFFER_SIZE);
	geometry_msgs::Twist cmd_msg;
  ROS_INFO ("Enter Arrow Keys for Motion");
  ROS_INFO ("Press ANY other key or no key for brake");
	ROS_INFO ("Press 0 for exit");
  ROS_INFO ("Commands are configured to a %d Buffer",BUFFER_SIZE);
	while (ros::ok()) {
    // Keyboard Input Processing
  	dir_ip = key_read(); // function call
  	// configuring the input for husky
  	cmd_msg.linear.x = 0;
  	cmd_msg.linear.y = 0;
  	cmd_msg.linear.z = 0;
  	cmd_msg.angular.x = 0;
  	cmd_msg.angular.y = 0;	
  	cmd_msg.angular.z = 0;
    // ROS_INFO("INTIAL CONFIG DONE %d", dir_ip);
  	switch (dir_ip) {
      case 0: // do nothing
        break;
  		case 1: // forward
  			cmd_msg.linear.x = LIN_VEL;
        // ROS_INFO("UP");
        break;
  		case 2: // backward
  			cmd_msg.linear.x = -LIN_VEL;
        // ROS_INFO("DOWN");
        break;
  		case 4: // clockwise and right
//  			cmd_msg.linear.x = LIN_VEL/2;
  			cmd_msg.angular.z = ANG_VEL;
        // ROS_INFO("RIGHT");
        break;
  		case 3: // anti-clockwise and left
//  			cmd_msg.linear.x = LIN_VEL/2;
  			cmd_msg.angular.z = -ANG_VEL;
        // ROS_INFO("LEFT");
        break;
      case 5:
        ros::shutdown();
        break;
 	  } // switch end
    vel_cmd.publish(cmd_msg);
	} // while end
  return 0;
}
