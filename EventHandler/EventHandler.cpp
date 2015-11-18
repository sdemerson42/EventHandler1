#include "EventHandler.h"


void EventHandler::handleEvent(const EventBase* evnt)
{
	HandlerMap::iterator i = m_handler.find(std::type_index(typeid(*evnt)));
	if (i != m_handler.end())
		i->second->call(evnt);
}