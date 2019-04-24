#include <stdio.h>
#include "read_save_file.h"
#include <stdlib.h>
//#include "cpu_zernike_moment.h"
#include <math.h>
#include "time_count.h"
#include "cuda_zernike_moment.h"
//#include <unistd.h>
#include <Windows.h>
//#include <string.h>

#include<opencv2\opencv.hpp>  

using namespace cv;
using namespace std;

int main()
{
	struct znk_mod zm;
	struct moment_para moment_p;

	Mat img;
	string imgpath = "tiffany.tif";
	//Mat img(512, 512, CV_8UC1);
	
	img = imread(imgpath, 1);

	if (img.rows == img.cols)
	{
		moment_p.pixel_size = img.rows;
		printf("pixel_size is %d \n", img.rows);
		printf("channel is %d , and step is %d\n ", img.depth(), img.channels());
	}
	else
	{
		printf("image width and height did not same\n");
		return 0;
	}

	
	//img.cols;

	//imshow("img", img);
    //waitKey(0);
	//memcpy(yourMat.data, YourData, 1024 * 800 * (unsined char));
	int * image = (int *)malloc(sizeof(int )* moment_p.pixel_size * moment_p.pixel_size);



	printf("test0\n");
	 for(int i = 0 ;i<moment_p.pixel_size;i++)
		 for (int j = 0; j < moment_p.pixel_size; j++)
		 {
			 image[j + moment_p.pixel_size * i] = img.at<Vec3b>(i, j)[0];// img.at<uchar>(i * 3, j);
		 }


	 //SaveIntData("D:\\matlab_workspace\\lidayu_recon\\test.txt", image, moment_p.pixel_size * moment_p.pixel_size);

	 printf("test\n");

	 moment_p.n = 31;
	 moment_p.m = 17;
	 //moment_p.pixel_size = 512;
	 moment_p.cnt = moment_p.pixel_size * moment_p.pixel_size + 1;


	 zm = cuda_zernike_moment(image, moment_p);


	 printf("real is %f and image is %f \n", zm.real_value, zm.image_value);

	 free(image);
	

	return 0;
}
