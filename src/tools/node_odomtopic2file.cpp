#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/TransformStamped.h"
#include "nav_msgs/Odometry.h"
#include <fstream>

using namespace  std;

std::ofstream fd;

//Call Back Function of motion captrure system
void callback(const nav_msgs::OdometryConstPtr& msg)
{
    fd << setprecision(6)
         << msg->header.stamp << " "
         << setprecision(9)
         << msg->pose.pose.position.x << " "
         << msg->pose.pose.position.y << " "
         << msg->pose.pose.position.z << " "
         << msg->pose.pose.orientation.w << " "
         << msg->pose.pose.orientation.x << " "
         << msg->pose.pose.orientation.y << " "
         << msg->pose.pose.orientation.z << std::endl;
}
//有关输出的在bag.launch 的文件里面设置，有两个odom可以保存，分别是gt和icp+text的，也就是真值和所提出的方法的。
int main(int argc, char **argv)
{
    ros::init(argc, argv, "topic2file");
    ros::NodeHandle n("~");
    std::string filepath;

    n.getParam("filepath", filepath);
    fd.open(filepath.c_str());

    ros::Subscriber sub = n.subscribe("odom", 10, callback);
    // cout<< "filepath:========="<<filepath<<endl;

    ros::spin();

    return 0;
}
