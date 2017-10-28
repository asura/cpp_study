#pragma once
#include <string>
#include <vector>

std::vector<std::wstring> SplitString(const std::wstring& s, wchar_t delimiter);
std::vector<std::wstring> SplitStringNaive(const std::wstring& s, wchar_t delimiter);
