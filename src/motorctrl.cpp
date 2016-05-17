/*
 * motorctrl.cpp
 * 
 * Copyleft 2014 dima <dima@debian>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
 /*
  * 
  * Motor Type	Unipolar stepper motor
  * Connection Type	5 Wire Connection (to the motor controller)
  * Voltage	5-12 Volts DC
  * Frequency	100 Hz
  * Step mode	Half-step mode recommended (8 step control signal sequence)
  * Step angle	Half-step mode: 
  * 8 step control signal sequence (recommended) 5.625 degrees per step / 64 steps per one revolution of the internal motor shaft
  * Full Step mode: 4 step control signal sequence 11.25 degrees per step / 32 steps per one revolution of the internal motor shaft
  * Gear ratio	Manufacturer specifies 64:1. Some patient and diligent people on the Arduino forums have disassembled the gear train of 
  * these little motors and determined that the exact gear ratio is in fact 63.68395:1. 
  * My observations confirm their findings. 
  * These means that in the recommended half-step mode we will have:64 steps per motor rotation x 63.684 gear ratio = 4076 steps per full revolution (approximately).
  * Wiring to the ULN2003 controller	A (Blue), B (Pink), C (Yellow), D (Orange), E (Red, Mid-Point)
  * Weight	30g
  * 
  * */
#include <stdio.h>
#include <wiringPi.h>

#include "motorctrl.h"
#include <stdio.h>
#include <stdarg.h>

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int sec[][]={{HIGH,LOW,LOW,LOW},
	         {HIGH,HIGH,LOW,LOW},
	         {LOW,HIGH,LOW,LOW},
	         {LOW,HIGH,HIGH,LOW},
	         {LOW,LOW,HIGH,LOW},
	         {LOW,LOW,HIGH,HIGH},
	         {LOW,LOW,LOW,HIGH},
	         {HIGH,LOW,LOW,HIGH}
	         };
	         
	int Motor::do_loadDF(){
		
		string STRING;
	    ifstream infile;
	    infile.open ("names.txt");
	    if(infile.is_open()){
        while ( getline (infile,STRING) )
        {
          cout << STRING << '\n';
          string s = STRING;//"scott>=tiger>=mushroom";
          string delimiter = ">=";

          size_t pos = 0;
          string token;
          while ((pos = s.find(delimiter)) != string::npos) 
          {
          token = s.substr(0, pos);
          cout << token << endl;
          s.erase(0, pos + delimiter.length());
          }
          cout << s << endl;

        }
	    infile.close();
	    }
	
		return 0;
		}

	Motor::Motor(){
		 m_drive="ULN2003";
		 m_model="28BYJ-48";
		 motor_setup_default(0);
		}
	Motor::~Motor(){}
	int Motor::init(){
		 printf("Motor %s drive %s init status %d\n",m_model.c_str(),m_drive.c_str(),m_init_status);
		 return m_init_status;
		}
	int Motor::init(unsigned int type,unsigned int base){
		printf("Motor type %d base %x\n",type,base);
		m_type=type;
		m_base=base;

	return init();
		}
		
		
			int Motor::doaction(unsigned int action,int n_args,...){
				int stat=0;
				printf("Motor doaction type %d\n",action);
			  va_list ap;
			  va_start(ap, n_args);
			  switch(action){
				  case ACT_GEN_INIT:
              stat=do_init(n_args, ap); 
              break;
              case ACT_GEN_RESET:
              stat=do_reset(n_args, ap); 
              break;
              case ACT_GEN_READ:
              stat=do_read(n_args, ap); 
              break;
              default:
              stat=-1;
               printf("Motor call unimplemented\n");
              break;
				  };
     
   /* int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    stat=max;
    * */
    va_end(ap);
    return stat;
				}
				
				 int Motor::do_init(int n_args,va_list ap){
					 printf("Motor call to do_init\n");
					 int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    return max;
					 }
	 int Motor::do_reset(int n_args,va_list ap){ 
		  printf("Motor call to do_reset\n");
		 int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    return max;}
	 int Motor::do_read(int n_args,va_list ap){ 
		 printf("Motor call to do_read\n");
		 int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    return max;}
    

void Motor::motor_setup_default(int baseaddr)
{
	       m_base=baseaddr; 
	       // Define GPIO signals to use
           // Physical pins 11,15,16,18
           // BCM GPIO17,GPIO22,GPIO23,GPIO24
           // WP 0,3,4,5
           s_ctrl[0]=0;
           s_ctrl[1]=3;
           s_ctrl[2]=4;
           s_ctrl[3]=5;
	}
void Motor::motor_setup(int baseaddr,int ctrl1,int ctrl2,int ctrl3,int ctrl4)
{ 
	m_base=baseaddr;
	s_ctrl[0]=ctrl1;
	s_ctrl[1]=ctrl2;
	s_ctrl[2]=ctrl3;
	s_ctrl[3]=ctrl4;
	for(int i=0;i<4;i++){
	if(m_base + s_ctrl[i]>=0){
		pinMode (m_base + s_ctrl[i], OUTPUT) ;
	}
	}
	
	} 
void Motor::motor_order(int mtype,int param1,int param2)
{
    switch(mtype)
    {
		case 0:
		motor_stop();
		break;
		case 1:
		motor_start();
		break;
		case 2:
		motor_forward(param1,param2);
		break;
		case 3:
		motor_back(param1,param2);
		break;
		default:
		motor_stop();
		break;
		};	
	}
void Motor::motor_stop()
{
	for(int i=0;i<4;i++){
	digitalWrite(m_base + s_ctrl[i],LOW);
    }
	}
void Motor::motor_start()
{
	
	}
void Motor::motor_forward(int speed,int tlimit)
{
	int currentsec=0;
	for(int i=0;i<8;i++)
	{
	 for(int j=0;j<4;j++){
	 digitalWrite(m_base + s_ctrl[j],sec[i][j]);
	 }
    }
	}
void Motor::motor_back(int speed,int tlimit)
{
	
	}
	
	
