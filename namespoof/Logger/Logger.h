#pragma once
#include <fstream>
#include <cstdarg>

__forceinline void writelog(const char* fmt, ...) {
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsprintf_s(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    char* value;
    size_t size;

    _dupenv_s(&value, &size, "APPDATA");

    std::string roam = (value + std::string("\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState\\Milkyway\\Logs\\"));
    std::string filePath = roam + "logs.txt";

    std::ofstream outputFile(filePath, std::ios::app);
    if (outputFile.is_open()) {
        outputFile << buffer << std::endl;
        outputFile.close();
    }
    else {
    }

    free(value);
}