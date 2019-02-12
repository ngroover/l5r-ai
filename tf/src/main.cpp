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
#include "biasadd.h"
#include "squareddifference.h"
#include "gradients.h"
#include "relu.h"
#include "sigmoid.h"
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

   double data4[] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0};
   const int64_t dim3[] = {2, 3};
   const int64_t dim4[] = {3};
   const int64_t dim5[] = {3, 1};
   double data5[] = {5.0, 6.0, 7.0};

   DoubleTensor t6(dim3, 2, data4);
   DoubleTensor t7(dim4, 1, data5);
   DoubleTensor t8;

   ConstOp c4(&g, &t6, "const4");
   ConstOp c5(&g, &t7, "const5");

   BiasAdd ba(&g, &c4, &c5, "badd");

   TfSession sess2(&g);
   sess2.run(NULL, NULL, &ba, &t8, NULL);

   t8.print();

   // MatMul
   DoubleTensor t9(dim3, 2, data4);
   DoubleTensor t10(dim5, 2, data5);
   DoubleTensor t11;
   DoubleTensor t12;

   ConstOp c6(&g, &t9, "const6");
   ConstOp c7(&g, &t10, "const7");

   MatMulOp mm(&g, &c6, &c7, "mm");

   Relu ru(&g, &mm, "ru");

   Sigmoid sig(&g, &ru, "sig");

   TfSession sess3(&g);
   sess3.run(NULL, NULL, &sig, &t11, NULL);

   printf("MatMul=\n");
   t11.print();

   Gradients grad(&g, &mm, &c6, "matmulgrad");

   sess3.run(NULL, NULL, &grad, &t12, NULL);

   printf("MatMul grad=\n");
   t12.print();

   return 0;
}
