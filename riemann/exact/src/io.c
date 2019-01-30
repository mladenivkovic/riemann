#include "params.h"
#include "riemann.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 200


/* ====================================================================== */
/* This function reads in the command line arguments and stores them in   */
/* the globalparams struct                                                */
/* ====================================================================== */
void read_cmdlineargs(int argc, char* argv[], params* p){

  if (argc < 3){
    printf("Too few arguments given. Run this program with ./riemann paramfile datafile\n");
    exit(600);
  }
  else {
    strcpy(p->paramfilename, argv[1]);
    strcpy(p->datafilename, argv[2]);
  };

}



/* ====================================================================== */
/* Read in initial conditions file, store read states.                    */
/* ====================================================================== */
void read_ic(params* p, state* left, state* right){

  //open file
  FILE *par = fopen(p->datafilename, "r");

  // check if file exists
  if (par == NULL) { 
    printf("Error: file '%s' not found.\n", p->datafilename);
    exit(2);
  }

  char varname[80] ;
  char varvalue[80] ;
  char tempbuff[MAX_LINE_SIZE] ;

  


  while (fgets(tempbuff,MAX_LINE_SIZE,par))
  // fgets(str_buff, n,filepointer) :
  // gets n characters from file in filepointer and stores them
  // in str_buff.
  // returns 0 if EoF is reached.
  
  {
  
    // check whether tempbuff is empty line
    int isempty = 0;
    for (int i = 0; i<MAX_LINE_SIZE; i++){
      if (tempbuff[i] != ' '){
        if (tempbuff[i] == '\n'){
          isempty = 1;
        }
        break;
      }
    }

    if (isempty) continue;


    sscanf(tempbuff, "%20s = %56[^\n]\n", varname, varvalue);
    // reads formatted input from a string, writes it in
    // the variables given after the format string.
    // The format used is <string> separator <=> <string> ends with <;>
  
    if (strcmp(varname,"rho_L") == 0) {
      left->rho = atof(varvalue);
    } 
    else if (strcmp(varname, "u_L")==0){
      left->u = atof(varvalue);
    }
    else if (strcmp(varname, "p_L")==0){
      left->p = atof(varvalue);
    }
    else if (strcmp(varname, "rho_R") == 0) {
      right->rho = atof(varvalue);
    } 
    else if (strcmp(varname, "u_R")==0){
      right->u = atof(varvalue);
    }
    else if (strcmp(varname, "p_R")==0){
      right->p = atof(varvalue);
    }
    else if (strcmp(varname, "//")==0) {
      // ignore comments
      continue;
    }
    else if (strcmp(varname, "/*")==0) {
      // ignore comments
      continue;
    }
    else{
      printf("Unrecongized data : \"%s\" | \"%s\"\n", varname, varvalue);
    }
  }

  fclose(par);



  if (p->verbose) {
    
    printf(" Initial conditions are:\n");
    printf("        Left                 Right\n");
    printf(" rho =  %20.8lf %20.8lf \n", left->rho, right->rho);
    printf(" u   =  %20.8lf %20.8lf \n", left->u, right->u);
    printf(" p   =  %20.8lf %20.8lf \n", left->p, right->p);
    printf("=======================================================================\n");

  }

}



/* ====================================================================== */
/* Read in parameter file, store read in global parameters.               */
/* ====================================================================== */
void read_paramfile(params* p){

  /* globalparams * g = &(p->gp); */
  /* units *u = &(p->units); */


  //open file
  FILE *par = fopen(p->paramfilename, "r");

  // check if file exists
  if (par == NULL) { 
    printf("Error: file '%s' not found.\n", p->paramfilename);
    exit(2);
  }

  char varname[80] ;
  char varvalue[80] ;
  char tempbuff[MAX_LINE_SIZE] ;

  


  while (fgets(tempbuff,MAX_LINE_SIZE,par))
  // fgets(str_buff, n,filepointer) :
  // gets n characters from file in filepointer and stores them
  // in str_buff.
  // returns 0 if EoF is reached.
  
  {
  
    // check whether tempbuff is empty line
    int isempty = 0;
    for (int i = 0; i<MAX_LINE_SIZE; i++){
      if (tempbuff[i] != ' '){
        if (tempbuff[i] == '\n'){
          isempty = 1;
        }
        break;
      }
    }

    if (isempty) continue;


    sscanf(tempbuff, "%20s = %56[^\n]\n", varname, varvalue);
    // reads formatted input from a string, writes it in
    // the variables given after the format string.
    // The format used is <string> separator <=> <string> ends with <;>
  

    if (strcmp(varname,"verbose") == 0) {
      p->verbose = atoi(varvalue);
    // atoi/atof: convert string to integer/float
    // from stdlib.h
    } 
    /* else if (strcmp(varname, "unit_m")==0){ */
    /*   u->unit_m = atof(varvalue); */
    /* } */
    /* else if (strcmp(varname, "unit_l")==0){ */
    /*   u->unit_l = atof(varvalue); */
    /* } */
    /* else if (strcmp(varname, "unit_t")==0){ */
    /*   u->unit_t = atof(varvalue); */
    /* } */
    else if (strcmp(varname, "//")==0) {
      // ignore comments
      continue;
    }
    else if (strcmp(varname, "/*")==0) {
      // ignore comments
      continue;
    }
    else{
      printf("Unrecongized parameter : \"%s\"\n", varname);
    }
  }

    fclose(par);

}
