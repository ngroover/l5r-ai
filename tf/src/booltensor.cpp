#include "booltensor.h"
#include <tensorflow/c/c_api.h>
#include <string.h>
#include <stdio.h>

BoolTensor::BoolTensor(const int64_t *dims,
   const int64_t num_dims,
   const bool* data)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_BOOL, dims, num_dims, sizeof(bool) * num_values);
  memcpy(TF_TensorData(tensor), data, sizeof(bool) * num_values);
}

BoolTensor::BoolTensor(const int64_t *dims, const int64_t num_dims)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_BOOL, dims, num_dims, sizeof(bool) * num_values);
}

BoolTensor::BoolTensor()
{
   tensor = NULL;
}

BoolTensor::~BoolTensor()
{
   if(tensor != NULL)
   {
      TF_DeleteTensor(tensor);
   }
}

void BoolTensor::print()
{
   bool *data = (bool *)TF_TensorData(tensor);
   int totalDims=TF_NumDims(tensor);
   int totalSize=1;
   int dimBoundaries[totalDims];
   if(totalDims > 0)
   {
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
            printf("%s", (*data ? "true": "false"));
         }
         else
         {
            printf("%s, ", (*data ? "true": "false"));
         }
         data++;
      }
      for(int j=0;j<totalDims;j++)
      {
         printf("]");
      }
      printf("\n");
   }
}
