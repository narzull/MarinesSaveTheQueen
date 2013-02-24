#include "../include/api/WebcamManager.hpp"
#include "../include/api/Tools.hpp"
#include "../include/api/Application.hpp"
#include <string>
#include <iostream>
namespace api{
  
  WebcamManager::WebcamManager(){
    m_MarkerSize = -1;
  }
  
  bool WebcamManager::initWebcamManager(int argc, char **argv){
    std::cout << "---------------------------------" << std::endl;
    std::cout << "WEBCAM INIT : Opening the webcam" << std::endl;
    //First checking
    if (argc != 4) {
        cerr<<"FAILURE : Invalid number of arguments"<<endl;
        cerr<<"Usage: cam_id  intrinsics.yml   marker_size "<<endl;
        return false;
    }
    
    //Getting the arguments
    int inputVideo= atoi(argv[1]);
    string intrinsicFile=argv[2];
    float markerSize = atof(argv[3]);
    
    //Second checking
    if(inputVideo < 0 || markerSize < 0){
        cerr<<"FAILURE : Invalid arguments"<<endl;
        cerr<<"Usage: cam_id and marker_size must be > 0 "<<endl;
        return false;
    }
    
    //Init variables
    m_CameraID = inputVideo;
    m_MarkerSize = markerSize;
    
    //Init the capturer
    m_Capturer.open(m_CameraID);
    if (!m_Capturer.isOpened())
    {
        cerr<<"FAILURE : Invalid arguments"<<endl;
        cerr<<"Usage: cam_id => couldn't open the camera "<<endl;
	return false;
    }
    
    //Init the camera parameters
    m_Parameters.readFromXMLFile(intrinsicFile);
    m_Capturer >> m_CurrentImage;
    m_Parameters.resize(m_CurrentImage.size());
    std::cout << "SUCCESS : Webcam manager initialized" << std::endl;
    return true;
  }
  
  cv::Mat * WebcamManager::grabCurrentImage(){
        //capture image
        m_Capturer.grab();
        m_Capturer.retrieve(m_CurrentImage);
        m_CurrentTransformedImage.create(m_CurrentImage.size(),CV_8UC3);
        //transform color that by default is BGR to RGB because windows systems do not allow reading BGR images with opengl properly
        cv::cvtColor(m_CurrentImage,m_CurrentImage,CV_BGR2RGB);
        //remove distorion in image
        //cv::undistort(m_CurrentImage,m_CurrentTransformedImage, m_Parameters.CameraMatrix, m_Parameters.Distorsion);
        //resize the image to the size of the GL window
        //cv::resize(m_CurrentTransformedImage,m_ResizedImage,cv::Size(Application::m_WINDOW_WIDTH, Application::m_WINDOW_HEIGHT));
	cv::resize(m_CurrentImage,m_ResizedImage,cv::Size(Application::m_WINDOW_WIDTH, Application::m_WINDOW_HEIGHT));
	return & m_ResizedImage;
  }
  
  void WebcamManager::grabMarkersInCurrentImage(std::vector<aruco::Marker> & markers){
    //Undistort the images
    cv::undistort(m_CurrentImage,m_CurrentTransformedImage, m_Parameters.CameraMatrix, m_Parameters.Distorsion);
    //Detect the markers
    m_Detector.detect(m_CurrentTransformedImage, markers, m_Parameters.CameraMatrix, cv::Mat(), m_MarkerSize);
  }
  
  glm::mat4 WebcamManager::getProjectionMatrix(unsigned int appliWidth, unsigned int appliHeight){
    double projection[16];
    glm::mat4 projectionMatrix;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "WEBCAM PROJECTION : Building the webcam projection matrix" << std::endl;
    std::cout << "Image size : " << m_CurrentImage.size().width << " " << m_CurrentImage.size().height << std::endl;
    std::cout << "Application size : " << appliWidth << " " << appliHeight << std::endl;
    m_Parameters.glGetProjectionMatrix(m_CurrentImage.size(), cv::Size(appliWidth, appliHeight), projection, 0.05, 100, false);
    tools::transformToMatrix(projection, projectionMatrix);
    return projectionMatrix;
  }
}//namespace api