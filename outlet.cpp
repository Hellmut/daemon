#include <outlet.hpp>
#include <config.hpp>
#include <iostream>


extern void * Outlet_Work(void * ptr);

unsigned int Outlet::outlets_max_nr = 4;
unsigned int Outlet::outlets_cur_nr = 0;
Outlet* Outlet::pInstancet[4] = {NULL};

Outlet * Outlet::Create_Instance(unsigned int nr){
    if (outlets_cur_nr < outlets_max_nr){
        pInstancet[outlets_cur_nr] = new Outlet;
        outlets_cur_nr++;
        cout << "Outlet instance nr. "<< outlets_cur_nr << " created"<<std::endl;
    }
    else{
        cout << "Outlet instance creation filed" <<std::endl;
    }
    return pInstancet[outlets_cur_nr - 1];        
}

void Outlet::Delete_Instance(unsigned int nr){
    if (outlets_cur_nr > 0){
       delete pInstancet[outlets_cur_nr-1];
       outlets_cur_nr--;
       cout << "Outlet instance nr. "<< outlets_cur_nr << " deleted"<<std::endl;
    }
    else{
        cout << "Outlet instance deletion filed" <<std::endl;
    }        
}

Outlet::Outlet(){
     cout << "Outlet Constructor nr:"<< Outlet::outlets_cur_nr <<std::endl;
    number = Outlet::outlets_cur_nr + 1;
    pthread_create( &thread, NULL, Outlet_Work, (void *)&number);
}

Outlet::~Outlet(){ 
    cout << "Outlet Destructor nr:"<< Outlet::outlets_cur_nr <<std::endl;
    pthread_join( thread, NULL);
}
