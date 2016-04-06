#ifndef __MOTORCTRL_H__
#define __MOTORCTRL_H__

//ULN2003
void motor_setup_default(int baseaddr);
void motor_setup(int baseaddr,int ctrlA,int Actrl1,int Actrl2,int ctrlB,int Bctrl1,int Bctrl2); 
void motor_order(int mtype,int ctrl,int param1,int param2);
void motor_stop(int ctrl);
void motor_start(int ctrl);
void motor_forward(int ctrl);
void motor_back(int ctrl);


#endif
