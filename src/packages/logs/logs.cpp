
            // Includes
#include "packages/logs/logs.hpp"

namespace Log {

    void Write(LogLevel logtype, const char* format, ...) {

        auto getCore = PluginComponent::getCore();
        if(!getCore) return;

        char buffer[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof buffer, format, args);
        va_end(args);
        getCore->logLn(logtype, "%s", buffer);
    }
}