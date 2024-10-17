#include "client.hpp"





client::client(){}

client::~client(){}

int client::getFd()
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
