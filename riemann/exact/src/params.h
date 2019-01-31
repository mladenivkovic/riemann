/* All around parameters used in the simulation. */

#ifndef PARAMS_H
#define PARAMS_H
#include "gas.h"

/* GLOBAL PARAMETERS */
typedef struct {
  int verbose;
  char paramfilename[200];
  char datafilename[200];
} params;



// extern void check_params();
extern void init_params(params *p);
extern void print_params(params *p, constants *c);


#endif
