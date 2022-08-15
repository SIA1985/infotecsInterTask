#include "Program1Classes.h"
#include "Utils.h"
#include "Network.h"

void Subprogram_1::TaskExecution()
{
	while (1)
	{
		if(networkMemberObject->IsConnected())
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
		else
		{
			networkMemberObject->Connect();
		}
	}
}


void Subprogram_2::TaskExecution()
{
	while (1)
	{
		if(networkMemberObject->IsConnected())
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

				networkMemberObject->GetBuffer().append(std::to_string(EvenNumbersSum));

				networkMemberObject->SendMessage();


				ConnectionCheck();

				if(offlineBuffer->HasAnyData())
				{
					CONSOLE("\nSending saved data...")

					networkMemberObject->ClearBuffer();

					networkMemberObject->GetBuffer().append(offlineBuffer->GetData());

					networkMemberObject->SendMessage();
					
					CONSOLE("Done!\n")

					offlineBuffer->ClearData();
				}

				networkMemberObject->ClearBuffer();

				buffer->synchroObject.InverseSynchroFlag();

				uniqueLock.unlock();
			}
		}
		else
		{
			networkMemberObject->Connect();
		}
	}
}

void Subprogram_2::OnBufferSet()
{
	// Wake up 2nd thread
	buffer->synchroObject.InverseSynchroFlag();
	buffer->synchroObject.conditionalVariable.notify_one();
}

void Subprogram_2::ConnectionCheck()
{
	networkMemberObject->RecievMessage();

	networkMemberObject->ClearBuffer();
}

void Subprogram_2::OnReconnect() 
{
	CONSOLE("\nSaving data...")
	
	offlineBuffer->AddData(networkMemberObject->GetBuffer());

	CONSOLE("Saved data will be resend after connection!\n")
}
