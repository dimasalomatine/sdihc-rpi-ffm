/*

 * gsm.cpp

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



#include "gsm.h"

#include <stdio.h>
#include <stdarg.h>

#include <string>
#include <iostream>


using namespace std;

	Gsm::Gsm(){
		m_model="NeowayM590";
		}
	Gsm::~Gsm(){}
	int Gsm::init(){
		 printf("Gsm %s init status %d\n",m_model.c_str(),m_init_status);
		 return m_init_status;
		}
	int Gsm::init(unsigned int type,unsigned int base){
		printf("Gsm type %d base %x\n",type,base);
		m_type=type;
		m_base=base;

	    return init();
		}
		
		
			int Gsm::doaction(unsigned int action,int n_args,...){
				int stat=0;
				printf("Gsm doaction type %d\n",action);
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
               printf("Gsm call unimplemented\n");
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
				
				 int Gsm::do_init(int n_args,va_list ap){
					 printf("Gsm call to do_init\n");
					 int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    return max;
					 }
	 int Gsm::do_reset(int n_args,va_list ap){ 
		  printf("Gsm call to do_reset\n");
		 int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    return max;}
	 int Gsm::do_read(int n_args,va_list ap){ 
		 printf("Gsm call to do_read\n");
		 int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    return max;}
