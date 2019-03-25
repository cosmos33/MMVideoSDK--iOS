/******************************************************************************

@File         XEBroadcast.h

@Version       1.0

@Created      2017, 8, 28

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XE_BROADCAST_H_
#define _XE_BROADCAST_H_
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <stdarg.h> 
#include "IXEInterface.h"
class XEListener;
typedef std::vector<XEListener*> BroadcasterGuestList;


class XEBroadcaster:public IXEInterface
{
public:
	XEBroadcaster(void){}
	virtual void Accept(XEListener* guest)
	{
		BroadcasterGuestList::iterator it = m_lsGeusts.begin();
		for (; it != m_lsGeusts.end(); ++it)
		{
			if (*it == guest)
				return;
		}
		m_lsGeusts.push_back(guest);
	}
	template<typename t_first, typename ... t_rest>
	void Broadcast(const char* fmt, const unsigned short channel, const t_first& f, const t_rest& ... r)
	{
		//to tell all the guest listeners.
		for (BroadcasterGuestList::iterator it = m_lsGeusts.begin(); it != m_lsGeusts.end(); ++it)
		{
			(*it)->Recieve(fmt, channel, f, r ...);
		}
	}
private:
	BroadcasterGuestList m_lsGeusts;//a list of guests. note: this pointer will not be safe.
private:
	//no copy or copy assign
	XEBroadcaster& operator=(const XEBroadcaster&) { return *this; }
	XEBroadcaster(const XEBroadcaster&) {}
};

#define EXPANDPARAMS_LISTENER_START()\
va_list ap;\
va_start(ap, fmt);\
va_arg(ap, unsigned short)

#define EXPANDPARAMS_LISTENER_BODY(val)\
if (*fmt){\
	switch (*fmt)\
	{\
	case 'u':\
		val = (void*)&va_arg(ap, unsigned short);\
		break;\
	case 'd':\
		val = (void*)&va_arg(ap, int);\
		break;\
	case 'c':\
		val = (void*)&va_arg(ap, char);\
		break;\
	case 's':\
		val = (void*)&va_arg(ap, char *);\
		break;\
	case 'f':\
		val = (void*)&va_arg(ap, float);\
		break;\
	case 'r':\
		val = va_arg(ap,void *);\
		break;\
	default:\
		va_arg(ap,void *);\
		break;\
	}\
	fmt++;\
}

#define EXPANDPARAMS_LISTENER_END()\
va_end(ap)

class XEListener :public IXEInterface
{
public:
	enum { CHANNEL0, CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4, CHANNEL5, CHANNEL6, CHANNEL7, CHANNEL8, CHANNEL9 };//mostly used channels;
	XEListener(void){}
	virtual void Attach(XEBroadcaster* holder)
	{
		m_pHolder = holder;
		holder->Accept(this);
	}
	virtual void SetupChannelMeaning(const unsigned short channel, const char* meaning)
	{
		m_channelMean[channel] = std::string(meaning);
	}
	virtual const char* GetChannelMean(const unsigned short channel)
	{
		if (m_channelMean.find(channel) == m_channelMean.end())
			return NULL;
		return m_channelMean[channel].c_str();
	}
	virtual bool GetChannel(unsigned short& channel, const char* mean)
	{
		for (auto it = m_channelMean.begin(); it != m_channelMean.end(); ++it)
		{
			if (0 == it->second.compare(mean))
			{
				channel = it->first;
				return true;
			}
		}
		return false;
	}
	virtual void Recieve(const char* fmt, const unsigned short channel, ...){};
private:
	//no copy or copy assign
	XEListener& operator=(const XEListener&) { return *this; }
	XEListener(const XEListener&) {}
private:
	std::map<unsigned short, std::string> m_channelMean;
protected:
	XEBroadcaster* m_pHolder;
};
#endif