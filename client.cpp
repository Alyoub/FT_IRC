#include "client.hpp"





client::client(){}

client::~client(){}

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
    this->IPadd = ipadd;
}
