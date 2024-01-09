#ifndef REQUEST_H
#define REQUEST_H

#include "DateTime.h"

class Member;
class DateTime;

class Request {
    DateTime* requestFrom;
    DateTime* requestTo;
    Member* requestingMember;

public:
    Request(DateTime *from, DateTime *to, Member *member);

    friend class System;

    friend class Member;
};

#endif