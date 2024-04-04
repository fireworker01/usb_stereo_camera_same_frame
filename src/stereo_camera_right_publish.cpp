#include <ros/ros.h>  
#include <image_transport/image_transport.h>  
#include <opencv2/highgui/highgui.hpp>  
#include <cv_bridge/cv_bridge.h>  
#include <sstream> 
 
int main(int argc, char** argv)  
{  
    if(argv[1] == NULL)   
    {  
        ROS_INFO("argv[1]=NULL\n");  
        return 1;  
    }  
 
    ros::init(argc, argv, "image_publisher");  
    ros::NodeHandle nh;  
    image_transport::ImageTransport it(nh);  
    image_transport::Publisher pub = it.advertise("camera/image", 1);  
 
    std::istringstream video_sourceCmd(argv[1]);  
    int video_source;  
    if(!(video_sourceCmd >> video_source))   
    {  
        ROS_INFO("video_sourceCmd is %d\n",video_source);  
        return 1;  
    }  
 
    cv::VideoCapture cap(video_source);  
    if(!cap.isOpened())   
    {  
        ROS_INFO("can not opencv video device\n");  
        return 1;  
    }  
    cv::Mat frame;  
    sensor_msgs::ImagePtr msg;  

 
    ros::Rate loop_rate(5);  
    while (nh.ok()) 
    {  
        cap >> frame;  
        cv::Mat rightImage = frame(cv::Rect(1280, 0, 1280, 720)); //Only display right img
        if(!frame.empty()) 
        {  
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", rightImage).toImageMsg(); 
            msg->header.frame_id = "camera";
            msg->header.stamp = ros::Time::now();
    	    msg->header.stamp.nsec = 0; 
            pub.publish(msg);  
            //cv::Wait(1);  
    	}  
    }
    
    ros::spinOnce();  
    loop_rate.sleep();  
}  
