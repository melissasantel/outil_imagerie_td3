#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

void
process(int r, const char* imsname, const char* imdname)
{
  (void) imdname;
  //Check the existence of the file, if the file doesn't exist the programme stop
  fstream infile(imsname);
  if (infile.good() == false){
    cerr<<"The file doesn't exist. Check the location of the file\n"<<endl;
    exit(EXIT_FAILURE);
  }
  cout<< "\n############### exercice : median-filter ##############\n"<<endl;
  //Read the image and display it whit the size
  Mat ims = imread(imsname, 0);
  Size s = ims.size();

  //Initialize variables
  Mat imd(s,CV_8UC1);
  Mat imd_median_ocv(s,CV_8UC1);
  Mat diff_median(s,CV_8UC1);
  int median_value;

  //Compute the median value of the pixel neighbor
  for(int i=0;i<s.height; i++){
    for(int j=0; j<s.width; j++){
      vector<int>p_neighbor;
      for(int l=-r; l<=r; l++){
        for(int m=-r; m<=r; m++){
          if(i+l>=0 && j+m>=0 && i+l<s.height && j+m<s.width){
            p_neighbor.push_back(ims.at<uchar>(i+l,j+m));
          }
        }
      }
      size_t n_size = p_neighbor.size();
      if (n_size == 0){
        median_value = ims.at<uchar>(i,j);
      }
      else{
        sort(p_neighbor.begin(), p_neighbor.end());
        if (n_size % 2 == 0){
          median_value = (p_neighbor[n_size / 2 - 1] + p_neighbor[n_size / 2]) / 2;
        }
        else{
          median_value = p_neighbor[n_size / 2];
        }
      }
      imd.at<uchar>(i,j) = median_value;
    }
  }

  imwrite(imdname,imd);

  medianBlur(ims,imd_median_ocv,2*r+1);
  imshow("res-ocv",imd_median_ocv);
  imwrite("res-ocv.png",imd_median_ocv);
  waitKey(0);
  diff_median=imd-imd_median_ocv;
  imshow("diff-median-method",diff_median);
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
