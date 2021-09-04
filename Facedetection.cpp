#include<opencv2/opencv.hpp>
#include<vector>
#include<string>
#include <chrono>
#include<thread>

using namespace cv;
using namespace std;

void Photo(Mat CropImg){
    imshow("Video",CropImg);
    for(int i=0; i<5; i++){
            string path = "Faces\\pic"+to_string(i)+".jpg";
            imwrite(path, CropImg);
            _sleep(3000);
        }
}

int main(){
    double Scale = 2.0;
    CascadeClassifier faceCascade;
    faceCascade.load("opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml");
    VideoCapture cap(0);
    if(!cap.isOpened()){
        return -1;
    }

    for(;;){
        Mat frame, Gray, CropImg;
        cap>>frame;
        cvtColor(frame, Gray, COLOR_BGR2GRAY);
        resize(Gray, Gray, Size(Gray.size().width/Scale, Gray.size().height/Scale));
        vector<Rect> faces;
        faceCascade.detectMultiScale(Gray, faces, 1.1, 3, 0,Size(30,30));
         
        for(Rect area: faces){
            Scalar drawColor = Scalar(0,255,0);
            Rect roi(cvRound(area.x * Scale), cvRound(area.y * Scale), cvRound((area.width - 1) * Scale), cvRound((area.height - 1) * Scale));

            rectangle(frame, roi, drawColor);
            CropImg = frame(roi);
            Photo(CropImg);

        }

        if(waitKey(30)>=0)
        break;

    }
}