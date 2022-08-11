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
	Subprogram_1(Buffer<std::string>* __buffer, NetworkMember* __networkMemberObject) : Subprogram(__buffer, __networkMemberObject) {}

	void TaskExecution() override;
};

class Subprogram_2 : public Subprogram
{
public:
	Subprogram_2(Buffer<std::string>* __buffer, OfflineBuffer* __offlineBuffer, NetworkMember* __networkMemberObject) 
	: Subprogram(__buffer, __networkMemberObject)
	{
		offlineBuffer = __offlineBuffer;
	}

	void TaskExecution() override;

	void OnBufferSet() override;

private:
	OfflineBuffer* offlineBuffer = nullptr;
};