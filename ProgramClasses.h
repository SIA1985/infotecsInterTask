#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

// Enums
enum class Errors
{
	InvalidInput,
	BufferContainsData,
	InvalidDelegate, //?
	NoErrors
};

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

// Base classes
template <typename ContainerType>
class Buffer
{
public:
	Buffer() {};

	void SetData(ContainerType __data) { dataContainer = __data; StateDelegate.Call(); }

	ContainerType GetData() { return dataContainer; }

	void ClearData() { dataContainer = ContainerType(); }

	Delegate StateDelegate;

protected:
	ContainerType dataContainer;
	
};

class Subprogram
{
public:
	Subprogram(Buffer<std::string>* __buffer) { buffer = __buffer; };

	virtual Errors TaskExecution() = 0;

	virtual void DelegateFunction() = 0;

	Buffer<std::string>* GetBuffer() { return buffer; }

protected:
	Buffer<std::string>* buffer = nullptr;
};

//Main classes
//class CommonBuffer : public Buffer<std::string>
//{
//public:
//	CommonBuffer() {};
//};

class OfflineBuffer : public Buffer<std::vector<int>>
{
public:
	OfflineBuffer() {};

	void AddData(int __data) { dataContainer.push_back(__data); }
};

class Subprogram_1 : public Subprogram
{
public:
	Subprogram_1(Buffer<std::string>* __buffer) : Subprogram(__buffer) {}

	Errors TaskExecution() override;

	void DelegateFunction() override {};
};

class Subprogram_2 : public Subprogram
{
public:
	Subprogram_2(Buffer<std::string>* __buffer, OfflineBuffer* __offlineBuffer) : Subprogram(__buffer)
	{ offlineBuffer = __offlineBuffer; }

	Errors TaskExecution() override;

	void DelegateFunction() override;

private:
	OfflineBuffer* offlineBuffer = nullptr;
};