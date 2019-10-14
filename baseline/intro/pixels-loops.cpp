#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

void
process(const char* imsname)
{
  cout<< "\n############### exercice : pixels-loops ##############\n"<<endl;

  //Convert the imsname image to a bigger one for the test
  cout<<"Wait a moment.. The image is being created\n\n"<<endl;
  string ch = "convert -resize 10240 "+string(imsname)+" ../data/lena_color_10000.png";
  system(ch.c_str());

  //Load the created image
  Mat ims = imread("../data/lena_color_10000.png", CV_LOAD_IMAGE_COLOR);
  Size s = ims.size();
  cout << "Image size H="<<s.height <<" W=" << s.width << endl;

  double t;

  //Calculate the time process for pointers
  t = (double)getTickCount();
  for(int i = 0; i < ims.rows; i++){
    Vec3b* ims_coord = ims.ptr<Vec3b>(i);
    for(int j = 0; j < ims.cols; j++){
      for(int c=0; c<3; c++){
        ims_coord[j][c] =(1/64)*ims_coord[j][c]*64+64/2;
      }
    }
  }

  t = ((double)getTickCount() - t)/getTickFrequency();
  printf("Access with pointers ... takes %f.\n",t);


  //Calculate the time process for iterators
  t = (double)getTickCount();
  Mat_<Vec3b>::iterator it = ims.begin<Vec3b>(), itEnd = ims.end<Vec3b>();
  for(; it!= itEnd; ++it){
    for(int c=0; c<3; c++){
      (*it)[c]=(1/64)*(*it)[c]*64+64/2;
    }
  }

  t = ((double)getTickCount() - t)/getTickFrequency();
  printf("Access with iterators ... takes %f.\n",t);


  //Calculate the time process for method at
  t = (double)getTickCount();
  for(int i = 0; i < ims.rows; i++){
    for(int j = 0; j < ims.cols; j++){
      for(int c=0; c<3; c++){
        ims.at<Vec3b>(i,j)[c]=(1/64)*ims.at<Vec3b>(i,j)[c]*64+64/2;
      }
    }
  }
  t = ((double)getTickCount() - t)/getTickFrequency();
  printf("Access with 'at' method ... takes %f.\n",t);

  //Calculate the time process for opencv operator
  t = (double)getTickCount();
  ims = (1/64)*ims*64+64/2;
  t = ((double)getTickCount() - t)/getTickFrequency();
  printf("Access with opencv operator redefinition ... takes %f.\n\n",t);

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
