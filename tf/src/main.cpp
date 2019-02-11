#include <stdio.h>
#include <string.h>
#include "tfgraph.h"
#include "tfsession.h"
#include "doubletensor.h"
#include "constop.h"
#include "addop.h"
#include "matmulop.h"
#include "floattensor.h"
#include "int32tensor.h"
#include "truncatednormalop.h"
#include "variable.h"
#include "assignop.h"
#include "booltensor.h"
#include "placeholder.h"
#include "mean.h"
#include "squareddifference.h"
#include <tensorflow/c/c_api.h>

int main() {
   printf("TensorFlow C library version %s\n", TF_Version());

   TfGraph g;

   double data[] = {10.0, 20.0, 30.0};
   double data2[] = {50.0, 40.0, 35.0};
   const int64_t dim[] = {3};
   const int64_t dim2[] = {1};
   int32_t data3[] = {0};

   DoubleTensor t1(dim, 1, data);
   DoubleTensor t2(dim, 1, data2);
   Int32Tensor t4(dim2, 1, data3);
   DoubleTensor t3;
   DoubleTensor t5;

   ConstOp c(&g, &t1, "const");
   ConstOp c2(&g, &t2, "const2");
   ConstOp c3(&g, &t4, "const3");

   SquaredDifference sd(&g, &c, &c2, "sqdif");

   Mean m(&g, &sd, &c3, "mean1");

   TfSession sess(&g);
   sess.run(NULL, NULL, &sd, &t5, NULL);
   sess.run(NULL, NULL, &m, &t3, NULL);

   t5.print();
   t3.print();

   return 0;
}
