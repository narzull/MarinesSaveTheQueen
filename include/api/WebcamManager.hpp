#ifndef __WEBCAMMANAGER_HPP__
#define __WEBCAMMANAGER_HPP__

#include <aruco/aruco.h>
#include <glm/glm.hpp>

//Webcam Manager class
namespace api {
class WebcamManager{
public:
    //Constructor
    WebcamManager();
    //Public methods
    bool initWebcamManager(int argc, char **argv);
    cv::Mat * grabCurrentImage();
    void grabMarkersInCurrentImage(std::vector<aruco::Marker> & markers);
    glm::mat4 getProjectionMatrix(unsigned int appliWidth, unsigned int appliHeight);
private:
    unsigned int m_CameraID;
    float m_MarkerSize;
    cv::VideoCapture m_Capturer;
    cv::Mat m_CurrentImage;
    cv::Mat m_CurrentTransformedImage;
    cv::Mat m_ResizedImage;
    aruco::MarkerDetector m_Detector;
    aruco::CameraParameters m_Parameters;
};
} // namespace api
#endif // __WEBCAMMANAGER_HPP__
