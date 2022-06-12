#pragma once

#ifndef CPP_DIRS_HPP
#define CPP_DIRS_HPP

#include <iostream>
#include <cstdlib>

namespace dirs {
    #ifdef unix

    #include <limits.h>
    #include <unistd.h>

    char hn[HOST_NAME_MAX];
    char un[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);

    #endif

    #if defined(WIN32) || defined(_WIN64)
    char* hn = std::getenv("COMPUTERNAME");
    char* un = std::getenv("USERNAME");

    #endif

    const std::string hostname = std::string(hn);
    const std::string username = std::string(un);

}



#endif