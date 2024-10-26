#pragma once 




#include "Server.hpp"




class client
{
    private:

        int FD;
        std::string addIP;
    




    public :

    int getFD();
    void setFD(int fd);
    void setIPadd(std::string ipadd);




};
