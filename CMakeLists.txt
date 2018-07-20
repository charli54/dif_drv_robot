cmake_minimum_required(VERSION 2.8.3)
project(dif_drv_robot)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  controller_manager
  roscpp
  rospy
  std_msgs
  tf
)





###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES dif_drv_robot
  CATKIN_DEPENDS controller_manager roscpp rospy std_msgs
#  DEPENDS system_lib 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)


## Declare a C++ library
 add_library(hardwareInterface src/hardware_interface.cpp
 )

add_executable(${PROJECT_NAME}_node src/controller.cpp)

 add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(
	${PROJECT_NAME}_node
	hardwareInterface
  	${catkin_LIBRARIES}
 )


#############
## Install ##
#############

## Mark cpp header files for installation
 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h *.hpp"
   PATTERN ".svn" EXCLUDE
 )

