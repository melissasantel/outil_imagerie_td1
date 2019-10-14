#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int g_slider_position;
int g_slider_position_max;
VideoCapture cap;
//event based function for the slide bar
void
on_slidebar(int, void*)
{
 printf("go to frame number = %d\n", g_slider_position);
 cap.set(CV_CAP_PROP_POS_FRAMES, g_slider_position);
}

void
process(const char* vidname)
{
  cout<< "\n############### exercice : video-player ##############\n"<<endl;

  fstream infile(vidname);
  //Check the existence of the video
  if (infile.good() == false){
    cerr<<"The file doesn't exist. Check the location of the file\n"<<endl;
    exit(EXIT_FAILURE);
  }
  //Check if the video can be open
  if(vidname)
    cap.open(vidname);
  else
    printf("Please check your file\n");

  double fps =  cap.get(CV_CAP_PROP_FPS);
  double frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  double frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  double nb_of_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
  double current_frame;

  g_slider_position=0;
  g_slider_position_max=nb_of_frame;

  cout << "fps=" <<fps <<endl;
  cout << "width=" << frame_width << ", height=" << frame_height <<endl;
  cout << "total frames= " << nb_of_frame <<"\n\n"<<endl;

  Mat frame;
  namedWindow(vidname,1);
  //Create a slide bar
  createTrackbar("Slide bar", vidname, &g_slider_position, g_slider_position_max, on_slidebar);

  //Play the video on the namedWindow until the video is finished or a press key
  while(1){
    current_frame = cap.get(CV_CAP_PROP_POS_FRAMES);
    std::stringstream ss;
    ss << "Frame = " << current_frame;
    string showing_frame = ss.str();

    cap >> frame;
    if(!frame.data)
        break;

    putText(frame,showing_frame, Point2f(50,50), FONT_HERSHEY_PLAIN, 1, Scalar(255,255,255,255));
    imshow(vidname,frame);

    if(current_frame>=1000){
      if(g_slider_position>=1000)
        cap.set(CV_CAP_PROP_POS_FRAMES, g_slider_position);
      else
        cap.set(CV_CAP_PROP_POS_FRAMES, 1000);
    }
    if(waitKey(30)>=0)
      break;
  }

  cap.release();
}

void
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;
}
