#include "SplitString.h"
#include <sstream>

std::vector<std::wstring> SplitString(const std::wstring &original, wchar_t delimiter)
{
    std::vector<std::wstring> result;
    std::wistringstream ss(original);
    std::wstring item;
    while (std::getline(ss, item, delimiter))
	{
		if (!item.empty())
		{
            result.push_back(item);
        }
    }
    return result;
}

std::vector<std::wstring> SplitStringNaive(const std::wstring &original, wchar_t delimiter)
{
    std::vector<std::wstring> result;
    std::wstring item;
    for (wchar_t ch : original) {
        if (ch == delimiter)
		{
            if (!item.empty())
			{
                result.push_back(item);
			}
            item.clear();
        }
        else
		{
            item += ch;
        }
    }
    if (!item.empty())
	{
		result.push_back(item);
	}
    return result;
}
