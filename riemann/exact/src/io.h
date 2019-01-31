/* IO routines */

#ifndef IO_H
#define IO_H
#include "gas.h"
#include "params.h"

extern void read_cmdlineargs(int argc, char* argv[], params* p);
extern void read_ic(params* p, state* left, state* right);
extern void read_paramfile(params* p, constants* c);


#endif
