#pragma once

#include "ProgramClasses.h"


class MainSubprogram : public Subprogram
{
public:
	MainSubprogram(Buffer<std::string>* __buffer, NetworkMember* __networkMemberObject) : Subprogram(__buffer, __networkMemberObject){}

	void TaskExecution() override;
};