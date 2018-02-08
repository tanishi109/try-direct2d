#pragma once
class Debug
{
public:
    Debug();
    ~Debug();
    template<typename Head, typename... Rest>
    static void log(Head head, Rest... rest);
private:
    static std::ostringstream& joinLog(std::ostringstream& oss);
    template<typename Head, typename... Rest>
    static std::ostringstream& joinLog(std::ostringstream& oss, Head head, Rest... rest);
};

template<typename Head, typename... Rest>
void Debug::log(Head head, Rest... rest) {
    std::ostringstream oss;
    oss << " " << head;
    std::ostringstream& result = joinLog(oss, rest...);
    oss << "\n";
    OutputDebugStringA(result.str().c_str());
}

template<typename Head, typename... Rest>
std::ostringstream& Debug::joinLog(std::ostringstream& oss, Head head, Rest... rest) {
    oss << " " << head;
    return joinLog(oss, rest...);
}
