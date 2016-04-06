
/*
 * sdisys.c
 * 
 * Copyright 2014 dima <dima@debian>
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

#include "sdisys.h"
#include <stdio.h>
#include <wiringPi.h>

int f_sysinit(int itype,int use_exit)
{
	int ret=1;
	int code=-1;
	printf ( "<enter>f_sysinit(%d,%d)\n",itype,use_exit) ;
	switch(itype){
		case 1:
	           code=wiringPiSetup () ;
        break;
        case 2:
               // We need wiringPi setup in some way to make sure that
               //      delay() works, but we don't need to be root to
               //      use the I2C, so ...
               code=wiringPiSetupSys ();
        break;
        case 3:
        code=0;
        break;
        default:
        break;
    }
    if(code<0){
		 ret=0;
         fprintf (stderr, "<f_sysinit>wiringPiSetupSys setup failed\n") ;
         printf ( "wiringPiSetup setup failed wit code %d \n",code) ;
		 if(use_exit==1)
		 {
			 exit(1);
			 }
		}
		printf ( "<exit>f_sysinit\n") ;
	return ret;
}
