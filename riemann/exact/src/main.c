/* ======================================== 
 *  
 * An exact Riemann solver.
 *
 * Usage: ./riemann paramfile.txt ic.dat
 *  
 * ======================================== */



#include <stdlib.h>
#include <stdio.h>

#include "gas.h"
#include "io.h"
#include "params.h"
#include "riemann.h"


/*==========================================================================*/
void print_results(state* left, state* right, state* starL, state* starR){
/*==========================================================================*/
  /* print the 2 resulting star states between the initial states.          */
  /*------------------------------------------------------------------------*/
    
  printf("        %12s %12s %12s %12s\n", "Left", "Star left", "Star right", "Right");
  printf(" rho =  %12.5lf %12.5lf %12.5lf %12.5lf \n", left->rho, starL->rho, starR->rho, right->rho);
  printf(" u   =  %12.5lf %12.5lf %12.5lf %12.5lf \n", left->u,   starL->u,   starR->u,   right->u);
  printf(" p   =  %12.5lf %12.5lf %12.5lf %12.5lf \n", left->p,   starL->p,   starR->p,   right->p);
  printf("=======================================================================\n");


}




/* ====================================== */
int main(int argc, char* argv[]){
/* ====================================== */

  params p;
  constants c;
  state left, right, starL, starR;
  init_params(&p);
  init_constants(&c);
  read_cmdlineargs(argc, argv, &p);
  read_paramfile(&p, &c);
  if (p.verbose) print_params(&p, &c);

  init_states(&left, &right, &starL, &starR);
  read_ic(&p, &left, &right);
  check_ic(&c, &left, &right);
  compute_star_state(&c, &left, &right, &starL, &starR);
  print_results(&left, &right, &starL, &starR);


  return(0);

}




