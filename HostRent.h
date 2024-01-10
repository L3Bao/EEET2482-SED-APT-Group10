#ifndef HOSTRENT_H
#define HOSTRENT_H

class DateTime;
class Member;

class HostRent {
    DateTime* rentFrom;
    DateTime* rentTo;
    Member* host;

public:
    HostRent(DateTime* from, DateTime* to, Member* host);

    friend class System;

    friend class Member;

    friend class Skill;
};

#endif HOSTRENT_H