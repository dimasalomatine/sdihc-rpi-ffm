#ifndef __SELUA_H__
#define __SELUA_H__

#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class selua{
	public:	
	static selua* Instance();
	static selua* Erase();
	int init();
	int f_enter_lua_cbloop();
    int f_exec_lua_file(std::string argv);
    int f_exec_lua_ep(std::string argv,std::vector<std::string> argv2);
	private:
	selua(); // Private so that it can  not be called
    selua(selua const&){;};             // copy constructor is private
    selua& operator=(selua const&){;};  // assignment operator is private
	static selua* m_inst;
	};
	
#endif
