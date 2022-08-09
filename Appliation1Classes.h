#pragma once

#include "ProgramClasses.h"

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

	void TaskExecution() override;
};

class Subprogram_2 : public Subprogram
{
public:
	Subprogram_2(Buffer<std::string>* __buffer, OfflineBuffer* __offlineBuffer) : Subprogram(__buffer)
	{
		offlineBuffer = __offlineBuffer;
	}

	void TaskExecution() override;

	void OnBufferSet() override;

private:
	OfflineBuffer* offlineBuffer = nullptr;
};