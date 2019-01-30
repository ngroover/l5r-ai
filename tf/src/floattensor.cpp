#include "floattensor.h"
#include <tensorflow/c/c_api.h>
#include <string.h>
#include <stdio.h>

FloatTensor::FloatTensor(const int64_t *dims,
   const int64_t num_dims,
   const float* data)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_FLOAT, dims, num_dims, sizeof(float) * num_values);
  memcpy(TF_TensorData(tensor), data, sizeof(float) * num_values);
}

FloatTensor::FloatTensor(const int64_t *dims, const int64_t num_dims)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_FLOAT, dims, num_dims, sizeof(float) * num_values);
}

FloatTensor::FloatTensor()
{
   tensor = NULL;
}

FloatTensor::~FloatTensor()
{
   if(tensor != NULL)
   {
      TF_DeleteTensor(tensor);
   }
}

void FloatTensor::print()
{
   float *data = (float *)TF_TensorData(tensor);
   printf("[");
   for(int n=0;n<TF_NumDims(tensor);n++)
   {
      printf("[");
      for(int i=0;i<TF_Dim(tensor, n);i++)
      {
         printf("%f, ", *data);
         data++;
      }
      printf("]");
   }
   printf("]\n");
}
