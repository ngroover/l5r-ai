#include <stdio.h>
#include <string.h>
#include "tfgraph.h"
#include "tfsession.h"
#include "doubletensor.h"
#include "constop.h"
#include "addop.h"
#include <tensorflow/c/c_api.h>

int main() {
   printf("TensorFlow C library version %s\n", TF_Version());

   TfGraph g;

   double data[] = {1.0, 2.0, 7.0, 4.0, 5.0};
   const int64_t dim[] = {5};
   DoubleTensor t1(dim, 1, data);
   DoubleTensor t2(dim, 1, data);
   DoubleTensor t3;

   ConstOp c(&g, &t1, "test");
   ConstOp c2(&g, &t2, "test2");

   AddOp a(&g, &c, &c2, "addit");

   TfSession sess(&g);

   sess.run(NULL, NULL, &a, &t3);

   t3.print();

   return 0;
}
