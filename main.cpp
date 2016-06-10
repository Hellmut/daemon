#include <iostream>
#include <cstdlib>

#include <config.hpp>
#include <daemonizer.hpp>
#include <outlet.hpp>

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
    
Outlet::Instance(1);
Outlet::Instance(2);
Outlet::Instance(3);
Outlet::Instance(4);
Outlet::Instance(5);    
#ifdef DEBUG
    cout<<"Daemon deinitialization skiped."<< std::endl;
#else
    daemon.deinit_daemon();
    cout<<"First daemon terminated."<<std::endl;
#endif
    deinit_output();
    std::exit(EXIT_SUCCESS);
}

