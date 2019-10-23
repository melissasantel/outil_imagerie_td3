#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

double
computeTreshDistance(int sigma){

}

void
process(int sigma, const char* imsname, const char* imdname)
{
  (void) imdname;
  //Check the existence of the file, if the file doesn't exist the programme stop
  fstream infile(imsname);
  if (infile.good() == false){
    cerr<<"The file doesn't exist. Check the location of the file\n"<<endl;
    exit(EXIT_FAILURE);
  }
  cout<< "\n############### exercice : nl-means ##############\n"<<endl;
  //Read the image and display it whit the size
  Mat ims = imread(imsname, 0);
  Size s = ims.size();

  Mat imd(s,CV_8UC1);
  //According to author the patch tall should be 7*7. We can deduce r=3
  int patch_radius = 3;
  //According to author the window tall should be 11*11. We can deduce r=5
  int window_radius = 5;
  int patchs_sum;
  int pi,pj,qi,qj=0;
  int w;
  int sum_w;
  int sum_w_means;
  // for(int i=0; i<s.height; i++){
  //   for(int j=0; j<s.width; j++){
  //     patchs_sum =0;
  //     pi=i;
  //     pj=j;
  //     w=0;
  //     sum_w=0;
  //     for(int l=-window_radius; l<=window_radius; l++){
  //       for(int m=-window_radius; m<=window_radius; m++){
  //         if(i+l>=0 && j+m>=0 && i+l<s.height && j+m<s.width){
  //           qi=i+l;
  //           qj=j+m;
  //           for(int u=-patch_radius; u<=patch_radius; u++){
  //             for(int v=-patch_radius; v<=patch_radius; u++){
  //               if(i+u>=0 && j+v>=0 && i+u<s.height && j+v<s.width && qi+u>=0 && qj+v>=0 && qi+u<s.height && qj+v<s.width){
  //                 patchs_sum +=pow(ims.at<uchar>(pi+u,pj+v)-ims.at<uchar>(qi+u,qj+v),2);
  //               }
  //             }
  //           }
  //           w = exp((-1)*(patchs_sum/pow(2*patch_radius+1,1))/2*pow(sigma,2));
  //           sum_w += w;
  //           sum_w_means += w*ims.at<uchar>(qi,qj);
  //         }
  //       }
  //     }
  //     cout << sum_w << endl;
  //   }
  // }

}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname imdname\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), argv[2], argv[3]);
  return EXIT_SUCCESS;
}
