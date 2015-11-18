#include "EventHandler.h"
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

// Small test of the EventHandler class...

class MsgEvent : public EventBase
{
public:
	MsgEvent(const string& s) : m_msg(s){}
	const string& getMsg() const { return m_msg; }
private:
	string m_msg;
};

class ThingBase: public EventHandler {};

class Alice : public ThingBase
{
public:
	Alice()
	{
		registerMember(this, &Alice::onMsg);
	}
protected:
	void onMsg(const MsgEvent* msg)
	{
		cout << "Alice received a message: " << msg->getMsg() << "\n";
	}
};

class Bob : public ThingBase
{
public:
	Bob()
	{
		registerMember(this, &Bob::onMsg);
	}
protected:
	void onMsg(const MsgEvent* msg)
	{
		cout << "Bob received a message and ignored its contents.";
	}
};

class Carol : public ThingBase
{
public:
	Carol(){}	// Carol does not receive MsgEvents
};

int main()
{

	vector <unique_ptr<ThingBase>> thing;
	thing.push_back(make_unique<Alice>());
	thing.push_back(make_unique<Bob>());
	thing.push_back(make_unique<Carol>());

	// Alice will display the event's string. Bob will acknowledge receipt but not display the string.
	// Carol will not handle the event.

	for (auto& p : thing)
		p->handleEvent(&MsgEvent("This is the message."));
		

	_getch();
	return 0;
}