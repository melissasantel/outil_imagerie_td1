#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

#include <time.h>

using namespace cv;
using namespace std;

void
process(const char* imsname)
{
  Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
  Size s = ims.size();
  cout << "Image size H="<<s.height <<" W=" << s.width << endl;
  clock_t t;
  t=clock();
  ims.at<Vec3b>(400,300) = (1/64)*ims.at<Vec3b>(400,300)*64+64/2;
  t=clock()-t;
  printf("Access with ’at’ method ... %f.\n",((float)t)/CLOCKS_PER_SEC);

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
