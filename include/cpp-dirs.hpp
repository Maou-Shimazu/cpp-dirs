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

#if defined(__unix__)
#include <limits.h>
#include <unistd.h>
#endif

std::string empty_dir(std::string dir) {
    if (fs::is_directory(dir))
        return dir;
    else
        return "";
}

// todo: look into replacing these with c++ funcs. eg fgets for getline
std::string process(std::string command){
    char buffer[128];
    std::string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
       return "popen failed!";
     while (!feof(pipe)) {
       if (fgets(buffer, 128, pipe) != NULL)
          result += buffer;
    }
    pclose(pipe);
    return result;
 }

// note: add overhead comments for each func
class dirs {
  private:
    std::string application_name;
    std::string corporation;
    std::string joint;
    std::string path;
#if defined(__unix__)
    char hn[HOST_NAME_MAX + 1];
    char un[LOGIN_NAME_MAX + 1];
    int x = gethostname(hn, HOST_NAME_MAX + 1);
    int y = getlogin_r(un, LOGIN_NAME_MAX + 1);
    const char* h = std::getenv("HOME");
    std::string temp = process("xdg-user-dir TEMP");
    std::string dd = process("xdg-user-dir DATA");
    std::string ldd = process("xdg-user-dir LOCAL");
    std::string pub = process("xdg-user-dir PUBLIC");
    std::string v = std::string(h) + "/Videos";
    std::string doc = std::string(h) + "/Documents";
    std::string pic = std::string(h) + "/Pictures";
    std::string down = std::string(h) + "/Downloads";
    std::string desk = std::string(h) + "/Desktop";
    std::string aud = std::string(h) + "/Music";

#endif

#if defined(__WIN32__) || defined(__WIN64__)
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

    // todo: add linux support
    // ________ Constructors ________
    dirs() = default;
    dirs(std::string corp, std::string app_name)
        : application_name(std::move(app_name)), corporation(std::move(corp)) {
        this->joint = corporation + "/" + application_name;
    }
    explicit dirs(std::string p): path(std::move(p)) {
        #if defined(__WIN32__) || defined(__WIN64__)
        std::replace( this->path.begin(), this->path.end(), '/', '\\');
        #endif
    }

    // _________ Member Function _________
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
    dirs cache_dir(){
        return dirs(cache() + "/" + joint);
    }
    dirs data_dir(){
        return dirs(data() + "/" + joint);
    }
    dirs local_data_dir(){
        return dirs(local_data() + "/" + joint);
    }
    dirs public_dir(){
        return dirs(public_folder() + "/" + joint);
    }
    dirs video_dir(){
        return dirs(video() + "/" + joint);
    }
    dirs documents_dir(){
        return dirs(documents() + "/" + joint);
    }
    dirs pictures_dir(){
        return dirs(pictures() +  "/" + joint);
    }
    dirs downloads_dir() {
        return dirs(downloads() + "/" + joint);
    }
    dirs desktop_dir() {
        return dirs(desktop() + "/" + joint);
    }
    dirs audio_dir() {
        return dirs(audio() + "/" + joint);
    }

    // __________ Static Functions __________
    static const std::string home() {
        return empty_dir(std::string(dirs().h));
    }
    static const std::string cache() {
        return empty_dir(std::string(dirs().temp));
    }
    static std::string data() {
        return empty_dir(std::string(dirs().dd));
    }
    static std::string local_data() {
        return empty_dir(std::string(dirs().ldd));
    }
    static std::string public_folder() {
        return empty_dir(std::string(dirs().pub));
    }
    static std::string video() {
        return empty_dir(dirs().v);
    }
    static std::string documents() {
        return empty_dir(dirs().doc);
    }
    static std::string pictures() {
        return empty_dir(dirs().pic);
    }
    static std::string downloads() {
        return empty_dir(dirs().down);
    }
    static std::string desktop() {
        return empty_dir(dirs().desk);
    }
    static std::string audio() {
        return empty_dir(dirs().aud);
    }
};
#endif
