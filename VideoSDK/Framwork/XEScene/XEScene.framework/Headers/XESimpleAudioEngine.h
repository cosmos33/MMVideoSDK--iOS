//
// Created by HongjieFu on 2018/6/8.
//


#import "XEAudioManager.h"

/**
 A wrapper to the XEAudioManager object.
 This is recommended for basic audio requirements. If you just want to play some sound fx
 and some background music and have no interest in learning the lower level workings then
 this is the interface to use.
 
 Requirements:
 - Firmware: OS 2.2 or greater 
 - Files: SimpleAudioEngine.*, CocosDenshion.*
 - Frameworks: OpenAL, AudioToolbox, AVFoundation
 @since v0.8
 */
@interface XESimpleAudioEngine : NSObject <XEAudioInterruptProtocol> {

    BOOL mute_;
    BOOL enabled_;
}

/** Background music volume. Range is 0.0f to 1.0f. This will only have an effect if willPlayBackgroundMusic returns YES */
@property(readwrite) float backgroundMusicVolume;
/** Effects volume. Range is 0.0f to 1.0f */
@property(readwrite) float effectsVolume;
/** If NO it indicates background music will not be played either because no background music is loaded or the audio session does not permit it.*/
@property(readonly) BOOL willPlayBackgroundMusic;

/** returns the shared instance of the XESimpleAudioEngine object */
+ (XESimpleAudioEngine *)sharedEngine;

/** Preloads a music file so it will be ready to play as background music */
- (void)preloadBackgroundMusic:(NSString *)filePath;

/** plays background music in a loop*/
- (void)playBackgroundMusic:(NSString *)filePath;

/** plays background music, if loop is true the music will repeat otherwise it will be played once */
- (void)playBackgroundMusic:(NSString *)filePath loop:(BOOL)loop;

/** stops playing background music */
- (void)stopBackgroundMusic;

/** pauses the background music */
- (void)pauseBackgroundMusic;

/** resume background music that has been paused */
- (void)resumeBackgroundMusic;

/** rewind the background music */
- (void)rewindBackgroundMusic;

/** returns whether or not the background music is playing */
- (BOOL)isBackgroundMusicPlaying;

/** plays an audio effect with a file path*/
- (ALuint)playEffect:(NSString *)filePath loop:(BOOL)loop;

/** stop a sound that is playing, note you must pass in the soundId that is returned when you started playing the sound with playEffect */
- (void)stopEffect:(ALuint)soundId;

/** plays an audio effect with a file path, pitch, pan and gain */
- (ALuint)playEffect:(NSString *)filePath loop:(BOOL)loop pitch:(Float32)pitch pan:(Float32)pan gain:(Float32)gain;

/** pause an audio */
- (void)pauseEffect:(ALuint)soundId;

/** pause all audioes */
- (void)pauseAllEffects;

/** resume an audio */
- (void)resumeEffect:(ALuint)soundId;

/** resume all audioes */
- (void)resumeAllEffects;

/** stop all audioes */
- (void)stopAllEffects;

/** preloads an audio effect */
- (void)preloadEffect:(NSString *)filePath;

/** unloads an audio effect from memory */
- (void)unloadEffect:(NSString *)filePath;

/** Gets a XESoundSource object set up to play the specified file. */
- (XESoundSource *)soundSourceForFile:(NSString *)filePath;

/** Shuts down the shared audio engine instance so that it can be reinitialised */
+ (void)end;

@end
