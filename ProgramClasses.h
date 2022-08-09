#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

// Delegate
class Subprogram; //Forward declaration

template <class CallableObject, class FunctionToCall>
class DelegateContainer 
{
public:
	DelegateContainer(CallableObject* __object, FunctionToCall __function) { object = __object; function = __function; }

	void Call() { (object->*function)(); }

	CallableObject* object = nullptr;
	FunctionToCall function;
};

class Delegate
{
public:
	void Call();

	void Subscribe(Subprogram* Object, void(Subprogram::*Function)());// call wake up thread

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
	Subprogram(Buffer<std::string>* __buffer) { buffer = __buffer; };

	virtual void TaskExecution() {};

	virtual void OnBufferSet() {};

	Buffer<std::string>* GetBuffer() { return buffer; }

protected:
	Buffer<std::string>* buffer = nullptr;
};