#include "stringtensor.h"
#include <tensorflow/c/c_api.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

StringTensor::StringTensor(const int64_t *dims,
   const int64_t num_dims,
   std::list<std::string> strList)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }

  if(strList.size() == num_values)
  {
      TF_Status *status = TF_NewStatus();
     int dimsSize=sizeof(uint64_t)*num_values;
     int strSize=0;
     for(auto str : strList)
     {
        strSize += TF_StringEncodedSize(str.size());
     }
     char buffer[dimsSize+strSize];
     uint64_t *nums = reinterpret_cast<uint64_t*>(buffer);

     char *dataStart = buffer + dimsSize;
     char *dst = dataStart;
     int dst_len = strSize;
     for (auto str : strList)
     {
      *nums = (dst - dataStart);
      nums++;
      int consumed = TF_StringEncode(str.data(), str.size(), dst, dst_len, status);
      dst += consumed;
      dst_len -= consumed;
      if(strcmp(TF_Message(status), "") != 0)
      {
         printf("%s\n", TF_Message(status));
      }
     }
     tensor = TF_AllocateTensor(TF_STRING, dims, num_dims, dimsSize + strSize);
     memcpy(TF_TensorData(tensor), buffer, dimsSize + strSize);
     TF_DeleteStatus(status);
  }
  else
  {
     std::cout << "String list and dims don't match!" << std::endl;
  }
}

/*
StringTensor::StringTensor(const int64_t *dims, const int64_t num_dims)
{
  int64_t num_values = 1;
  for (int i = 0; i < num_dims; ++i) {
    num_values *= dims[i];
  }
  tensor = TF_AllocateTensor(TF_STRING, dims, num_dims, sizeof(char) * num_values);
}
*/

StringTensor::StringTensor()
{
   tensor = NULL;
}

StringTensor::~StringTensor()
{
   if(tensor != NULL)
   {
      TF_DeleteTensor(tensor);
   }
}

void StringTensor::print()
{
/*
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
   */
}
