#include "Appliation1Classes.h"
#include "Utils.h"

void Subprogram_1::TaskExecution()
{
	while (1)
	{
		std::string InputString;
		bool OperationResult;

		std::cin >> InputString;

		OperationResult = CheckStringLengthAndContetnt(InputString);
		if (OperationResult == false)
			continue;

		StringProcessing(InputString);

		buffer->SetData(InputString);
	}
}

void Subprogram_2::TaskExecution()
{
	while (1)
	{
		std::unique_lock<std::mutex> uniqueLock(buffer->synchroObject.mutex);
		bool& SynchroFlag = buffer->synchroObject.GetSynchroFlag();
		buffer->synchroObject.conditionalVariable.wait(uniqueLock, [&SynchroFlag] {return SynchroFlag; });

		if (SynchroFlag)
		{
			std::string StringFromBuffer = buffer->GetData();

			buffer->ClearData();

			CONSOLE(StringFromBuffer)

				int EvenNumbersSum = GetSumOfEvenNumbersInString(StringFromBuffer);

			//Send sum to the second program;

			buffer->synchroObject.InverseSynchroFlag();

			uniqueLock.unlock();
		}
	}
}

void Subprogram_2::OnBufferSet()
{
	// Wake up 2nd thread
	buffer->synchroObject.InverseSynchroFlag();
	buffer->synchroObject.conditionalVariable.notify_one();
}
