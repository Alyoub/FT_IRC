#include "Server.hpp"

#include "client.hpp"




int client::getFD()
{
    return this->FD;
}
void client::setFD(int fd)
{
    this->FD = fd;
}
void client::setIPadd(std::string ipadd)
{
    this->addIP = ipadd;
}