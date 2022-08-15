#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

class NetworkMember;

// Delegate
class Subprogram; //Forward declaration

template <class CallableObject, class FunctionToCall>
class DelegateContainer 
{
public:
	DelegateContainer(CallableObject* __object, FunctionToCall __function) { object = __object; function = __function; }

	void Call() { if(object) (object->*function)(); }

	CallableObject* object = nullptr;
	FunctionToCall function;
};

class Delegate
{
public:
	~Delegate() { delete subscriberData; }

	void Call();

	void Subscribe(Subprogram* Object, void(Subprogram::*Function)());

private:
	DelegateContainer<Subprogram, void(Subprogram::*)()>* subscriberData = nullptr;
};


// SynchroObject
class SynchroObject
{
public:
	std::mutex mutex;
	std::condition_variable conditionalVariable;

	void InverseSynchroFlag() { SynchroFlag = !SynchroFlag; }
	bool& GetSynchroFlag() { return SynchroFlag; }

private:
	bool SynchroFlag = false;
};


// Base classes
template <typename ContainerType>
class Buffer
{
public:
	Buffer() {};

	virtual ~Buffer() {}

	void SetData(ContainerType __data) { dataContainer = __data; OnBufferSetSignature.Call(); }

	ContainerType GetData() { return dataContainer; }

	void ClearData() { dataContainer = ContainerType(); }

	Delegate OnBufferSetSignature;

	SynchroObject synchroObject;

protected:
	ContainerType dataContainer;
	
};

class Subprogram
{
public:
	Subprogram(Buffer<std::string>* __buffer, NetworkMember* __networkMemberObject);

	virtual ~Subprogram();

	virtual void TaskExecution() {}

	virtual void OnBufferSet() {}

	virtual void OnReconnect() {}

	virtual void ConnectionCheck() {}

	Buffer<std::string>* GetBuffer() { return buffer; }

	NetworkMember* GetNetworkMemberObject() { return networkMemberObject; }

protected:
	Buffer<std::string>* buffer = nullptr;
	NetworkMember* networkMemberObject = nullptr;
};