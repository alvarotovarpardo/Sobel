#include "logger.h"

std::string Logger::m_sPath = std::filesystem::current_path().string();
std::ofstream Logger::logFile;

Logger::Logger()
{
    std::filesystem::path filePath = std::filesystem::path(m_sPath) / createFilename();
    logFile.open(filePath.string());
}

Logger::~Logger()
{
    if(logFile.is_open()) logFile.close();
}

Logger& Logger::getInstance()
{
    static Logger logInstance;
    return logInstance;
}

std::string Logger::createFilename() {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_FilterApp.log", tm);
    return std::string(buffer);
}

std::string Logger::getCurrentTime() {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    char buffer[9];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
    return std::string(buffer);
}


void Logger::log(const std::string& message, const char* func) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if(logFile.is_open())
    {
        logFile << "[" << getCurrentTime() << "] [" << func << "]: " << message << "\n";
        logFile.flush();
    }
}
