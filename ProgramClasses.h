#pragma once

#include <vector>
#include <string>

// Base classes
class Subprogram
{
public:
	Subprogram(Buffer<std::string>* _buffer) { buffer = _buffer; };

	virtual void TaskExecution() = 0;

protected:
	Buffer<std::string>* buffer;
};

template <typename ContainerType>
class Buffer
{
public:
	Buffer() {};

	void SetData(ContainerType _data) { dataContainer = _data; };

	ContainerType GetData() { return dataContainer; };

	void ClearData() { dataContainer = ContainerType(); };

protected:
	ContainerType dataContainer;
};

class Delegate
{

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

	void AddData(int _data) { dataContainer.push_back(_data); }
};

class Subprogram_1 : public Subprogram
{
public:
	Subprogram_1(Buffer<std::string>* _buffer) : Subprogram(_buffer) {}

	void TaskExecution() override;
};

class Subprogram_2 : public Subprogram
{
public:
	Subprogram_2(Buffer<std::string>* _buffer, OfflineBuffer* _offlineBuffer) : Subprogram(_buffer) 
	{ offlineBuffer = _offlineBuffer; }

	void TaskExecution() override;

private:
	OfflineBuffer* offlineBuffer;
};