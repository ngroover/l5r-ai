#include "doubletensor.h"
#include <tensorflow/c/c_api.h>
#include <string.h>
#include <stdio.h>

DoubleTensor::DoubleTensor(const int64_t *dims,
   const int64_t num_dims,
   const double* data)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_DOUBLE, dims, num_dims, sizeof(double) * num_values);
  memcpy(TF_TensorData(tensor), data, sizeof(double) * num_values);
}

DoubleTensor::DoubleTensor(const int64_t *dims, const int64_t num_dims)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_DOUBLE, dims, num_dims, sizeof(double) * num_values);
}

DoubleTensor::DoubleTensor()
{
   tensor = NULL;
}

DoubleTensor::~DoubleTensor()
{
   if(tensor != NULL)
   {
      TF_DeleteTensor(tensor);
   }
}

void DoubleTensor::print()
{
   double *data = (double *)TF_TensorData(tensor);
   for(int n=0;n<TF_NumDims(tensor);n++)
   {
      printf("[");
      for(int i=0;i<TF_Dim(tensor, n);i++)
      {
         printf("%f, ", *data);
         data++;
      }
      printf("]\n");
   }
}
