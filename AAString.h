#ifndef _AAString_H_
#define _AAString_H_

#include <string.h>

#define AAS_MAXLEN 256

struct AAString
{
	mutable char Name[AAS_MAXLEN];
	mutable const char * tmpName;
	__forceinline bool operator==(const AAString & str) const
	{
		return(strcmp(tmpName ? tmpName : Name, str.tmpName ? str.tmpName : str.Name) == 0);
	}

	__forceinline bool operator<(const AAString & str) const
	{
		return(strcmp(tmpName ? tmpName : Name, str.tmpName ? str.tmpName : str.Name) < 0);
	}

	__forceinline void SetName(const char * str)const
	{
		strcpy(Name, str);
		tmpName = NULL;
	}

	__forceinline const char * GetName() const
	{
		return(tmpName ? tmpName : Name);
	}

	__forceinline AAString(const char * str)
	{
		tmpName = str;
		Name[0] = 0;
	}

	__forceinline AAString()
	{
		tmpName = NULL;
		Name[0] = 0;
	}
};

#endif
