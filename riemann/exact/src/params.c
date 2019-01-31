#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* #include "gas.h" */
#include "params.h"




/* ========================================== */
void init_params(params * p){
/* ========================================== */
  /* Initialize parameters to default values  */

  p->verbose = 0;
  strcpy(p->paramfilename, "");
  strcpy(p->datafilename,  "");

}




/* ========================================== */
void print_params(params *p, constants *c){
/* ========================================== */
  /* Print out current parameters             */

  printf("==================================================\n");
  printf("Starting calculation. Parameters are:\n");

  printf("Verbose?              ");
  if (p->verbose) {
    printf("True\n");
  } else {
    printf("False\n");
  }

  printf("gamma:                %g\n", c->gamma);

  printf("==================================================\n");

}
