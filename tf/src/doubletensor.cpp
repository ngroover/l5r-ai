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
            printf("%f", *data);
         }
         else
         {
            printf("%f, ", *data);
         }
         data++;
      }
      for(int j=0;j<totalDims;j++)
      {
         printf("]");
      }
      printf("\n");
   }
   else if(totalDims == 0)
   {
      printf("%f\n", *data);
   }
}

void DoubleTensor::copyTo(double *array, int size)
{
   double *data = (double *)TF_TensorData(tensor);
   int totalSize=getSize();

   // don't let totalSize overrun the buffer
   if( size < totalSize)
   {
      printf("Total tensor size is bigger than expected");
      totalSize = size;
   }
   memcpy(array, (double *)TF_TensorData(tensor), totalSize * sizeof(double));
}

int DoubleTensor::getSize()
{
   int totalDims=TF_NumDims(tensor);
   int totalSize=1;
   if(totalDims > 0)
   {
      for(int i=totalDims-1;i>=0;i--)
      {
         totalSize *= TF_Dim(tensor, i);
      }
   }
   return totalSize;
}

double *DoubleTensor::getData()
{
   return (double *)TF_TensorData(tensor);
}
