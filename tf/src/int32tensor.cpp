#include "int32tensor.h"
#include <tensorflow/c/c_api.h>
#include <string.h>
#include <stdio.h>

Int32Tensor::Int32Tensor(const int64_t *dims,
   const int64_t num_dims,
   const int32_t* data)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_INT32, dims, num_dims, sizeof(int32_t) * num_values);
  memcpy(TF_TensorData(tensor), data, sizeof(int32_t) * num_values);
}

Int32Tensor::Int32Tensor(const int64_t *dims, const int64_t num_dims)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_INT32, dims, num_dims, sizeof(int32_t) * num_values);
}

Int32Tensor::Int32Tensor()
{
   tensor = NULL;
}

Int32Tensor::~Int32Tensor()
{
   if(tensor != NULL)
   {
      TF_DeleteTensor(tensor);
   }
}

void Int32Tensor::print()
{
   int32_t *data = (int32_t *)TF_TensorData(tensor);
   int totalDims=TF_NumDims(tensor);
   int totalSize=1;
   int dimBoundaries[totalDims];
   for(int i=totalDims-1;i>=0;i--)
   {
      totalSize *= TF_Dim(tensor, i);
      dimBoundaries[i] = totalSize;
   }

   bool endLine=false;
   for(int n=0;n < totalSize;n++)
   {
      for(int j=0;j<totalDims;j++)
      {
         if(n % dimBoundaries[j] == 0)
         {
            if(n == 0)
            {
               printf("[");
            }
            else
            {
               endLine=false;
               printf("],\n[");
            }
         }
         if(((n+1) % dimBoundaries[j]) == 0)
         {
            endLine=true;
         }
      }
      if(endLine)
      {
         printf("%d", *data);
      }
      else
      {
         printf("%d, ", *data);
      }
      data++;
   }
   for(int j=0;j<totalDims;j++)
   {
      printf("]");
   }
   printf("\n");
}
