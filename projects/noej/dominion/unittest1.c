#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printTestResults(int test){
      if(test == 0)
            printf("Test Failed.\n");
      else if(test == 1)
            printf("Test Passed.\n");
      else
            printf("Function returned unexpected value.\n");
}

int compareTest(){
      int a = 10;
      int b = 9;
      int *ptr1 = &a;
      int *ptr2 = &b;

      if(compare(ptr1, ptr2) != 1)
            return 0;
      else if(compare(ptr2, ptr1) != -1)
            return 0;
      else if(compare(ptr2, ptr2) != 0)
            return 0;
      else
            return 1;
}
int main(){

      printf("Testing the 'compare' function...\n");
      int testResults = compareTest();
      printTestResults(testResults);

      return 0;
}
