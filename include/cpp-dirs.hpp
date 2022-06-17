#pragma once

#ifndef CPP_DIRS_HPP
#define CPP_DIRS_HPP

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include "console-log.hpp"

namespace fs = std::filesystem;
using ll = console::log_level;

#ifdef unix
#include <limits.h>
#include <unistd.h>
#endif

std::string empty_dir(std::string dir) {
    if (fs::is_directory(dir))
        return dir;
    else
        return "";
}
// note: add overhead comments for each func
class dirs {
  private:
    std::string application_name;
    std::string corporation;
    std::string joint;
    std::string path;
#ifdef unix
    char hn[HOST_NAME_MAX];
    char un[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);

#endif

#if defined(WIN32) || defined(_WIN64)
    const char *hn = std::getenv("COMPUTERNAME");
    const char *un = std::getenv("USERNAME");
    const char *h = std::getenv("USERPROFILE");
    const char *temp = std::getenv("TEMP");
    const char *dd = std::getenv("APPDATA");
    const char *ldd = std::getenv("LOCALAPPDATA");
    const char *pub = std::getenv("PUBLIC");
    std::string v = std::string(h) + "\\Videos";
    std::string doc = std::string(h) + "\\Documents";
    std::string pic = std::string(h) + "\\Pictures";
    std::string down = std::string(h) + "\\Downloads";
    std::string desk = std::string(h) + "\\Desktop";
    std::string aud = std::string(h) + "\\Music";
#endif

  public:
    const std::string hostname = std::string(hn);
    const std::string username = std::string(un);

  public:
    dirs() = default;
    dirs(std::string corp, std::string app_name)
        : application_name(app_name), corporation(corp) {
        this->joint = corporation + "/" + application_name;
    }
    dirs(std::string p): path(p) {
        #if defined(WIN32) || defined(_WIN64)
        std::replace( this->path.begin(), this->path.end(), '/', '\\');
        #endif
    }

    std::string get_joint(){
        return this->joint;
    }

    void create(){
        // warning: use cppm module when available
        if(!fs::is_directory(this->path)){
            console::log("Creating directory " + this->path);
            fs::create_directories(this->path);
        }
        else console::log("Directory `" + this->path + "` Already exists.", ll::Debug);
    }

    dirs home_dir(){
        return dirs(home() + "/" + joint);
    }

    // __________ Static Functions __________
    static const std::string home() {
        dirs d;
        return empty_dir(std::string(d.h));
    }
    static const std::string cache() {
        dirs d;
        return empty_dir(std::string(d.temp));
    }
    static const std::string data_dir() {
        dirs d;
        return empty_dir(std::string(d.dd));
    }
    static const std::string data_local_dir() {
        dirs d;
        return empty_dir(std::string(d.ldd));
    }
    static const std::string public_dir() {
        dirs d;
        return empty_dir(std::string(d.pub));
    }
    static const std::string video() {
        dirs d;
        return empty_dir(d.v);
    }
    static const std::string documents() {
        dirs d;
        return empty_dir(d.doc);
    }
    static const std::string pictures() {
        dirs d;
        return empty_dir(d.pic);
    }
    static const std::string downloads() {
        dirs d;
        return empty_dir(d.down);
    }
    static const std::string desktop() {
        dirs d;
        return empty_dir(d.desk);
    }

    static const std::string audio() {
        dirs d;
        return empty_dir(d.aud);
    }
};
#endif