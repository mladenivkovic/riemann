#include "gas.h"
#include "riemann.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/* ====================================================== */
void check_ic(constants* c, state *left, state *right){
/* ====================================================== */
  /* Check that the initial conditions are proper         */
  /*------------------------------------------------------*/

  double delta_u = right->u - left->u;
  double u_crit = 2./(c->gamma - 1) * (soundspeed(c, left) + soundspeed(c, right));

  if (delta_u >= u_crit){
    printf("delta_u >= u_crit: nonnegative pressure condition violated. Quitting.\n");
    exit(0);
  }

}


/* ========================================================================================== */
void compute_star_state(constants *c, state *left, state *right, state* starL, state* starR){
/* ========================================================================================== */
  /* computes the star state given the left and right states.                                 */
  /*------------------------------------------------------------------------------------------*/

  double AL = 2. / ((c->gamma + 1) * left->rho);
  double AR = 2. / ((c->gamma + 1) * right->rho);
  double BL = (c->gamma - 1)/(c->gamma + 1) * left->p;
  double BR = (c->gamma - 1)/(c->gamma + 1) * right->p;
  double aL = soundspeed(c, left);
  double aR = soundspeed(c, right);

  double delta_u = right->u - left->u;

  double tolerance = 1e-6;

  double pguess, pold;
  double fL, fR, dfpdpL, dfpdpR;


  pguess = 0.5*(left->p + right->p);

  int niter = 0;

  do {
    niter += 1;
    fL = fp(pguess, left,  c->gamma, AL, BL, aL);
    fR = fp(pguess, right, c->gamma, AR, BR, aR);
    dfpdpL = dfpdp(pguess, left,  c->gamma, AL, BL, aL);
    dfpdpR = dfpdp(pguess, right, c->gamma, AR, BR, aR);
    pold = pguess;
    pguess -= fpfull(fL, fR, delta_u)/dfpdpfull(dfpdpL, dfpdpR);
    if (pguess<tolerance) pguess=tolerance;
    /* printf("pstar iter %d pguess=%10.6lf, pold=%10.6lf\n", niter, pguess, pold); */
  }
  while (2*fabs((pguess-pold)/(pguess+pold)) >= tolerance);
  printf("p* found after %d iterations.\n", niter);


  starL->p = pguess;
  starR->p = pguess;

  fL = fp(pguess, left,  c->gamma, AL, BL, aL);
  fR = fp(pguess, right, c->gamma, AR, BR, aR);
  double u = 0.5*((left->u + right->u) + fR - fL);
  starL->u = u;
  starR->u = u;

  starL->rho = rho_star(c, left,  starL);
  starR->rho = rho_star(c, right, starR);
  

}



/* ==================================================== */
double rho_star(constants *c, state *s, state *star){
/* ==================================================== */
  /* Compute the density in the star region             */
  /*----------------------------------------------------*/

  double pdiv = (star->p/s->p);
  if (star->p > s->p) {
    /* shocking matters */
    double gamfact = (c->gamma - 1)/(c->gamma + 1);
    return s->rho * (gamfact + pdiv) / (gamfact*pdiv + 1);
  } 
  else{
    /* rare occasions */
    return s->rho * pow(pdiv, (1./c->gamma));
  }

}





/* ========================================================== */
double fpfull(double fpL, double fpR, double delta_u){
/* ========================================================== */
  /* Full pressure function                                   */
  /*----------------------------------------------------------*/
  return fpL + fpR + delta_u;
}


/* ================================================== */
double dfpdpfull(double dfpdpL, double dfpdpR){
/* ================================================== */
  /* Full derivative of pressure function             */
  /*--------------------------------------------------*/
  return dfpdpL + dfpdpR;
}






/* =============================================================================== */
double fp(double pguess, state *s, double gamma, double A, double B, double a){
/* =============================================================================== */
  /* Left/Right part of the pressure function                                      */
  /*-------------------------------------------------------------------------------*/

  if (pguess > s->p){
    /* we have a shock situation */
    return (pguess - s->p)*sqrt(A/(pguess + B));
  }
  else{
    /* we have a rarefaction situation */
    return 2 * a / (gamma - 1) * ( pow(pguess/s->p, 0.5*(gamma-1)/gamma) - 1 );
  }
}


/* =============================================================================== */
double dfpdp(double pguess, state *s, double gamma, double A, double B, double a){
/* =============================================================================== */
  /* First derivative of Left/Right part of the pressure function                  */
  /*-------------------------------------------------------------------------------*/

  if (pguess > s->p){
    /* we have a shock situation */
    return sqrt(A/(pguess + B)) * (1 + 0.5 * (pguess - s->p)/(pguess + B));
  }
  else{
    /* we have a rarefaction situation */
    return 1./(s->rho * a) * ( pow(pguess/s->p, -0.5*(gamma+1)/gamma) );
  }
}

