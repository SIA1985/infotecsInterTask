#pragma once

#include "ProgramClasses.h"

class OfflineBuffer : public Buffer<std::string>
{
public:
	OfflineBuffer() {};

	void AddData(std::string __data) { dataContainer += __data; }

	bool HasAnyData() { return dataContainer.size() > 0; }
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

	virtual ~Subprogram_2() { delete offlineBuffer; }

	void TaskExecution() override;

	void OnBufferSet() override;

	void OnReconnect() override;

	void ConnectionCheck() override;

private:
	OfflineBuffer* offlineBuffer = nullptr;
};