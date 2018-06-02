
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2018
See the license in LICENSE
******************************************************/

#ifndef __FILE_UTILS_H
#define __FILE_UTILS_H

#include <windows.h>
#include <sys/stat.h>
#include <time.h>
#include "string.h"
#include "string_utils.h"
#include "array.h"

//! существует ли файл
bool FileExistsFile(const char *szPath);

//! существует ли директория
bool FileExistsDir(const char *szPath);

//! существует ли путь (файл или директория)
#define FileExistsPath(szPath)(FileExistsFile(szPath) || FileExistsDir(szPath))

//! типы списков для #FileGetList
enum FILE_LIST_TYPE
{
	//! файлы
	FILE_LIST_TYPE_FILES,

	//! директории
	FILE_LIST_TYPE_DIRS,

	//! все
	FILE_LIST_TYPE_ALL,
};

/*! возвращает массив со всеми данными находящимися по пути szPath, 
szPath может быть не канонизирован и необязательно должен заканчиваться слэшем, 
szPath уже может содержать фильтр (к примеру C:/*), но если его нет, тогда функция подставит сама
*/
Array<String> FileGetList(const char *szPath, FILE_LIST_TYPE type);

//! возвращает массив файлов в директории szPath
#define FileGetListFiles(szPath)(FileGetList(szPath, FILE_LIST_TYPE_FILES))

//! возвращает массив директорий в директории szPath
#define FileGetListDirs(szPath)(FileGetList(szPath, FILE_LIST_TYPE_DIRS))

//! возвращает массив файлов и директорий в директории szPath
#define FileGetListAll(szPath)(FileGetList(szPath, FILE_LIST_TYPE_ALL))


/*! возвращает список всех файлов или папок (в зависимости от type), 
szPath не должен содержать фильтров, может быть не канонизирован и без последнего слэша, 
szExt - расширение файла без точки
*/
Array<String> FileGetListRec(const char *szPath, FILE_LIST_TYPE type, const char *szExt = 0);


const char *FileBaseName(const char *szPath);

const char *FileDirName(char *szPath);


//! канонизация строки пути (приведение слэшей к единому виду), изменяет входящую строку szPath
const char *FileCanonizePath(char *szPath);

//! канонизация строки пути (приведение слэшей к единому виду), возвращает новую строку
String FileCanonizePathS(const char *szPath);

//! возвращает количество вложенности папки/файла
int FileCountNesting(const char *szPath);

//! возвращает путь на одно вложение меньше, то есть вырезает последний /
String FileGetPrevDir(const char *szPath);

//! есть ли в конце строки слэш?
bool FileExistsEndSlash(const char *szPath);

//! добавляет в конец строки слэш
String FileAppendSlash(const char *szPath);

//! входит ли szSubPath в szPath
bool FileExistsInPath(const char *szPath, const char *szSubPath);

//! установка файлу в строке szPath (путь) расширения szExt, если расширение уже было то будет заменено на новое
String FileSetStrExt(const char *szPath, const char *szExt);

//! сравнивает расширение файла в строке szPath с расширением szExt (без точки)
bool FileStrIsExt(const char *szPath, const char *szExt);


//! создание директорий, в том числе и вложенных
bool FileCreateDir(const char *szPath);

//! возвращает время последнего изменения файла
UINT FileGetTimeLastModify(const char *szPath);

//! возвращает размер файла в байтах
int FileGetSizeFile(const char *szPath);


#endif