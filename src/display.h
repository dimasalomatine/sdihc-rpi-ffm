#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "gapptypes.h"

class Display:BaseT{
	public:
	Display();
	~Display();
	 int init(unsigned int type,unsigned int base); 
	 int doaction(unsigned int action,int n_args,...); 
	 int do_init(int n_args,va_list args);
	 int do_reset(int n_args,va_list args);
	 int do_read(int n_args,va_list args);
	 private:
	 int init();
	};

#endif
