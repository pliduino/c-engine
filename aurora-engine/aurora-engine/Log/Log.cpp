#include "Log.h"

std::string ELogVerbosity::EnumToString(ELogVerbosity::Type e)
{
    switch (e)
    {
    case Fatal:
        return "Fatal";
    case Error:
        return "Error";
    case Warn:
        return "Warn";
    case Info:
        return "Info";
    case Debug:
        return "Debug";
    default:
        return "";
    }
}