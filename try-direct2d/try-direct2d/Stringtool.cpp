#include "stdafx.h"
#include "Stringtool.h"

Stringtool::Stringtool()
{
}

Stringtool::~Stringtool()
{
}


std::string Stringtool::JoinAsString(std::string string)
{
    return string;
}

std::wstring Stringtool::ToWString(const std::string& refSrc)
{
    std::vector<wchar_t> buffer(MultiByteToWideChar(CP_ACP, 0, refSrc.c_str(), -1, nullptr, 0));
    MultiByteToWideChar(CP_ACP, 0, refSrc.c_str(), -1, &buffer.front(), buffer.size());
    return std::wstring(buffer.begin(), buffer.end());
}
