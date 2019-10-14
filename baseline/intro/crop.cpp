#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

void
process(const char* imsname, int i0, int j0, int w, int h)
{
	cout<< "\n############### exercice : crop ##############\n\n"<<endl;
	Mat ims = imread(imsname);
	//Make a hand made crop on the image and save the crop image
	Mat croped_image(h, w, CV_8UC3);

	for (int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			croped_image.at<Vec3b>(i,j) = ims.at<Vec3b>(i0 + i, j0 + j);
		}
	}
	imwrite("crop.png",croped_image);
	//Make a crop image using the Rect function and save the crop image
	Mat croped_image_auto = ims(Rect(j0,i0,w,h));
	imwrite("crop-cv.png",croped_image_auto);
	
	//Create a image to compare the both crop method used
	Mat compare_crop = croped_image - croped_image_auto;
	imshow("diff=((crop)-(crop-cv))", compare_crop);
	waitKey(0);

}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname i0 j0 w h\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 5
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
  return EXIT_SUCCESS;
}
