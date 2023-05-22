#include <termios.h>
#include <ros/ros.h>

int ReturnInputKey()
{
  struct termios org_term;

  char input_key = 0;

  tcgetattr(STDIN_FILENO, &org_term);

  struct termios new_term = org_term;

  new_term.c_lflag &= ~(ECHO | ICANON);

  new_term.c_cc[VMIN] = 0;
  new_term.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

  read(STDIN_FILENO, &input_key, 1);

  tcsetattr(STDIN_FILENO, TCSANOW, &org_term);

  return input_key;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robot_controller_node");
  ros::NodeHandle n;

  int return_key = 0;

  ros::Rate loop_rate(60);

  while (ros::ok())
  {
    return_key = ReturnInputKey();
    // W 입력시 전진
    if(return_key == 119 | return_key == 87)
    {
      ROS_INFO("Input W");
    }
    // A 입력시 좌회전
    if(return_key == 97 | return_key == 65)
    {
      ROS_INFO("Input A");
    }
    // S 입력시 후진
    if(return_key == 115 | return_key == 83)
    {
      ROS_INFO("Input S");
    }
    // D 입력시 우회전
    if(return_key == 100 | return_key == 68)
    {
      ROS_INFO("Input D");
    }
    // X 입력시 정지
    if(return_key == 120 | return_key == 88)
    {
      ROS_INFO("Input X");
    }
    // ESC 입력시 종료
    if(return_key == 27) break;


    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;

}


