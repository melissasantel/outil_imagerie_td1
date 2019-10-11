#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

void
process(const char* imsname, const char* imdname)
{
  fstream infile(imsname);
  if (infile.good() == false){
    cerr<<"The file doesn't exist. Check the location of the file\n"<<endl;
    exit(EXIT_FAILURE);
  }
  cout<< "\n############### exercice : readwriteshow ##############\n"<<endl;
  Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
  Size s = ims.size();
  cout << "Image size H="<<s.height <<" W=" << s.width << "\n\n"<< endl;
  imshow(imsname, ims);

  waitKey(0);

  Mat imd(100, 200, CV_8UC3, Scalar(255,0,255));

  imshow(imdname, imd);
  waitKey(0);
  imwrite(imdname, imd);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname imdname\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2]);
  return EXIT_SUCCESS;
}
