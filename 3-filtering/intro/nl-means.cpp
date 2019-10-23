#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

void
process(int sigma, const char* imsname, const char* imdname)
{
  (void) sigma;
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
  int radius = 3;
  int
  for(int i=0; i<s.height; i++){
    for(int j=0; j<s.width; j++){
      for(int l=-radius; l<=radius; l++){
        for(int m=-radius; m<=radius; m++){
          if(i+l>=0 && j+m>=0 && i+l<s.height && j+m<s.width){

          }
        }
      }
    }
  }

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
