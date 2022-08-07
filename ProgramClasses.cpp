#include "ProgramClasses.h"
#include "Utils.h"


void Delegate::Call()
{
	subscriberData->Call();
}

void Delegate::Subscribe(Subprogram* Object, void(Subprogram::* Function)())
{
	if (subscriberData)
		delete subscriberData;

	subscriberData = new DelegateContainer<Subprogram, void(Subprogram::*)()>(Object, Function);
}


Errors Subprogram_1::TaskExecution()
{
	std::string InputString;
	Errors OperationResult;

	std::cin >> InputString;

	OperationResult = CheckStringLengthAndContetnt(InputString);
	if (OperationResult == Errors::InvalidInput)
		return Errors::InvalidInput;

	StringProcessing(InputString);

	if (buffer->GetData() != "")
	{
		LOG("Buffer contains unused data")
		return Errors::BufferContainsData;
	}
	
	buffer->SetData(InputString);

	return Errors::NoErrors;
}

Errors Subprogram_2::TaskExecution()
{
	std::string StringFromBuffer = buffer->GetData();
	
	buffer->ClearData();

	CONSOLE(StringFromBuffer)

	int EvenNumbersSum = GetSumOfEvenNumbersInString(StringFromBuffer);

	//Send sum to the second program

	return Errors::NoErrors;
}

void Subprogram_2::DelegateFunction()
{
	TaskExecution();
}
