//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2024-04-03 17:59
// 从事件类中独立出观察者模式类
// 观察事件类增加观察者个数的获取接口

#pragma once

#ifndef _TANXL_OBSERVERBASE_
#define _TANXL_OBSERVERBASE_

#include<vector>
#include<string>

template<typename Tanxl_TypeName>
class Event_Observer
{
public:
	virtual void EventCheck(Tanxl_TypeName& Tanxl_Type) = 0;
	virtual ~Event_Observer();
};

template<typename Tanxl_TypeName>
class EventSubject
{
public:
	void Add_Observer(Event_Observer<Tanxl_TypeName>* Observer);

	void Remove_Observer(Event_Observer<Tanxl_TypeName>* Observer);

	void Remove_Observer();

	void Notify(Tanxl_TypeName Tanxl_Type);

	int Size();

private:
	std::vector<Event_Observer<Tanxl_TypeName>*> _ObserverS;
};

template<typename Tanxl_TypeName>
inline Event_Observer<Tanxl_TypeName>::~Event_Observer() {}

template<typename Tanxl_TypeName>
inline void EventSubject<Tanxl_TypeName>::Add_Observer(Event_Observer<Tanxl_TypeName>* Observer)
{
	if (Observer)
		this->_ObserverS.push_back(Observer);
}

template<typename Tanxl_TypeName>
inline void EventSubject<Tanxl_TypeName>::Remove_Observer(Event_Observer<Tanxl_TypeName>* Observer)
{
	auto Location{ std::find(this->_ObserverS.begin(), this->_ObserverS.end(), Observer) };
	if (Location != this->_ObserverS.end())
		this->_ObserverS.erase(Location);
}

template<typename Tanxl_TypeName>
inline void EventSubject<Tanxl_TypeName>::Remove_Observer()
{
	this->_ObserverS.erase(this->_ObserverS.begin(), this->_ObserverS.end());
}

template<typename Tanxl_TypeName>
inline void EventSubject<Tanxl_TypeName>::Notify(Tanxl_TypeName Tanxl_Type)
{
	for (const auto& Observer : this->_ObserverS)
		Observer->EventCheck(Tanxl_Type);
}

template<typename Tanxl_TypeName>
inline int EventSubject<Tanxl_TypeName>::Size()
{
	return static_cast<int>(this->_ObserverS.size());
}

#endif