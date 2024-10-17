#pragma once 





#include "server.hpp"




class client
{
    private :
        int FD;
        std::string IPadd;




    public :
    client();
    ~client();

    int getFd();

    void setFD(int fd);
    void setIPadd(std::string ipadd);


};