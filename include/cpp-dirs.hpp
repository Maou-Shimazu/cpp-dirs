#pragma once

#ifndef CPP_DIRS_HPP
#define CPP_DIRS_HPP

#include <cstdlib>
#include <filesystem>
#include <iostream>

#ifdef unix
#include <limits.h>
#include <unistd.h>
#endif

std::string empty_dir(std::string dir) {
    auto dir_exists = [](const auto &file) {
        return std::filesystem::is_directory(file) ? true : false;
    };
    if (dir_exists(dir))
        return dir;
    else
        return "";
}
// note: add overhead comments for each func
class dirs {
  private:
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
    static const std::string home() {
        dirs d;
        const std::string home = std::string(d.h);
        return empty_dir(home);
    }
    static const std::string cache() {
        dirs d;
        const std::string cache = std::string(d.temp);
        return empty_dir(cache);
    }
    static const std::string data_dir() {
        dirs d;
        const std::string data_dir = std::string(d.dd);
        return empty_dir(data_dir);
    }
    static const std::string data_local_dir() {
        dirs d;
        const std::string data_local_dir = std::string(d.ldd);
        return empty_dir(data_local_dir);
    }
    static const std::string video() {
        dirs d;
        const std::string video = d.v;
        return empty_dir(video);
    }
    static const std::string documents() {
        dirs d;
        const std::string documents = d.doc;
        return empty_dir(documents);
    }
    static const std::string pictures() {
        dirs d;
        const std::string pictures = d.pic;
        return empty_dir(pictures);
    }
    static const std::string downloads() {
        dirs d;
        const std::string downloads = d.down;
        return empty_dir(downloads);
    }
    static const std::string desktop() {
        dirs d;
        const std::string desktop = d.desk;
        return empty_dir(desktop);
    }

    static const std::string audio() {
        dirs d;
        const std::string audio = d.aud;
        return empty_dir(audio);
    }

    static const std::string public_dir() {
        dirs d;
        const std::string public_dir = std::string(d.pub);
        return empty_dir(public_dir);
    }
};
#endif