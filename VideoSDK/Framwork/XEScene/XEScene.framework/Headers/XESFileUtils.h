//
//  XESFileUtils.hpp
//  FaceDecorationKit
//
//  Created by HongjieFu on 2018/7/26.
//

#ifndef XESFileUtils_hpp
#define XESFileUtils_hpp

#include "xcommon/XTypes.h"
#include "xcommon/XString.h"
#include "xcommon/XArray.h"

class XESData {
public:
    XESData():_bytes(NULL),_size(0){};
    
    virtual ~XESData();

    void resize(size_t size);

    ssize_t getSize() const;

    virtual unsigned char *buffer() const;

private:
    unsigned char *_bytes;
    ssize_t _size;
};

class FileUtils {

public:

    static xbool AddSearchPath(const char *cRelativePath);

    static void RemoveSearchPath(const char *cRelativePath);

    static xbool FileExists(const xchar *xcFileName);

    static const XString JSONBuffer(const xchar *xcFileName);

    static const XString FullFilePath(const xchar *xcFileName);

    static const XString FilePath(const xchar *xcFileName);

    static xbool GetDataFromFile(const xchar *xcFileName,XESData &data);

public:
    static XArray<XString> m_SearchPaths;

private:
    friend class Director;
};

#endif /* XESFileUtils_hpp */
