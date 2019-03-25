/******************************************************************************

@File         XEPathFunc.h

@Version       1.0

@Created      2017, 6, 14

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_PATHFUNC_H_
#define _XE_PATHFUNC_H_

#include <vector>
#include <string>
#include "XPlatform.h"

using std::vector;
using std::string;

//will not actually operate the files.
namespace XEPathFileTool
{
#if X_PLATFORM_WIN_DESKTOP
	// [WINDOWS ONLY]判定文件（夹）是否存在 
	bool IsFileOrDirExist(const char* pathname);
	// [WINDOWS ONLY]获取完整物理路径下指定后缀的文件
	std::vector<std::string> GetFileWithExt(const char* path, const char* ext);
	// [WINDOWS ONLY]使用系统命令删除文件夹,无QT环境，有QT环境请使用XEFileHelper::removePath
	bool DeleteDir(const char* pathname);
	// [WINDOWS ONLY]使用系统命令删除文件，无QT环境，有QT环境请使用XEFileHelper::removePath
	bool Deletefile(const string &strFilePath);
	void GetAllFormatFiles(string fileFolderPath, vector<string>& files, string fileExtension);
	// [WINDOWS ONLY]使用系统命令拷贝文件，无QT环境 ，有QT环境请使用XEFileHelper::CopyFileToPath
	bool Copyfile(const string &strFromPath, const string &strToPath);
	// [WINDOWS ONLY]
	bool CreateFolderByPath(const char* path);
#endif
	//如果reverse为true，转换为/(反斜杠)，否则为\(斜杠，Windows命令行识别，不识别/)
	void NormalPath(string& strFullName, bool reverse = true);
	void NormalPath(char *pFullName, bool reverse = true);
	//加密/解密路径
	void EncodePath(const string &strKey, string &strpath);
	void DecodePath(const string &strKey, string &strpath);
	// 获取应用程序目录路径,Android平台不支持!请使用JNI AssetManager或其它方法获取
	string GetAppPath();
	// 从完整路径中得到目录部分
	string GetPathDir(const string &strFullName);
	// 从完整的名字中得到名字(带后缀名)
	string GetFileName(const string& strFullName);
	// 获取后缀名
	string GetFileExt(const std::string &strName);
	// 去掉后缀名
	string GetFilePathExceptExt(const std::string &strName);
	// 获取相对路径
	bool GetRaletivePath(const string &strFullPath, const string &strParentPath, string &strRelativePath);
	// 判断相对路径
	bool IsRaletivePath(const string &strFullPath, const string &strParentPath);
	//简化路径,如将root/bb/../aa 变为root/aa 
	void ExpandPath(string &strPath);
	//分离字符串
	void SplitString(const string &str, const string &mak, vector<string> &vstr);
	//去除两端空白字符
	const string& Strtrim(string &s);

};

#endif


