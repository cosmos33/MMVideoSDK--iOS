//-----------------------------------------
//FileName:XAndroidSys.h
//-----------------------------------------

#ifndef _X_ANDROID_SYS_H_
#define _X_ANDROID_SYS_H_

#include "XTypes.h"
#if X_PLATFORM_ANDROID

#include <errno.h>
#include <android/log.h>
#include <pthread.h>
#include <jni.h>

#define x_snprintf snprintf
#define x_isnan isnan

X_FORCEINLINE xuint32 XSys::GetFileTimeStamp(const char* szFileName)
{

    struct stat fileStat;
    stat(szFileName, &fileStat);
    return (xuint32)(fileStat.st_mtime);
}

X_FORCEINLINE xuint32 XSys::GetFileSize(const char* szFileName)
{
    struct stat fileStat;
    stat(szFileName, &fileStat);
    return (xuint32)(fileStat.st_size);
}

X_FORCEINLINE  xuint32 XSys::ChangeFileAttributes(const char* szFileName, int mode)
{
    return chmod( szFileName,mode);
}

X_FORCEINLINE bool XSys::IsFileExist(const char* szFileName)
{
    if( access(szFileName, 0) == 0)
        return true;
    return false;
}

X_FORCEINLINE bool XSys::DeleteFile(const char* szFile)
{
    if( remove(szFile) == -1)
        return xfalse;

    return xtrue;
}

X_FORCEINLINE bool XSys::CopyFile(const char* src,const char* des,bool bFailIfExists)
{
    const int BUF_SIZE = 1024;
    FILE* fromfd = NULL;
    FILE*  tofd = NULL;
    int bytes_read = 0;
    int bytes_write = 0;
    char buffer[BUF_SIZE];
    char *ptr;

    /*open source file*/
    if((fromfd = fopen(src,"r")) == NULL)
    {
        //fprintf(stderr,"Open source file failed:%s\n",strerror(errno));
        return xfalse;
    }
    /*create dest file*/
    if((tofd = fopen(des,"wb")) == NULL)
    {
        //fprintf(stderr,"Create dest file failed:%s\n",strerror(errno));
        fclose(fromfd);
        return 0;
    }

    /*copy file code*/
    while((bytes_read = fread(buffer,1,BUF_SIZE,fromfd)))
    {
        if(bytes_read ==-1 && errno!=EINTR)
            break; /*an important mistake occured*/
        else if(bytes_read == 0)
        {
            break;
        }
        else if( bytes_read > 0 )
        {
            bytes_write = fwrite(buffer,1,bytes_read,tofd);
            ASSERT(bytes_write == bytes_read);
        }
    }
    fclose(fromfd);
    fclose(tofd);
    return xtrue;
}

X_FORCEINLINE bool XSys::MoveFile(const char* src,const char* des)
{
    if(!CopyFile(src,des,false))
        return false;
    if( !DeleteFile(src))
        return false;    
    return  true;
}



X_FORCEINLINE bool XSys::CreateDirectory(const char* szDir)
{
    if( mkdir(szDir, S_IRWXU) == -1)
        return xfalse;

    return  xtrue;

}



X_FORCEINLINE void XSys::Sleep(unsigned int nMilliSecond)
{
    ::usleep(nMilliSecond * 1000);
}

X_FORCEINLINE xuptrint XSys::GetCurrentThreadID()
{
	return (xuptrint)pthread_self();
}

#define XSys_GetCurrentFrame(frame_cur) __asm\
{\
    mov frame_cur, ebp\
}


#define X_CPPTEXT_TO_GB2312(x) X_UTF8_TO_GB2312(x)
#define X_GB2312_TO_CPPTEXT(x) X_GB2312_TO_UTF8(x)
#define X_CPPTEXT_TO_UTF8(x) (x)
#define X_UTF8_TO_CPPTEXT(x) (x)

#define XSTR_CPPTEXT_TO_GB2312(x) XSTR_UTF8_TO_GB2312(x)
#define XSTR_GB2312_TO_CPPTEXT(x) XSTR_GB2312_TO_UTF8(x)
#define XSTR_CPPTEXT_TO_UTF8(x) (x)
#define XSTR_UTF8_TO_CPPTEXT(x) (x)
/*
#define X_CPPTEXT_TO_GB2312(x) (x)
#define X_GB2312_TO_CPPTEXT(x) (x)
#define X_CPPTEXT_TO_UTF8(x) X_GB2312_TO_UTF8(x)
#define X_UTF8_TO_CPPTEXT(x) X_UTF8_TO_GB2312(x)

#define XSTR_CPPTEXT_TO_GB2312(x) (x)
#define XSTR_GB2312_TO_CPPTEXT(x) (x)
#define XSTR_CPPTEXT_TO_UTF8(x) XSTR_GB2312_TO_UTF8(x)
#define XSTR_UTF8_TO_CPPTEXT(x) XSTR_UTF8_TO_GB2312(x)
*/

template<typename T>
struct XEngineThreadLocal
{
    XEngineThreadLocal()
    {
        pthread_key_create(&key, XEngineThreadLocal<T>::_ClearStorage);
    }
    XEngineThreadLocal(const T& other) : XEngineThreadLocal()
    {
        m_InitData = other;
    }
    XEngineThreadLocal<T>& operator=(const T& other)
    {
        Data() = other;
        return *this;
    }
    operator const T&() const
    {
        return Data();
    }
    operator T&()
    {
        return Data();
    }

private:
    pthread_key_t key;
    T m_InitData;
    static void _ClearStorage(void* pData)
    {
        if(pData)
            delete (T*)pData;
    }
    T& Data() const
    {
        void* data = pthread_getspecific(key);
        if(!data)
        {
            data = new T(m_InitData);
            pthread_setspecific(key, data);
        }
        return *(T*)data;
    }
};
#define XThreadLocal(of_type) XEngineThreadLocal<of_type>


#define  LOG_TAG    "XEngine"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

// 客房端要对其赋值
extern JavaVM* g_pJVM;

#endif //X_PLATFORM_ANDROID

#endif //_A_ANDROID_SYS_H_

