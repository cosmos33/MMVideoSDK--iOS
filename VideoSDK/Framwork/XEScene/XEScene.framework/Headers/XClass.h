/******************************************************************************

@File         XClass.h

@Version       1.0

@Created      2018/12/17

@HISTORY:

******************************************************************************/
#ifndef _XE_CLASS_H_
#define _XE_CLASS_H_

#include "XTypes.h"

#define X_CLASS_DEF(T) virtual const xchar* GetClassName()const override{return #T;}
#define X_EEH_FILE//EXPORT[for lua, etc]: EEH: ENGINE- ELIMINATE HEAD FILE, eliminate an entire head-file if found this in a head file.
#define X_EMG_BEGIN//EXPORT[for lua, etc]: EMG: ENGINE - MARK as GREP, place this line in a file if you want to greedily analyze the code manually.(otherwise will only analyze the code begin as namespace, class, struct, enum, etc.)
#define X_EMG_END//EXPORT[for lua, etc]: EMG: ENGINE - MARK as GREP, place this line in a file if you want to greedily analyze the code manually.(otherwise will only analyze the code end with },;)
#define X_ECB_AUTO(T, ...)//EXPORT[for lua,etc.]: ECB: ENGINE - ELIMINATE CALLBACK, auto generate a callback function.
#define X_EES_LINE//EXPORT[for lua,etc.]: EES: ENGINE - ELIMINATE SINGLE LINE,eliminate a single line in the head file.
#define X_EEB_BEGIN//EXPORT[for lua,etc.]: EEB: ENGINE - ELIMINATE BLOCK, eliminate block begin(WARNING! should be formed a pair with X_EEB_END)
#define X_EEB_END//EXPORT[for lua,etc.]: EEB: ENGINE - ELIMINATE BLOCK, eliminate block end

X_EES_LINE typedef void(*DestructXClassCallback)(class XClass *pClass);

class XClass
{
public:
	virtual ~XClass(){ if (const DestructXClassCallback& _lpFunc = __getXClassCallback()) _lpFunc(this); }
	virtual const xchar* GetClassName()const = 0;
	X_EES_LINE X_FORCEINLINE static void SetXClassCallback(DestructXClassCallback lpFunc){ __getXClassCallback() = lpFunc; }
private:
	X_FORCEINLINE static DestructXClassCallback& __getXClassCallback()
	{
		static DestructXClassCallback __lpFunc = nullptr;
		return __lpFunc;
	}
};


#endif // _XE_CLASS_H_
