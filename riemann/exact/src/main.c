/* ======================================== 
 *  
 * An exact Riemann solver.
 *
 * Usage: ./riemann paramfile.txt ic.dat
 *  
 * ======================================== */



#include <stdlib.h>
#include <stdio.h>

#include "io.h"
#include "params.h"
#include "riemann.h"




int main(int argc, char* argv[]){

  params p;
  state left;
  state right;
  init_params(&p);
  read_cmdlineargs(argc, argv, &p);
  read_paramfile(&p);
  print_params(&p);

  init_states(&left, &right);
  read_ic(&p, &left, &right);

  return(0);

}




