/*
 * sdi_coref.c
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

#include "sdi_coref.h"


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include <semaphore.h>


pthread_mutex_t lock_v= PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_v;

pthread_mutex_t lock_ai= PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_ai;

pthread_mutex_t lock_ao= PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_ao;

int globalwork=TRUE;

void * th_global_wd()
{
        while(globalwork==TRUE&&immediatestop==0){
               
                printf("wd...\n");
                //
                //
                sleep(1);
                
        }
        globalwork=FALSE;
        immediatestop=1;
        
        printf("th_global_wd exit stop all...\n");
}

void * th_video_in_m_process()
{
	    char cmd[1024];
	    int res;
        while(globalwork){
                pthread_mutex_lock(&lock_v);
                printf("capturing video...\n");
                //
                //sprintf(cmd, "/bin/ls -l");
                sprintf(cmd, "raspistill -t 100 -w 1920 -h 1080 -q 90 -o /home/pi/rha/tmpimg/currcap.jpg");
                res=system(cmd);
                fprintf(stdout,"execution returned %d.\n",res);
                if ((-1 != res) && (0 != res)){
                 fprintf(stdout,"now would be a good time to check out what the resulting return-value (%d) means.\n",res);
                }else{
	                  sprintf(cmd, "cp /home/pi/rha/tmpimg/currcap.jpg /home/pi/rha/tmpimg/currinproc.jpg");
                      res=system(cmd);
                      fprintf(stdout,"execution returned %d.\n",res);
                      if ((-1 != res) && (0 != res)){
                        fprintf(stdout,"now would be a good time to check out what the resulting return-value (%d) means.\n",res);
                      }else{
	                        fprintf(stdout,"capture ok going to proccess opencv...\n");
	                        //here begin 1
	                        //here end 1
	                       }
	                  }
                //
                sleep(1);
                pthread_mutex_unlock(&lock_v);
                pthread_cond_signal(&cond_v);
        }
        printf("th_video_in_m_process exit...\n");
}

void * th_video_in_process()
{
        while(globalwork){
               
                pthread_mutex_lock(&lock_v);
                
                 pthread_cond_wait(&cond_v,&lock_v);
                 printf("pthread_cond_ok\n");
                 //
                 //
                  pthread_mutex_unlock(&lock_v);
        }
}

void * th_audio_in_m_process()
{
        while(globalwork){
                pthread_mutex_lock(&lock_ai);
                printf("capturing audio...\n");
                //
                //
                sleep(1);
                pthread_mutex_unlock(&lock_ai);
                pthread_cond_signal(&cond_ai);
        }
        printf("th_audio_in_m_process exit...\n");
}

void * th_audio_in_process()
{
        while(globalwork){
               
                pthread_mutex_lock(&lock_ai);
                
                 pthread_cond_wait(&cond_ai,&lock_ai);
                 printf("pthread_cond_ok\n");
                 //
                 //
                  pthread_mutex_unlock(&lock_ai);
        }
}

void * th_audio_out_m_process()
{
        while(globalwork){
                pthread_mutex_lock(&lock_ao);
                printf("begin speaking...\n");
                //
                //
                sleep(1);
                pthread_mutex_unlock(&lock_ao);
                pthread_cond_signal(&cond_ao);
        }
        printf("th_audio_out_m_process exit...\n");
}

void * th_audio_out_process()
{
        while(globalwork){
               
                pthread_mutex_lock(&lock_ao);
                
                 pthread_cond_wait(&cond_ao,&lock_ao);
                 printf("pthread_cond_ok speak\n");
                 //
                 //
                  pthread_mutex_unlock(&lock_ao);
        }
}

	
	pthread_t tr0,tr, tr2,tr3;
	
int coref_start(int argc, char **argv)
{
	    pthread_create(&tr0,NULL,th_global_wd,NULL);
        pthread_create(&tr,NULL,th_video_in_m_process,NULL);
        pthread_create(&tr2,NULL,th_audio_in_m_process,NULL);
        pthread_create(&tr3,NULL,th_audio_out_m_process,NULL);
        
        
        
            
        
 return 0;
}

int coref_join(int argc, char **argv){
	 pthread_join(tr,NULL);
        pthread_join(tr2,NULL);
        pthread_join(tr3,NULL);
        pthread_join(tr0,NULL);
        
 return 0;
	}
