#pragma once

#ifndef CONSOLE_LOG_HPP
#define CONSOLE_LOG_HPP

#include <chrono>
#include <ctime>
#include <experimental/source_location>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>

using std::experimental::source_location;

const std::string Black = "\u001b[30m";
const std::string Red = "\u001b[31m";
const std::string Green = "\u001b[32m";
const std::string Yellow = "\u001b[33m";
const std::string Blue = "\u001b[34m";
const std::string Magenta = "\u001b[35m";
const std::string Cyan = "\u001b[36m";
const std::string White = "\u001b[37m";
const std::string Reset = "\u001b[0m";
const std::string Underline = "\u001b[4m";

namespace console {
    enum class log_level : char {
        Info = '-',
        Warning = '!',
        Error = 'x',
        Success = '+',
        Debug = '*'
    };
    
    void time_now() {
        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::tm tn = *std::localtime(&end_time);
        std::cout << std::put_time(&tn, "%X");
    }

    template <class T>
    void log(T message, log_level log_level_ = log_level::Info,
             std::string color = Reset,
             std::experimental::source_location const source =
                 std::experimental::source_location::current()) {
        switch (log_level_) {
        case log_level::Info:
            if (color == Reset) color = Cyan;
            break;
        case log_level::Warning:
            if (color == Reset) color = Yellow;
            break;
        case log_level::Error:
            if (color == Reset) color = Red;
            break;
        case log_level::Success:
            if (color == Reset) color = Green;
            break;
        case log_level::Debug:
            if (color == Reset) color = Magenta;
            break;
        }

        std::cout << color << "[" << static_cast<char>(log_level_) << "] ";
        time_now();
        std::cout << " || " << Reset;
        std::cout
            << std::filesystem::path(source.file_name()).filename().string()
            << ":" << source.function_name() << ":" << source.line() << Reset;
        std::cout << color << " || " << Reset << message << std::endl;
    }
}; // namespace Console

#endif
