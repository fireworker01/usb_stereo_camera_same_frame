#include <ros/ros.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/CameraInfo.h>
#include <math.h>

using namespace std;
using namespace cv;

sensor_msgs::CameraInfo getCameraInfo(void){        // extract cameraInfo.
    sensor_msgs::CameraInfo cam;

    vector<double> D{0.0131, -0.0582, -0.0005, 0.0050, 0.000000};
    boost::array<double, 9> K = {
        754.3377,         0,  601.3630,
         0,  406.8714,  171.6567,
         0,         0,    1.0000  
    };
    
     boost::array<double, 12> P = {
        762.1327212923846, 0, 599.483642578125, 0,
 	0, 762.1327212923846, 325.0535736083984, 0,
 	0, 0, 1, 0
    };
    boost::array<double, 9> r = {1, 0, 0, 0, 1, 0, 0, 0, 1};

    cam.height = 720;
    cam.width = 1280;
    cam.distortion_model = "plumb_bob";
    cam.D = D;
    cam.K = K;
    cam.P = P;
    cam.R = r;
    cam.binning_x = 0;
    cam.binning_y = 0;
    cam.header.frame_id = "camera_info";  
    cam.header.stamp = ros::Time::now();
    cam.header.stamp.nsec = 0;
    return cam;
}

int main(int argc, char** argv) {

  ros::init(argc, argv, "camera_info");  
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<sensor_msgs::CameraInfo>("/camera/camera_info", 1000);  
  sensor_msgs::CameraInfo camera_info_dyn;
  ros::Rate rate(1); 

  while (ros::ok())
  {
      camera_info_dyn = getCameraInfo();
      pub.publish(camera_info_dyn); 
      rate.sleep();
  }
    ros::spin();
    return 0;
}


