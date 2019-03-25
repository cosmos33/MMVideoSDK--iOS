/******************************************************************************

@File         XESingleton.h

@Version       1.0

@Created      2017, 6, 12

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/


#ifndef _XE_SINGLETON_H_
#define _XE_SINGLETON_H_

template<typename T>
class XESingleton {
public:
	static T *GetInstance() {
// 		if (nullptr == s_pInst) {
// 			s_pInst = new T();
// 		}
// 		return s_pInst;

		static  T _instance;
		return &_instance;
	}
// private:
// 	static T *s_pInst;

protected:

	XESingleton(void){};
	XESingleton(const XESingleton<T> &);
	XESingleton& operator=(const XESingleton<T> &);
};

// template<typename T>
// T *XESingleton<T>::s_pInst = nullptr;
#endif