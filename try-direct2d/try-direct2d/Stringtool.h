#pragma once

#include <string>

class Stringtool
{
public:
    Stringtool();
    ~Stringtool();

    template<typename Head, typename... Rest>
    static std::string GetAsString(Head head, Rest... rest)
    {
        std::ostringstream oss;
        oss << head;
        std::string string = JoinAsString(oss.str(), rest...);

        return string;
    }
    static std::wstring ToWString(const std::string& refSrc);
private:
    static std::string JoinAsString(std::string string);

    template<typename Head, typename... Rest>
    static std::string JoinAsString(std::string string, Head head, Rest... rest)
    {
        std::ostringstream oss;
        oss << string << head;

        return JoinAsString(oss.str(), rest...);
    }
};

