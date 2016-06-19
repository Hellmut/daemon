#ifndef OUTLET_HPP
#define OUTLET_HPP
#include <pthread.h>


class Outlet{
public:
    static unsigned int outlets_max_nr;
    static unsigned int outlets_cur_nr;
    static Outlet * Create_Instance(unsigned int nr);
    static void Delete_Instance(unsigned int nr);
    ~Outlet();
private:
    Outlet();
    Outlet(Outlet const &){};
    Outlet & operator=(Outlet const &){};
    static Outlet * pInstancet[4];
    pthread_t thread;
    unsigned int number;
};


#endif
