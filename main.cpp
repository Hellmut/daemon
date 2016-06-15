#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <config.hpp>
#include <daemonizer.hpp>
#include <outlet.hpp>

Daemonizer mdaemon;

void * Outlet_Work(void * ptr){
    unsigned int * nr = (unsigned int *)ptr;
    cout<<"Thread "<< *nr << " message."<<std::endl;
}


int main()
{
    int i=0;
    init_output();
#ifdef DEBUG
    cout<< "Damenon initialization skiped."<< std::endl;
#else    
    mdaemon.init_daemon();
    cout<<"First daemon started."<<std::endl;
#endif

for (unsigned int i=1; i<5 ;i++)    
    Outlet::Create_Instance(i);

sleep(50);

for (unsigned int i=1; i<5 ;i++)    
    Outlet::Delete_Instance(i);
   
#ifdef DEBUG
    cout<<"Daemon deinitialization skiped."<< std::endl;
#else
    mdaemon.deinit_daemon();
    cout<<"First daemon terminated."<<std::endl;
#endif
    deinit_output();
    std::exit(EXIT_SUCCESS);
}

