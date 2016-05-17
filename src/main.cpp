
#include <stdio.h>
#include <string.h>


#include "params.h"
#include "sdisys.h"
#include "sdi_coref.h"
#include "gyro.h"
#include "gsm.h"
#include "display.h"
#include "motorctrl.h"

#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;



#if defined(__cplusplus)
extern "C" {
#endif
#include <wiringPi.h>
#include <mcp23017.h>
#include <unistd.h>
#include <pthread.h>
#if defined(__cplusplus)
}
#endif

#define BASE_I2C        456

short int immediatestop=0;


PI_THREAD (matrixUpdater)
{
  int i ;

  printf("PI_THREAD enter %ld\n",pthread_self());
  piHiPri (50) ;

  for (i=0;i<100;i++)
  {
   
          printf("PI_THREAD work%ld result i= %d\n",pthread_self(),i);
          //delayMicroseconds (50) ;
          sleep(1);
          if(i>50){immediatestop=1;break;}
       
  }
  printf("PI_THREAD success %ld\n",pthread_self());

  return NULL ;
}

int main(int argc, char **argv)
{
	printf("hello\n");
	
	Gyro g;
	g.init(TYPE_I2C,0x0);
	
	Display d;
	d.init(TYPE_I2C,0x0);
	
	Gsm gs;
	gs.init(TYPE_I2C,0x0);
	
	Motor m1;
	m1.init(TYPE_I2C,0x20);
	
	printf("ter2 %d\n",g.doaction(0,2,1,2));
	printf("ter2 %d\n",g.doaction(1,3,1,2,3));
	printf("ter2 %d\n",g.doaction(2,4,1,2,3,9));
	printf("ter2 %d\n",g.doaction(88,1,55));
	
	
	cfg_dt cfg=load_config(argc,argv);
	printf("config type loaded=%d=>loglevel=%d\t\nlogfile=%s\n",cfg.configmode,cfg.log_level,cfg.logfile);
	
	// from aaa.h test f(argc, argv);
	
	
	if(1!=f_sysinit(cfg.itype,cfg.use_exit_critical_function))
	{ 
		release_config(&cfg);
		return 1;
     }
     else if(cfg.itype!=3)
     {
		 printf("init base\n.............................++++++++++++++");
	
	  mcp23017Setup (BASE_I2C, 0x20) ;
	  
	
	// For the push button to stop it...

  pinMode         (BASE_I2C + 15, OUTPUT) ;
  digitalWrite(BASE_I2C + 15, HIGH);
  sleep(1);
  pinMode         (BASE_I2C + 15, INPUT) ;
  pullUpDnControl (BASE_I2C + 15, PUD_UP) ;
  
  while (digitalRead (BASE_I2C + 15) == 0)
        delay (1) ;
  }
  
    coref_start(argc, argv);
    
    piThreadCreate (matrixUpdater) ;
    //piThreadCreate (matrixUpdater) ;
    
    coref_join(argc, argv);
    
     while(/*getchar()!=32&&*/immediatestop==0);
     globalwork=FALSE;
	release_config(&cfg);
	return 0;
}
