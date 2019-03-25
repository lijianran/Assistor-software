#pragma once

#include <string>
#include <vector>
#include <sstream>
using namespace std;

static std::string& trim(std::string &s)
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

static bool ProcessTitles(vector<string> titlestrings, string line, vector<int> &titileIndexs)
{
	//读入标题
	vector<string> titles;
	istringstream data(line);

	string title;
	while (getline(data, title, ','))
	{
		titles.push_back(trim(title));
	}
	//寻找需要的标题
	bool flag = false;
	for (unsigned int j = 0; j < titlestrings.size(); j++)
	{
		for (unsigned int i = 0; i < titles.size(); i++)
		{
			if (titles[i] == titlestrings[j])
			{
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}
	if (!flag)
		return false;

	for (unsigned int j = 0; j < titlestrings.size(); j++)
	{
		bool flag = false;
		for (unsigned int i = 0; i < titles.size(); i++)
		{
			if (titles[i] == titlestrings[j])
			{
				titileIndexs.push_back(i);
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			titileIndexs.push_back(-1);
		}
	}
	return true;
}

static char* ConvertLPWSTRToLPSTR(LPWSTR lpwszStrIn)
{
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL)
	{
		int nInputStrLen = wcslen(lpwszStrIn);

		// Double NULL Termination

		int nOutputStrLen = WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;

		pszOut = new char[nOutputStrLen];

		if (pszOut)
		{
			memset(pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}