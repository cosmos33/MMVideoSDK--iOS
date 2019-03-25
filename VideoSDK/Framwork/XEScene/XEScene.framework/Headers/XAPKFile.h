/******************************************************************************

@File         XAPKFile.h

@Version       1.0

@Created      2017, 12, 19

@Description  ÎÄ¼þ²Ù×÷

@HISTORY:

******************************************************************************/

#ifndef _XAPKFILE_H_
#define _XAPKFILE_H_

#include "XTypes.h"
#if X_PLATFORM_ANDROID
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

void XAPKFile_GlobalInit(JNIEnv* env, jobject assetManager);
void XAPKFile_GlobalRelease(JNIEnv* env);

class XAPKFile
{
public:
				XAPKFile();
				~XAPKFile();

    bool			Open(const char* filename);
    void			Close();
    int			Read(void* buffer, size_t count);
    int			Size();
    
private:
    AAsset*		m_pAsset;
};

#endif // X_PLATFORM_ANDROID
#endif	//	_AAPKFILEMAN_H_
