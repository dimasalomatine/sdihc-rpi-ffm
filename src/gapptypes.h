#ifndef __GAPPTYPES_H__
#define __GAPPTYPES_H__

#ifndef TRUE

#define TRUE 1
#define FALSE 0

#endif

#include <stdarg.h>
#include <string>
#include <iostream>
using namespace std;




#define TYPE_I2C 1
#define TYPE_IO 2

#define ACT_GEN_INIT 0
#define ACT_GEN_RESET 1
#define ACT_GEN_READ 2


class BaseT{
	public:
	BaseT(){m_init_status=-1;}
	~BaseT(){}
	
	virtual int init(unsigned int type,unsigned int base){}
	virtual int doaction(unsigned int action,int n_args,...){}
	
	virtual int do_init(int n_args,va_list args){}
	virtual int do_reset(int n_args,va_list args){}
	virtual int do_read(int n_args,va_list args){}
	virtual int do_loadDF(){}
	
	private:
	virtual int init(){}
	protected:
	int m_init_status;
	unsigned m_type;
	unsigned int m_base;
	string m_drive;
	string m_model;
	};

#endif
