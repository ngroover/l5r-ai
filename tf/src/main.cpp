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
#include <tensorflow/c/c_api.h>

int main() {
   printf("TensorFlow C library version %s\n", TF_Version());

   TfGraph g;

   // Addition
   double data[] = {1.0, 2.0, 7.0, 4.0, 5.0};
   const int64_t dim[] = {5};
   DoubleTensor t1(dim, 1, data);
   DoubleTensor t2(dim, 1, data);
   DoubleTensor t3;

   ConstOp c(&g, &t1, "test");
   ConstOp c2(&g, &t2, "test2");

   AddOp a(&g, &c, &c2, "addit");

   TfSession sess(&g);

   sess.run(NULL, NULL, &a, &t3, NULL);

   t3.print();


   //Matmul

   double data2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
   double data3[] = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
   const int64_t dim2[] = {2,3};
   const int64_t dim3[] = {3,2};
   DoubleTensor t4(dim2, 2, data2);
   DoubleTensor t5(dim3, 2, data3);
   DoubleTensor t6;

   t4.print();
   t5.print();

   ConstOp c3(&g, &t4, "test3");
   ConstOp c4(&g, &t5, "test4");

   MatMulOp m(&g, &c3, &c4, "stuff");

   TfSession sess2(&g);

   sess2.run(NULL, NULL, &m, &t6, NULL);

   t6.print();

   // Truncated Normal Distribution

   const int32_t data4[] = {5,5};
   const int64_t data5[] = {5,5};
   const int64_t dim4[] = {2};
   Int32Tensor t7(dim4, 1, data4);
   DoubleTensor t8;
   ConstOp c5(&g, &t7, "test7");

   TruncatedNormalOp tnp(&g, &c5, TF_DOUBLE, "normy");

   TfSession sess3(&g);

   sess3.run(NULL, NULL, &tnp, &t8, NULL);
   TF_Status *status = TF_NewStatus();
   TF_GetCode(status);
   printf("session3 error=%s\n", TF_Message(status));

   t8.print();

   Variable v(&g, TF_DOUBLE, dim2, 2, "var1");
   AssignOp ass(&g, &c3, &v, "assigny");
   DoubleTensor t9;
   printf("Made varstuff\n");

   TfSession sess4(&g);
   sess4.run(NULL, NULL, NULL, NULL, &ass);
   TF_GetCode(status);
//   printf("session4 error=%s\n", TF_Message(status));
   printf("Made assignment\n");

   sess4.run(NULL, NULL, &v, &t9, NULL);

   printf("Variable\n");
   t9.print();

   printf("Variable2\n");
   double data6[] = {69.0, 70.0, 71.0, 72.0};
   const int64_t dim5[] = {2,2};
   double data7[] = {1.0, 0.0, 0.0, 1.0};
   double data8[] = {70.0, 71.0, 72.0, 73.0};
   Placeholder ph(&g, TF_DOUBLE, dim5, 2, "ph1");
   DoubleTensor t10;
   DoubleTensor t11(dim5, 2, data6);
   DoubleTensor t12(dim5, 2, data7);
   ConstOp c6(&g, &t12, "test5");

   MatMulOp m2(&g, &ph, &c6, "stuff69");

   TfSession sess5(&g);
   sess5.run(&ph, &t11, &m2, &t10, NULL);

   printf("Placeholder\n");
   t10.print();

   DoubleTensor t13(dim5, 2, data8);
   DoubleTensor t14;
   sess5.run(&ph, &t13, &m2, &t14, NULL);

   printf("Placeholder again\n");
   t14.print();
   return 0;
}
