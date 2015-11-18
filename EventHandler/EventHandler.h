#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include <map>
#include <typeindex>
#include <memory>

#include "EventBase.h"


class IMFuncHandler
{
public:
	virtual ~IMFuncHandler(){}
	virtual void call(const EventBase*) = 0;
};

template<typename T, typename EventT>
class MFuncHandler : public IMFuncHandler
{
public:
	typedef void (T::*mFunc)(const EventT*);
	MFuncHandler(T* instance, mFunc func) : m_instanceRef{ instance }, m_memberFunc{ func } {}
	void call(const EventBase* evnt) override
	{
		(m_instanceRef->*m_memberFunc)(static_cast<const EventT*>(evnt));
	}
private:
	T* m_instanceRef;
	mFunc m_memberFunc;
};

class EventHandler
{
public:
	template<typename T, typename EventT>
	void registerMember(T*, void (T::*mFunc)(const EventT*));
	void handleEvent(const EventBase*);
private:
	typedef std::map<std::type_index, std::unique_ptr<IMFuncHandler>> HandlerMap;
	HandlerMap m_handler;
};

template<typename T, typename EventT>
void EventHandler::registerMember(T* obj, void (T::*mFunc)(const EventT*))
{
	m_handler[typeid(EventT)] = std::make_unique<MFuncHandler<T, EventT>>(obj, mFunc);
}

#endif