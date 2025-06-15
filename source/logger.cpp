#include "Logger.h"
#include <fstream>
#include <ctime>
using namespace std;

void Logger::Log(const string& message) {
    std::ofstream log("game.log", std::ios::app);
    if (log) {

        time_t now = time(nullptr);
        tm localTime;
        localtime_s(&localTime, &now);

        
        char timeBuffer[32];
        std::strftime(timeBuffer, sizeof(timeBuffer), "[%A, %d %B %Y %I:%M:%S %p]", &localTime);

      
        log << timeBuffer << " - " << message << endl;
    }
}
