#ifndef __PARAMS_H__
#define __PARAMS_H__

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct configdata{
	 int configmode;//default=0,file=1,db=2
	 int itype;//init type of wiring
	 int use_exit_critical_function;//exit or only report
	 int use_exit_tolerant_function;//exit or only report
	 int log_level;//log level 0 none higher=more detailed
	 char *logfile;
	}cfg_dt;
	
cfg_dt load_config(int argc, char **argv);

void release_config(cfg_dt *a);

#if defined(__cplusplus)
}
#endif

#endif
