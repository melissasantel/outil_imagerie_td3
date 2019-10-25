#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

double
computeTresh(int sigma){
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
  //Read the image
  Mat ims = imread(imsname, 0);
  Size s = ims.size();
  cout<<"Wait a minute.. "<<endl;

  //Variables declarations and initialization
  Mat imd(s,CV_8UC1);
  // According to author the patch tall should be 7*7. We can deduce r=3
  int patch_radius = 3;
  //According to author the window tall should be 11*11. We can deduce r=5
  int window_radius = 5;
  double distance_max = computeTresh(sigma)*(2*patch_radius+1)*(2*patch_radius+1);
  int patchs_sum, pi, pj, qi, qj, Ip, Iq, nb_in_patch=0;
  double w, sum_w, sum_w_means;

  //Compute I'(p)
  for(int i=0; i<s.height; i++){
    for(int j=0; j<s.width; j++){
      //Retrieve the pixel p coordinates
      pi=i;
      pj=j;
      sum_w=0;//Denominator to calculate I'(p)
      sum_w_means=0;//Numerator to calculate I'(p)
      //Retrieve the pixel p neighbors coordinates
      for(int l=-window_radius; l<=window_radius; l++){
        for(int m=-window_radius; m<=window_radius; m++){
          nb_in_patch=0;
          patchs_sum =0;
          w=0;
          //Check if we are still in the image
          if(i+l>=0 && j+m>=0 && i+l<s.height && j+m<s.width){
            qi=i+l;
            qj=j+m;
            //Retrieve the patch coordinates of p and q
            for(int u=-patch_radius; u<=patch_radius; u++){
              for(int v=-patch_radius; v<=patch_radius; v++){
                //Check if we are still in the image
                if(qi+u>=0 && qj+v>=0 && qi+u<s.height && qj+v<s.width){
                    Ip = ims.ptr<uchar>(pi+u)[pj+v];
                    Iq = ims.ptr<uchar>(qi+u)[qj+v];
                    patchs_sum +=(Ip-Iq)*(Ip-Iq);
                    nb_in_patch+=1;
                }
              }
            }
            //Check if the patchs_sum value return a value
            //For the one the exp is null
            if(patchs_sum <= distance_max){
              w = exp((-patchs_sum/nb_in_patch)/(2*sigma*sigma));
              sum_w += w;
              sum_w_means+=w*ims.ptr<uchar>(qi)[qj];
            }
          }
        }
      }
      //Compute the I'(p) value
      imd.ptr<uchar>(pi)[pj]=sum_w_means/sum_w;
    }
  }
  imwrite(imdname,imd);
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
