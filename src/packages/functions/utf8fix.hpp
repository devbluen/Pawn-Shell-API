
#ifdef _WIN32
#include <windows.h>
#endif

#include <string>

std::string Utf8ToCP1252(const std::string& utf8)
{
#ifdef _WIN32
    if (utf8.empty())
        return {};

    int wideSize = MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8.c_str(),
        -1,
        nullptr,
        0
    );

    if (wideSize <= 0)
        return {};

    std::wstring wide(wideSize, L'\0');

    MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8.c_str(),
        -1,
        wide.data(),
        wideSize
    );

    int cpSize = WideCharToMultiByte(
        1252,
        0,
        wide.c_str(),
        -1,
        nullptr,
        0,
        nullptr,
        nullptr
    );

    if (cpSize <= 0)
        return {};

    std::string cp1252(cpSize, '\0');

    WideCharToMultiByte(
        1252,
        0,
        wide.c_str(),
        -1,
        cp1252.data(),
        cpSize,
        nullptr,
        nullptr
    );

    if (!cp1252.empty() && cp1252.back() == '\0')
        cp1252.pop_back();

    return cp1252;
#else
    return utf8;
#endif
}