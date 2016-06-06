#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <fstream>

#ifdef DEBUG
    using std::cout; 
#else
    #define LOG_FILE "./log.txt"
    extern std::ofstream logstream;
    extern std::ofstream & cout;
#endif

void init_output();
void deinit_output();
#endif
