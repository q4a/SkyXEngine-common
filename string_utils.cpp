
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

	while (szStr)
	{
		if ((szFound = strstr(szStr, szDelimiter)) == 0)
			break;

		iLen = szFound - szStr;
		//int iLen = (iLastPos - iBeginPos);
		if (isAllowEmpty || (!isAllowEmpty && iLen > 0))
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

	if (iBeginPos == 0 || (szStr && (isAllowEmpty || (!isAllowEmpty && strlen(szStr) > 0))))
		aStrings.push_back(szStr);

	return aStrings;
}

String StrWeld(const char *szDelimiter, const char *szStr1, ...)
{
	if (!szDelimiter || !szStr1)
		return "";

	String sNewStr = "";
	const char *szStrCurr = 0;
	va_list va;
	va_start(va, szStr1);

	szStrCurr = szStr1;
	while (szStrCurr)
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
	if (!szStr && strlen(szStr) <= 0)
		return "";

	int iStart = 0, iEnd = strlen(szStr), iCountFail = 0;

	for (int i = 0, il = strlen(szStr); i < il; ++i)
	{
		iCountFail = 0;

		for (int k = 0, kl = strlen(szSyms); k < kl; ++k)
		{
			if (szStr[i] == szSyms[k])
			{
				++iStart;
				break;
			}
			else
				++iCountFail;
		}

		if (iCountFail >= strlen(szSyms))
			break;
	}

	for (int i = strlen(szStr)-1; i >= 0; ++i)
	{
		iCountFail = 0;

		for (int k = 0, kl = strlen(szSyms); k < kl; ++k)
		{
			if (szStr[i] == szSyms[k])
			{
				--iEnd;
				break;
			}
			else
				++iCountFail;
		}

		if (iCountFail >= strlen(szSyms))
			break;
	}

	String sNewStr = szStr;
	return sNewStr.substr(iStart, iEnd - iStart);
}

String StrTrimL(const char *szStr, const char *szSyms)
{
	if (!szStr && strlen(szStr) <= 0)
		return "";

	int iStart = 0, iEnd = strlen(szStr), iCountFail = 0;

	for (int i = 0, il = strlen(szStr); i < il; ++i)
	{
		iCountFail = 0;

		for (int k = 0, kl = strlen(szSyms); k < kl; ++k)
		{
			if (szStr[i] == szSyms[k])
			{
				++iStart;
				break;
			}
			else
				++iCountFail;
		}

		if (iCountFail >= strlen(szSyms))
			break;
	}

	String sNewStr = szStr;
	return sNewStr.substr(iStart, iEnd - iStart);
}

String StrTrimR(const char *szStr, const char *szSyms)
{
	if (!szStr && strlen(szStr) <= 0)
		return "";

	int iStart = 0, iEnd = strlen(szStr), iCountFail = 0;

	for (int i = strlen(szStr) - 1; i >= 0; ++i)
	{
		iCountFail = 0;

		for (int k = 0, kl = strlen(szSyms); k < kl; ++k)
		{
			if (szStr[i] == szSyms[k])
			{
				--iEnd;
				break;
			}
			else
				++iCountFail;
		}

		if (iCountFail >= strlen(szSyms))
			break;
	}

	String sNewStr = szStr;
	return sNewStr.substr(iStart, iEnd - iStart);
}

//##########################################################################

String StrToLower(const char *szStr)
{
	String sNewStr = szStr;
	for (int i = 0, il = strlen(szStr); i < il; ++i)
	{
		sNewStr[i] = tolower((unsigned char)sNewStr[i]);
	}

	return sNewStr;
}

String StrToUpper(const char *szStr)
{
	String sNewStr = szStr;
	for (int i = 0, il = strlen(szStr); i < il; ++i)
	{
		sNewStr[i] = toupper((unsigned char)sNewStr[i]);
	}

	return sNewStr;
}