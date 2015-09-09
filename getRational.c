/*
 * Extra Credit Assignment
 *
 * Author: Dan Wilder
 * Class:  Math 3000 (Discrete Structures)
 * Date:   2015-02-23
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/*      p=1  p=2  p=3  ...
 *    
 * q=1  1/1  2/1  3/1  ...
 * 
 * q=2  1/2  2/2  3/2  ...
 *   
 * q=3  1/3  2/3  3/2  ...
 * 
 * ...  ...  ...  ...  ...
 *
 */

typedef enum {down, upright, right, downleft} direction_t;

long unsigned int gcd(long unsigned int, long unsigned int); 
 
void getRational(long unsigned int n, char *dest, int mode) {
  // Stores the nth positive rational number as "p/q" in dest
  // mode=1 means that will function will print all values of f(n) during
  // execution
  
  if (n < 1) // n < 1 is not in domain. Domain is N = {1,2,3,...}; 
    exit(1); 

  long unsigned int p=1, q=1;  // Fist rational number
  direction_t direction = down;

  if (mode == 1) {
    printf("f(%d) = %lu/%lu\n", 1, p, q); 
  }

  long unsigned int nBefore; // For use with mode == 1  
  int i = 1;   // For use with mode == 1
  while (n!= 1) {
    nBefore = n; // Will be used to compare if n changed during loop iteration  

    switch(direction) { //Sets p/q to next examine location
    case down:
      q++;
      direction++; // Always change direction after going down;
      n--;
      break;

    case upright:
      p++;
      q--;
      if (q == 1) { // then in first row (1,2,3...)
        direction++;
        n--;
      } 
      else if (gcd(p,q) == 1) // is a UNIQUE rational
        n--;
      break;

    case right:
      p++;
      direction++;
      n--;
      break;

    case downleft:
      p--;
      q++;
      if (p == 1) { // then in first col (1/1, 1/2, 1/3)
        direction = down;
        n--;
      } 
      else if (gcd(p,q) == 1) // is a UNIQUE rational
        n--;
      break;
    }

    if (mode == 1 && n != nBefore) {
      i++; 
      printf("f(%d) = %lu/%lu\n", i, p, q); 
    }        
  }
    
  snprintf(dest, 100, "%lu/%lu", p, q);
}

long unsigned int gcd(long unsigned int a, long unsigned int b) {
  long unsigned int temp;

  while (b != 0) {
    temp = b;
    b = a % b;
    a = temp;    
  }
  return a;
}

int main(int argc, char *argv[]) {
  
  char programName[16];
  snprintf(programName, sizeof(programName), "%s", argv[0]);

  if (argc == 1) {
    printf("[%s Syntax] : %s NUM\n", programName, programName);
    printf("   where NUM is a positive int\n");
    return 0;
  }

  char arg1Buffer[21];  
  snprintf(arg1Buffer, sizeof(arg1Buffer), "%s", argv[1]);

  int n = atoi(arg1Buffer);
  char strFn[100];
 
  // Did a patch job on implementing 2 modes; i.e. only check num arguments lol
  int mode = 0; // 0 -> Only want final val ;  1 -> Print all f(n) for n in [1,n]  
  if (argc > 2) { 
    mode =1;
  }

  getRational(n, strFn, mode); // Finds nth rational number, store as string in strFn
  printf("\n\n***    f(%d) = %s    ***\n", n, strFn);

  return 0;
}
