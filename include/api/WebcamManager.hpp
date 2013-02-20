#ifndef __WEBCAMMANAGER_HPP__
#define __WEBCAMMANAGER_HPP__

#include <aruco/aruco.h>

//Webcam Manager class
namespace api {
class WebcamManager{
public:
    //Constructor
    WebcamManager();
    //Public methods
    bool initWebcamManager(int argc, char **argv);
    cv::Mat * grabCurrentImage();
private:
    unsigned int m_CameraID;
    float m_MarkerSize;
    cv::VideoCapture m_Capturer;
    aruco::CameraParameters m_Parameters;
    cv::Mat m_CurrentImage;
    cv::Mat m_CurrentTransformedImage;
    cv::Mat m_ResizedImage;
};
} // namespace api
#endif // __WEBCAMMANAGER_HPP__
