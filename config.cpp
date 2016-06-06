#include <iostream>
#include <fstream>
#include <config.hpp>

#ifdef DEBUG
   
#else
std::ofstream logstream;
std::ofstream & cout = logstream;
#endif

void init_output(){
#ifdef DEBUG

#else
   logstream.open(LOG_FILE);  
#endif
}

void deinit_output(){
#ifdef DEBUG

#else
   logstream.close();
#endif
}
