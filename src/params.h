#ifndef __PARAMS_H__
#define __PARAMS_H__

typedef struct configdata{
	 int itype;//init type of wiring
	 int use_exit_critical_function;//exit or only report
	 int use_exit_tolerant_function;//exit or only report
	 int log_level;//log level 0 none higher=more detailed
	 char *logfile;
	}cfg_dt;
	
cfg_dt load_config(int argc, char **argv);

void release_config(cfg_dt *a);

#endif
