# arl_remote_test

# install ncurses in order to build and use the husky_keyboard_control package
sudo apt-get install libncurses5-dev libncursesw5-dev

# while in the arl_remote_test top level directory, build using
catkin_make

# launching the keyboard control demo:
rosrun husky_keyboard_control husky_keyboard_control

# launching the autonomous navigation demo:
After launching Phoenix and Unity with the husky robot in the rellis environment, run each of the following commands, in order, each in separate terminals:

roslaunch vicon_bridge vicon.launch, 
rosrun husky_vicon_link husky_vicon_link, 
rosrun simulated_gps simulated_gps, 
rosrun simulated_gps sim_gps_processor, 
rosrun algorithm_3 a_star, 
rosrun algorithm_3 mr_algorithm_3, 

Navigation can be cancelled at any time using cntrl+c in the mr_algorithm_3 terminal.
