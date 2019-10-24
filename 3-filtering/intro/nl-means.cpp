#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

double
computeTreshDistance(int sigma){
  //This compute the distance max two pixels of different patchs
  double distanceMax = (-2)*sigma*sigma*log(0.1);
  return distanceMax;
}

void
process(int sigma, const char* imsname, const char* imdname)
{
  //Check the existence of the file, if the file doesn't exist the programme stop
  fstream infile(imsname);
  if (infile.good() == false){
    cerr<<"The file doesn't exist. Check the location of the file\n"<<endl;
    exit(EXIT_FAILURE);
  }
  cout<< "\n############### exercice : nl-means ##############\n"<<endl;
  //Read the image and display it
  Mat ims = imread(imsname, 0);
  imshow("Initial",ims);

  Size s = ims.size();
  cout<<"Width : "<<s.height<<"  Height : "<<s.width<<endl;

  //Variables declarations and initialization
  Mat imd(s,CV_8UC1);
  // According to author the patch tall should be 7*7. We can deduce r=3
  int patch_radius = 3;
  //According to author the window tall should be 11*11. We can deduce r=5
  int window_radius = 5;
  double distance_max = computeTreshDistance(sigma)*(2*patch_radius+1)*(2*patch_radius+1);
  int patchs_sum, sum_w, sum_w_means, pi, pj, qi, qj, Ip, Iq, nb_in_patch=0;
  double w;

  for(int i=0; i<s.height; i++){
    for(int j=0; j<s.width; j++){
      pi=i;
      pj=j;
      sum_w=0;
      sum_w_means=0;
      for(int l=-window_radius; l<=window_radius; l++){
        for(int m=-window_radius; m<=window_radius; m++){
          nb_in_patch=0;
          patchs_sum =0;
          w=0;
          if(i+l>=0 && j+m>=0 && i+l<s.height && j+m<s.width){
            qi=i+l;
            qj=j+m;
            for(int u=-patch_radius; u<=patch_radius; u++){
              for(int v=-patch_radius; v<=patch_radius; v++){
                if(qi+u>=0 && qj+v>=0 && qi+u<s.height && qj+v<s.width){
                    Ip = ims.at<uchar>(pi+u,pj+v);
                    Iq = ims.at<uchar>(qi+u,qj+v);
                    patchs_sum +=(Ip-Iq)*(Ip-Iq);
                    nb_in_patch+=1;
                }
              }
            }
            if(patchs_sum <= distance_max){
              w = exp((-patchs_sum/nb_in_patch)/(2*sigma*sigma));
              sum_w += w;
              sum_w_means+=w*ims.at<uchar>(qi,qj);
            }
          }
        }
      }
      imd.at<uchar>(pi,pj)=sum_w_means/sum_w;
    }
  }
  imshow(imdname,imd);
  imwrite(imdname,imd);
  waitKey(0);
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
