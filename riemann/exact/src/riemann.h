/* all stuff concerning Riemann problem */

#ifndef RIEMANN_H
#define RIEMANN_H
#include "gas.h"


extern void check_ic(constants* c, state *left, state *right);
extern void compute_star_state(constants *c, state *left, state *right, state* starL, state* starR);
extern double compute_pstar(constants *c, state *left, state *right);
extern double fp(double pguess, state *s, double gamma, double A, double B, double a);
extern double dfpdp(double pguess, state *s, double gamma, double A, double B, double a);
extern double fpfull(double fpL, double fpR, double delta_u);
extern double dfpdpfull(double dfpdpL, double dfpdpR);
extern double rho_star(constants *c, state *s, state *star);
#endif
