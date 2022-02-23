cmake_minimum_required(VERSION 3.5.1)
project(husky_keyboard_control)

## Use C++11
add_definitions(--std=c++11)
## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs)
find_package(Curses REQUIRED)
## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS roscpp geometry_msgs
)
## Specify additional locations of header files
include_directories(${catkin_INCLUDE_DIRS})

add_executable(husky_keyboard_control src/husky_keyboard_control.cpp)
target_link_libraries(husky_keyboard_control ${catkin_LIBRARIES} ${CURSES_LIBRARIES})
add_dependencies(husky_keyboard_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} ${CURSES_EXPORTED_TARGETS})

## Mark executables and/or libraries for installation
install(TARGETS husky_keyboard_control
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)