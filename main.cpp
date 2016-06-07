#include <iostream>
#include <cstdlib>

#include <config.hpp>
#include <daemonizer.hpp>

Daemonizer daemon;

int main()
{
    int i=0;
    init_output();
#ifdef DEBUG
    cout<< "Damenon initialization skiped."<< std::endl;
#else    
    daemon.init_daemon();
    cout<<"First daemon started."<<std::endl;
#endif
    

    
#ifdef DEBUG
    cout<<"Daemon deinitialization skiped."<< std::endl;
#else
    daemon.deinit_daemon();
    cout<<"First daemon terminated."<<std::endl;
#endif
    deinit_output();
    std::exit(EXIT_SUCCESS);
}

