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
    const char* hn = std::getenv("COMPUTERNAME");
    const char* un = std::getenv("USERNAME");
    const char* h = std::getenv("USERPROFILE");
    const char* temp = std::getenv("TEMP");
    const char* dd = std::getenv("APPDATA");
    const char* ldd = std::getenv("LOCALAPPDATA");
    const char* pub = std::getenv("PUBLIC");
    std::string v = std::string(h) + "\\Videos";
    std::string doc = std::string(h) + "\\Documents";
    std::string pic = std::string(h) + "\\Pictures";
    std::string down = std::string(h) + "\\Downloads";
    std::string desk = std::string(h) + "\\Desktop";
    std::string aud = std::string(h) + "\\Music";
    #endif

    const std::string hostname = std::string(hn);
    const std::string username = std::string(un);
    const std::string home = std::string(h);
    const std::string cache = std::string(temp);
    const std::string data_dir = std::string(dd);
    const std::string data_local_dir = std::string(ldd);
    const std::string public_dir = std::string(pub);
    const std::string video = v;
    const std::string documents = doc;
    const std::string pictures = pic;
    const std::string downloads = down;
    const std::string desktop = desk;
    const std::string audio = aud;
}



#endif