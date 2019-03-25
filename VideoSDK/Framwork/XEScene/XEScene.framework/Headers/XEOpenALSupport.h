//
// Created by HongjieFu on 2018/6/8.
//

/*
 This file contains code from version 1.1 and 1.4 of MyOpenALSupport.h taken from Apple's oalTouch version.
 The 1.4 version code is used for loading IMA4 files, however, this code causes very noticeable clicking
 when used to load wave files that are looped so the 1.1 version code is used specifically for loading
 wav files.
 */

#ifndef __XE_OPENAL_H
#define __XE_OPENAL_H

#ifdef __cplusplus
extern "C" {
#endif


#import <OpenAL/al.h>
#import <OpenAL/alc.h>
#import <CoreFoundation/CFURL.h>


//Taken from oalTouch MyOpenALSupport 1.1
void *XELoadWaveAudioData(CFURLRef inFileURL, ALsizei *outDataSize, ALenum *outDataFormat, ALsizei *outSampleRate);

void *XELoadCafAudioData(CFURLRef inFileURL, ALsizei *outDataSize, ALenum *outDataFormat, ALsizei *outSampleRate);

void *XEGetOpenALAudioData(CFURLRef inFileURL, ALsizei *outDataSize, ALenum *outDataFormat, ALsizei *outSampleRate);

#ifdef __cplusplus
}
#endif

#endif 


