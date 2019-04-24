#include <cuda_runtime.h>
#include "cuda_zernike_moment.h"
#include <stdio.h>
#include "base_cuda.h"
#include "reduction.h"
#include "time_count.h"
//#include "cpu_zernike_moment.h"
#include <math.h>


__device__ double device_factorial(int n)
{
	double value = 1;
	for (int i = 1; i <= n; i++)
	{
		value = value * i;
	}
	return value;
}//*/

__device__ double device_radial_poly(double r, int n, int m)
{
	double rad = 0;
	double c;
	double den;

	//for(int s = 0;s<=(n-abs(m))/2; s++)   //是否加1 不一定
	for (int s = 0; s <= (n - m) / 2; s++)   //是否加1 不一定
	{
		//den =  device_factorial(s) * device_factorial((n+fabs((double)m))/2-s) * device_factorial((n-fabs((double)m))/2-s);
		den = device_factorial(s) * device_factorial((n + (double)m) / 2 - s) * device_factorial((n - (double)m) / 2 - s);
		//den =  c_factorial[s] * c_factorial[(n+m)/2-s] * c_factorial[(n-m)/2-s];

		c = pow((double)-1, (double)s) * device_factorial(n-s)/den;
		//c = pow((double)-1, (double)s) * c_factorial[n - s] / den;
		rad = rad + c * pow(r, n - 2 * s);
	}
	return rad;
}



__global__ void moment_map_kernel(int * d_p, double * d_real_map, double * d_image_map, moment_para para)
{
	const int tid = blockDim.x * blockIdx.x + threadIdx.x;   //表示总的

	int i, j;
	double x, y;
	double r, theta;
	double R;
	double cent_position;
	double rad;
	double real_temp;
	double image_temp;
	double p;

	R = para.pixel_size / 2;
	cent_position = R - 0.5;

	i = tid % para.pixel_size;   //表示列， 代表x
	j = tid / para.pixel_size;   //表示行， 代表y

	x = i - cent_position;
	y = cent_position - j;// j-cent_position;    // 注意此处 y需要翻转
	r = sqrt(x*x/2 + y*y/2) / R;
	//r = r / sqrt(2);
	theta = atan2(y, x);
	__syncthreads();
	if (r<1)
	{
		rad = device_radial_poly(r, para.n, para.m);

		real_temp = rad * cos(para.m*theta) * d_p[tid];
		image_temp = -rad * sin(para.m*theta) * d_p[tid];
	}
	else
	{
		real_temp = 0;
		image_temp = 0;
	}

	d_real_map[tid] = real_temp;
	d_image_map[tid] = image_temp; //real image 颠倒顺序结果正确？？？？？

}



extern "C" void calc_znk_moment(int * d_p, double * d_real_map, double * d_image_map, struct moment_para para)
{
	int thread_num = para.thread_num;
	int block_num = para.pixel_size * para.pixel_size / thread_num;

	moment_map_kernel <<< block_num, thread_num >>> (d_p, d_real_map, d_image_map, para);


	/*switch (para.mode)
	{
	case NO_CONSTANT:
		moment_map_kernel_noconstant << < block_num, thread_num >> > (d_p, d_real_map, d_image_map, para);
		cudaDeviceSynchronize();
		break;
	case FAC_CONSTANT:
		moment_map_kernel_fac << < block_num, thread_num >> > (d_p, d_real_map, d_image_map, para);
		cudaDeviceSynchronize();
		break;
	case NMS_CONSTANT:
		moment_map_kernel_nms << < block_num, thread_num >> > (d_p, d_real_map, d_image_map, para);
		cudaDeviceSynchronize();
		break;
	}*/

	//cudaThreadSynchronize();
}
