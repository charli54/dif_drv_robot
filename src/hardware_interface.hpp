#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>

class MyRobot : public hardware_interface::RobotHW
{
public:
  MyRobot() 
 { 
   // connect and register the joint state interface
   hardware_interface::JointStateHandle state_handle_a("base_to_roue_gauche", &pos_[0], &vel_[0], &eff_[0]);
   jnt_state_interface.registerHandle(state_handle_a);

   hardware_interface::JointStateHandle state_handle_b("base_to_roue_droite", &pos_[1], &vel_[1], &eff_[1]);
   jnt_state_interface.registerHandle(state_handle_b);

   registerInterface(&jnt_state_interface);

   // connect and register the joint position interface
   hardware_interface::JointHandle pos_handle_a(jnt_state_interface.getHandle("base_to_roue_gauche"), &cmd_[0]);
   jnt_pos_interface.registerHandle(pos_handle_a);
   jnt_vel_interface.registerHandle(pos_handle_a);
   

   hardware_interface::JointHandle pos_handle_b(jnt_state_interface.getHandle("base_to_roue_droite"), &cmd_[1]);
   jnt_pos_interface.registerHandle(pos_handle_b);
   jnt_vel_interface.registerHandle(pos_handle_b);

   registerInterface(&jnt_pos_interface);
   registerInterface(&jnt_vel_interface);
  }


  ros::Time getTime() const {return ros::Time::now();}
  ros::Duration getPeriod() const {return ros::Duration(0.01);}


  void read(){
    //ROS_INFO_STREAM("Commands for joints: " << cmd_[0] << ", " << cmd_[1]);
  }

  void write(){
    //Update pos_ and vel_
    //ROS_INFO_STREAM("Commands for joints: " << vel_[0] << ", " << vel_[1]);
    vel_[0] = cmd_[0];
  }

private:
  hardware_interface::JointStateInterface jnt_state_interface;
  hardware_interface::PositionJointInterface jnt_pos_interface;
  hardware_interface::VelocityJointInterface jnt_vel_interface;
  double cmd_[2];
  double pos_[2];
  double vel_[2];
  double eff_[2];
};