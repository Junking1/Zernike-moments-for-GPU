#include "base_cuda.h"
// Includes CUDA
#include <cuda_runtime.h>
// Utilities and timing functions
#include <helper_functions.h>    // includes cuda.h and cuda_runtime_api.h
// CUDA helper functions
#include <helper_cuda.h>         // helper functions for CUDA error check

void copy2gpu(void * h_data, void * d_data, int data_size)
{
	cudaError_t err;
	err = cudaMemcpy(d_data, h_data, data_size, cudaMemcpyHostToDevice);
	if(err!= cudaSuccess)
		{
			printf("copy mem to gpu err!\n");
			DEVICE_RESET
			exit(EXIT_FAILURE);
		}
}


void gpu_malloc(void ** d_data, int data_size)
{
	cudaError_t err;
	err = cudaMalloc((void **) d_data, data_size);
	if(err!= cudaSuccess)
	{
		printf("gpu malloc mem err!\n");
		DEVICE_RESET
		exit(EXIT_FAILURE);
	}
}

void copy2host(void * h_data, void * d_data , int data_size)
{
	cudaError_t err;
	err = cudaMemcpy(h_data, d_data, data_size, cudaMemcpyDeviceToHost);
	if(err!= cudaSuccess)
	{
		printf("gpu malloc mem err!\n");
		DEVICE_RESET
		exit(EXIT_FAILURE);
	}
}

void gpu_free(void * d_data)
{
	cudaFree(d_data);
}
