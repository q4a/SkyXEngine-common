
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2018
See the license in LICENSE
******************************************************/

#include "string_utils.h"

Array<String> StrExplode(const char *szStr, const char *szDelimiter, bool isAllowEmpty)
{
	Array<String> aStrings;
	int iBeginPos = 0, iLen = 0;
	const char *szFound = 0;

	while(szStr)
	{
		if((szFound = strstr(szStr, szDelimiter)) == 0)
			break;

		iLen = szFound - szStr;
		//int iLen = (iLastPos - iBeginPos);
		if(isAllowEmpty || (!isAllowEmpty && iLen > 0))
		{
			char *szNewStr = new char[iLen + 1];
			memcpy(szNewStr, szStr, sizeof(char)* iLen);
			szNewStr[iLen] = 0;
			aStrings.push_back(szNewStr);
			mem_delete_a(szNewStr);
		}

		iBeginPos += iLen + 1;
		szStr += iLen + 1;
	}

	if(iBeginPos == 0 || (szStr && (isAllowEmpty || (!isAllowEmpty && strlen(szStr) > 0))))
		aStrings.push_back(szStr);

	return aStrings;
}

String StrWeld(const char *szDelimiter, const char *szStr1, ...)
{
	if(!szDelimiter || !szStr1)
		return "";

	String sNewStr = "";
	const char *szStrCurr = 0;
	va_list va;
	va_start(va, szStr1);

	szStrCurr = szStr1;
	while(szStrCurr)
	{
		sNewStr += szStrCurr;

		if(szStrCurr = va_arg(va, const char *))
			sNewStr += szDelimiter;
	}

	va_end(va);

	return sNewStr;
}

//##########################################################################

String StrTrim(const char *szStr, const char *szSyms)
{
	int iStrLen = strlen(szStr);
	int iSymsLen = strlen(szSyms);

	if(!szStr && iStrLen <= 0)
		return "";

	int iStart = 0, iEnd = iStrLen, iCountFail = 0;

	for(int i = 0, il = iStrLen; i < il; ++i)
	{
		iCountFail = 0;

		for(int k = 0, kl = iSymsLen; k < kl; ++k)
		{
			if(szStr[i] == szSyms[k])
			{
				++iStart;
				break;
			}
			else
				++iCountFail;
		}

		if(iCountFail >= iSymsLen)
			break;
	}

	for(int i = iStrLen - 1; i >= 0; ++i)
	{
		iCountFail = 0;

		for(int k = 0, kl = iSymsLen; k < kl; ++k)
		{
			if(szStr[i] == szSyms[k])
			{
				--iEnd;
				break;
			}
			else
				++iCountFail;
		}

		if(iCountFail >= iSymsLen)
			break;
	}

	String sNewStr = szStr;
	return(sNewStr.substr(iStart, iEnd - iStart));
}

String StrTrimL(const char *szStr, const char *szSyms)
{
	int iStrLen = strlen(szStr);
	int iSymsLen = strlen(szSyms);

	if(!szStr && iStrLen <= 0)
		return "";

	int iStart = 0, iEnd = iStrLen, iCountFail = 0;

	for(int i = 0, il = iStrLen; i < il; ++i)
	{
		iCountFail = 0;

		for(int k = 0, kl = iSymsLen; k < kl; ++k)
		{
			if(szStr[i] == szSyms[k])
			{
				++iStart;
				break;
			}
			else
				++iCountFail;
		}

		if(iCountFail >= iSymsLen)
			break;
	}

	String sNewStr = szStr;
	return sNewStr.substr(iStart, iEnd - iStart);
}

String StrTrimR(const char *szStr, const char *szSyms)
{
	int iStrLen = strlen(szStr);
	int iSymsLen = strlen(szSyms);

	if(!szStr && strlen(szStr) <= 0)
		return "";

	int iStart = 0, iEnd = iStrLen, iCountFail = 0;

	for(int i = iStrLen - 1; i >= 0; ++i)
	{
		iCountFail = 0;

		for(int k = 0, kl = iSymsLen; k < kl; ++k)
		{
			if(szStr[i] == szSyms[k])
			{
				--iEnd;
				break;
			}
			else
				++iCountFail;
		}

		if(iCountFail >= iSymsLen)
			break;
	}

	String sNewStr = szStr;
	return sNewStr.substr(iStart, iEnd - iStart);
}

//##########################################################################

String StrToLower(const char *szStr)
{
	String sNewStr = szStr;
	for(int i = 0, il = strlen(szStr); i < il; ++i)
	{
		sNewStr[i] = tolower((unsigned char)sNewStr[i]);
	}

	return sNewStr;
}

String StrToUpper(const char *szStr)
{
	String sNewStr = szStr;
	for(int i = 0, il = strlen(szStr); i < il; ++i)
	{
		sNewStr[i] = toupper((unsigned char)sNewStr[i]);
	}

	return sNewStr;
}



void StrCutMesh(const char* path, char* name)
{
	for(size_t i = 0; i<strlen(path); i++)
	{
		if(path[strlen(path) - i] == '\\')
		{
			if(i + 6 > 0 && i + 6 < strlen(path) &&
				(path[(strlen(path) - i) - 1] == 's' || path[(strlen(path) - i) - 1] == 'S') &&
				(path[(strlen(path) - i) - 2] == 'e' || path[(strlen(path) - i) - 2] == 'E') &&
				(path[(strlen(path) - i) - 3] == 'h' || path[(strlen(path) - i) - 3] == 'H') &&
				(path[(strlen(path) - i) - 4] == 's' || path[(strlen(path) - i) - 4] == 'S') &&
				(path[(strlen(path) - i) - 5] == 'e' || path[(strlen(path) - i) - 5] == 'E') &&
				(path[(strlen(path) - i) - 6] == 'm' || path[(strlen(path) - i) - 6] == 'M')
				)
			{
				memcpy(name, path + (strlen(path) - i) + 1, i - 1);
				name[(i - 1)] = 0;
				break;
			}
		}
	}
}

void StrCutName(const char* path, char* name)
{
	name[0] = 0;
	for(size_t i = 0; i < strlen(path); i++)
	{
		if(path[strlen(path) - i] == '\\')
		{
			memcpy(name, path + (strlen(path) - i) + 1, i - 1);
			name[(i - 1)] = 0;
			break;
		}
	}

	if(name[0] == 0)
	{
		sprintf(name, "%s", path);
	}
}

//парсинг строки (имени файла) str на имя папки path и имя файла name
//str = test_file_1.ex - path = test, name = file_1.ex
bool StrParsePathName(const char* str, char* path, char* name)
{
	bool IsTruePath = false;
	//обрезаем имя файла и папку
	for(size_t i = 0; i < strlen(str); i++)
	{
		if(str[i] == '_')
		{
			memcpy(path, str, sizeof(char)*i);
			path[i] = 0;
			sprintf(name, "%s", str + i + 1);
			IsTruePath = true;
			break;
		}
	}

	return IsTruePath;
}

