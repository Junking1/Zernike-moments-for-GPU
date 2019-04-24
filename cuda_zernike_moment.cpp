#include "cuda_zernike_moment.h"
//#include "cpu_zernike_moment.h"
#include "base_cuda.h"
//#include "kernel_zernike_moment.cu"
#include <stdio.h>
#include <stdlib.h>
#include "read_save_file.h"
#include "time_count.h"
//#include <unistd.h>
#include <Windows.h>
#include <math.h>

FILE * fp = NULL;

znk_mod cuda_zernike_moment(int *p, struct moment_para para)
{
	time_count tt;

	int * d_p;
	
	double * d_real_map;
	double * d_image_map;
	gpu_malloc((void **)&d_real_map, sizeof(double) * para.pixel_size * para.pixel_size);
	gpu_malloc((void **)&d_image_map, sizeof(double) * para.pixel_size * para.pixel_size);

	znk_mod zm;

	gpu_malloc((void **)&d_p, para.pixel_size*para.pixel_size * sizeof(int));

	copy2gpu(p, d_p, para.pixel_size*para.pixel_size * sizeof(int));


	tt.startcount();

	printf("test11\n");
	calc_znk_moment(d_p, d_real_map, d_image_map, para);
	zm.real_value = reduce_double(d_real_map, para.pixel_size * para.pixel_size, 0)* (para.n + 1) / para.cnt;
	zm.image_value = reduce_double(d_image_map, para.pixel_size * para.pixel_size, 0)* (para.n + 1) / para.cnt;
	printf("test12\n");
	tt.endcount();
	//fprintf(para.fp, "%d %d %d %d\n", para.pixel_size, para.n, para.m, tt.gettime());


	double * test = (double *)malloc(sizeof(double) *para.pixel_size * para.pixel_size);
	copy2host(test, d_real_map, sizeof(double) * para.pixel_size * para.pixel_size);

	SaveDoubleData("D:\\matlab_workspace\\lidayu_recon\\test.txt", test, para.pixel_size * para.pixel_size);


	gpu_free(d_p);
	gpu_free(d_real_map);
	gpu_free(d_image_map);

	return  zm;
}
