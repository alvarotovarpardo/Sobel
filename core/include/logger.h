#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

#define LOG(msg) Logger::getInstance().log(msg, __func__)

class Logger 
{
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance();
    void log(const std::string& message, const char* func);

private:
    std::mutex m_mutex;
    Logger();
    ~Logger();
    static std::string m_sPath;
    static std::ofstream logFile;
    static std::string getCurrentTime();
    static std::string createFilename();
};

#endif // !LOGGER_H
