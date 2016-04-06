#ifndef __SDI_COREF_H__
#define __SDI_COREF_H__

#ifndef TRUE

#define TRUE 1
#define FALSE 0

#endif

extern short int immediatestop;
extern int globalwork;

int coref_start(int argc, char **argv);
int coref_join(int argc, char **argv);

#endif
