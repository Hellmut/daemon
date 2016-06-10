#ifndef OUTLET_HPP
#define OUTLET_HPP

class Outlet{
public:
    static unsigned int outlets_max_nr;
    static unsigned int outlets_cur_nr;
    static Outlet * Instance(unsigned int nr);
private:
    Outlet(){};
    Outlet(Outlet const &){};
    Outlet & operator=(Outlet const &){};
    static Outlet * pInstancet[4];
};




#endif
