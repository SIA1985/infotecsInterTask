#include "Program2Classes.h"
#include "Network.h"
#include "Output.h"

void MainSubprogram::TaskExecution() 
{
	while(1)
	{
		if(networkMemberObject->IsConnected())
		{
			networkMemberObject->RecievMessage();

			if(networkMemberObject->GetBuffer().size() > 0)
			{
				int RecievedSum = std::stoi(networkMemberObject->GetBuffer());

				if(RecievedSum > 99 && RecievedSum % 32 == 0)
					CONSOLE("Data is recieved!")
				else	
					LOG("Wrong data")	

				networkMemberObject->ClearBuffer();
			}

			ConnectionCheck();
		}
		else
		{
			networkMemberObject->TryToConnect();
		}
	}
}

void MainSubprogram::ConnectionCheck()
{
	networkMemberObject->GetBuffer().push_back(1);

	networkMemberObject->SendMessage();

	networkMemberObject->ClearBuffer();
}
