#include "riemann.h"


/* ========================================= */
/* This function initializes the states.     */
/* ========================================= */

void init_states(state *left, state *right){

  left->rho  = 0;
  left->u    = 0;
  left->p    = 0;

  right->rho = 0;
  right->u   = 0;
  right->p   = 0;

}
