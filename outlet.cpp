#include <outlet.hpp>
#include <config.hpp>
#include <iostream>

unsigned int Outlet::outlets_max_nr = 4;
unsigned int Outlet::outlets_cur_nr = 0;
Outlet* Outlet::pInstancet[4] = {NULL};

Outlet * Outlet::Instance(unsigned int nr){
    if (outlets_cur_nr < outlets_max_nr){
        pInstancet[outlets_cur_nr] = new Outlet;
        outlets_cur_nr++;
        cout << "Outlet instance nr. "<< outlets_cur_nr << " created"<<std::endl;
    }
    else
    {
        cout << "Outlet instance creation filed" <<std::endl;
    }
    return pInstancet[outlets_cur_nr - 1];
        
}

