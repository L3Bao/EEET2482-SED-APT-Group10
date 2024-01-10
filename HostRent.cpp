#include "HostRent.h"

HostRent::HostRent(DateTime *from, DateTime *to, Member *host) {
    this->rentFrom = from;
    this->rentTo = to;
    this->host = host;
}