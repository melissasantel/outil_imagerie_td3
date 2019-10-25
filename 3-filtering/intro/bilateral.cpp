#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int
distance_computation(int sigma){
  //This compute the distance max two pixels of different patchs
  int x=0;
  double g_value;
  do{
    g_value=exp(-pow(x,2)/(2*pow(sigma,2)));
    x++;
  } while (g_value>0.1);

  return x-1;
}

void
process(int sigma_s, int sigma_g, const char* imsname, const char* imdname)
{
  //Check the existence of the file, if the file doesn't exist the programme stop
  fstream infile(imsname);
  if (infile.good() == false){
    cerr<<"The file doesn't exist. Check the location of the file\n"<<endl;
    exit(EXIT_FAILURE);
  }
  cout<< "\n############### exercice : bilateral ##############\n"<<endl;
  //Read the image
  Mat ims = imread(imsname, 0);

  Size s = ims.size();

  //Variables declaration and initialization
  Mat imd(s,CV_8UC1);
  Mat imd_ocv(s,CV_8UC1);
  Mat diff_imd(s,CV_8UC1);
  int s_distance = distance_computation(sigma_s);
  int p,q,pi,pj,qi,qj,distance_pq=0;
  double sum_num, sum_denom =0;

  float Gs_values[s_distance];
  float Gc_values[256];
  //Compute the value in advance of Gs
  for(int c=0; c<=s_distance; c++){
    Gs_values[c] = exp(-pow(c,2)/(2*pow(sigma_s,2)));
  }
  //Compute the value in advance of Gc
  for(int a=0; a<256; a++){
    Gc_values[a] = exp(-pow(a,2)/(2*pow(sigma_g,2)));
  }

  for(int i=0; i<s.height; i++){
    for(int j=0; j<s.width; j++){
      //Retrieve the pixel p coordinates
      sum_num=0;
      sum_denom =0;
      pi=i;
      pj=j;
        //Retrieve the pixel p neighbors coordinates
      for(int l=-s_distance; l<=s_distance; l++){
        for(int m=-s_distance; m<=s_distance; m++){
          if(i+l>=0 && j+m>=0 && i+l<s.height && j+m<s.width){
            qi=i+l;
            qj=j+m;
            distance_pq = abs(pi-qi)+ abs(pj-qj);
            //Check if the distance of pixel is include in the circle
            if( distance_pq<= s_distance){
              p=ims.ptr<uchar>(pi)[pj];
              q=ims.ptr<uchar>(qi)[qj];
              sum_num+=Gs_values[distance_pq]*Gc_values[abs(p-q)]*q;
              sum_denom +=Gs_values[distance_pq]*Gc_values[abs(p-q)];
            }
          }
        }
      }
      imd.ptr<uchar>(pi)[pj]=sum_num/sum_denom;
    }
  }
  imwrite(imdname,imd);
  bilateralFilter(ims,imd_ocv,s_distance,sigma_g,sigma_s,BORDER_DEFAULT);
  imshow("res_ocv_method",imd_ocv);
  diff_imd = imd-imd_ocv;
  imshow("Difference-bilateral-method",diff_imd);
  waitKey(0);

}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname imdname\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 4
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
  return EXIT_SUCCESS;
}
