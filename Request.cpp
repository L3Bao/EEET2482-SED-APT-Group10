#include "Request.h"

Request::Request(DateTime *from, DateTime *to, Member *member) {
    this->requestFrom = from;
    this->requestTo = to;
    this->requestingMember = member;
}