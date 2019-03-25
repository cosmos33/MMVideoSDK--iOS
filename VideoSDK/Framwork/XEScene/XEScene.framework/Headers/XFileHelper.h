/******************************************************************************

 @File         XFI.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  封装了与文件相关的一系列操作

 @HISTORY:

******************************************************************************/

#ifndef _XFILEHELPER_H_
#define _XFILEHELPER_H_

#include "XTypes.h"
#include "XString.h"

class XFileHelper
{
public:
	/*
	* 使用文件相关功能之前，必须首先调用本函数
	* 
	* @notice	如果使用XFramework，则不必调用
	*
	* @param	szBaseDir 引擎根目录
	* @param	szLibraryDir 引擎库目录
	* @returns  总是xtrue
	*/
	static xbool		Init(const xchar* szBaseDir, const xchar* szDocuemnt, const xchar* szLibraryDir);
	
	/*
	* 使用文件相关功能之后（通常是程序关闭时）调用
	*
	* @notice	如果使用XFramework，则不必调用
	*
	* @returns  总是xtrue
	*/
	static xbool		Close();
	
	/*
	* 直接设置引擎根目录
	*
	* @param	szBaseDir 引擎根目录
	*/
	static void			SetBaseDir(const xchar* szBaseDir);

	/*
	* 获取引擎各目录
	*/
	static const xchar*	GetBaseDir();
	static const xchar*	GetLibraryDir();
    static const xchar* GetDocument();
	/*
	* 从一个路径中提取文件名
	*
	* @notice 带扩展名
	*
	* @param	szFile 路径
	* @param	szTitle 文件名
	*
	* @returns  异常或szFile以路径分隔符为结尾则返回xfalse，正常返回xtrue
	*/
	static xbool 		GetFileTitle(const xchar* szFile, xchar* szTitle);
	static xbool 		GetFileTitle(const xchar* szFile, XString& strTitle);

	/*
	* 从一个路径中提取文件所在目录
	*
	* @notice 结尾不带路径分隔符
	*
	* @param	szFile 路径
	* @param	szPath 文件目录
	*
	* @returns  异常或szFile以路径分隔符为结尾则返回xfalse，正常返回xtrue
	*/
	static xbool 		GetFilePath(const xchar* szFile, xchar* szPath);
	static xbool 		GetFilePath(const xchar* szFile, XString& strPath);

	/*
	* 判断文件的扩展名是否匹配
	*
	* @param	szFileName 文件名
	* @param	szExtension 扩展名
	*
	* @returns  匹配返回true，不匹配返回xfalse
	*/
	static xbool 		FileExtensionMatched(const xchar* szFileName, const xchar* szExtension);

	/*
	* 更改文件的后缀名
	*
	* @param	szFileName 文件名
	* @param	szNewExtension 新的扩展名
	*
	* @returns  总是xtrue
	*/
	static xbool 		ChangeExtension(xchar* szFileName, const xchar* szNewExtension);
	static xbool 		ChangeExtension(XString& strFileName, const xchar* szNewExtension);

	/*
	* 检查文件是否存在
	*
	* @param	szFileName 文件名
	*
	* @returns  存在返回xtrue，不存在返回xfalse
	*/
	static xbool 		FileExisted(const xchar * szFileName);
	
	/*
	* 移除文件扩展名
	*
	* @param	strFileName 文件名
	*
	*/
	static void 		RemoveExtension(XString& strFileName);

	/*
	* 文件名标准化，路径分隔符改为/
	*
	* @notice	IOS平台需要大写字母的路径，因此不将字母改成小写
	*
	* @param	szFileName 文件名
	*
	*/
	static void 		Normalize(xchar* szFileName);
	static void 		Normalize(const xchar* szSrcFileName, xchar* szDstFileName);

	static void			GetRelativePathNoBase(const xchar* szFullpath, const xchar* szParentPath, xchar* szRelativepath);
	static void			GetRelativePathNoBase(const xchar* szFullpath, const xchar* szParentPath, XString& strRelativePath);
	static void			GetFullPathNoBase(xchar* szFullpath, const xchar* szBaseDir, const xchar* szFilename);
	static void			GetFullPathNoBase(XString& strFullpath, const xchar* szBaseDir, const xchar* szFilename);
	static void			GetFullPath(xchar* szFullPath, const xchar* szFolderName, const xchar* szFileName);
	static void			GetFullPath(xchar* szFullPath, const xchar* szFileName);
	static void			GetFullPath(XString& strFullPath, const xchar* szFolderName, const xchar* szFileName);
	static void			GetFullPath(XString& strFullPath, const xchar* szFileName);
	static void			GetFullPathWithUpdate(XString& strFullPath, const xchar* szFileName, bool bNoCheckFileExist = false);
	static void			GetFullPathWithDocument(XString& strFullPath, const xchar* szFileName, bool bNoCheckFileExist = false);
	static void			GetRelativePath(const xchar* szFullPath, const xchar* szFolderName, xchar* szRelativePath);
	static void			GetRelativePath(const xchar* szFullPath, xchar* szRelativePath);
	static void			GetRelativePath(const xchar* szFullPath, const xchar* szFolderName, XString& strRelativePath);
	static void			GetRelativePath(const xchar* szFullPath, XString& strRelativePath);
};

#endif

