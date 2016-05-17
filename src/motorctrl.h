#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__

#include "gapptypes.h"

class Motor:BaseT{
	public:
	Motor();
	~Motor();
	 int init(unsigned int type,unsigned int base); 
	 int doaction(unsigned int action,int n_args,...); 
	 int do_init(int n_args,va_list args);
	 int do_reset(int n_args,va_list args);
	 int do_read(int n_args,va_list args);
	 
	 int do_loadDF();
	 private:
	 int init();
	 
	 void motor_setup_default(int baseaddr);
     void motor_setup(int baseaddr,int ctrl1,int ctrl2,int ctrl3,int ctrl4); 
     void motor_order(int mtype,int param1,int param2=-1);
     void motor_stop();
     void motor_start();
     void motor_forward(int param1,int param2=-1);
     void motor_back(int param1,int param2=-1);
     
     int s_ctrl[4];

	};
	




#endif
