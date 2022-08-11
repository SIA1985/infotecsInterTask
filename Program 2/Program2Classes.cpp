#include "Program2Classes.h"
#include "Network.h"
#include "Output.h"

void MainSubprogram::TaskExecution() 
{
	while(1)
	{
		if(NetworkMemberObject->IsConnected())
		{
			NetworkMemberObject->RecievMessage();

			for(auto it = NetworkMemberObject->GetBuffer().begin(); it < NetworkMemberObject->GetBuffer().end(); it++)
			{
				if(*it > 99 && *it % 32 == 0)
				CONSOLE("Data is recieved!")
			else	
				LOG("Wrong data")
			}

			NetworkMemberObject->ClearBuffer();
		}
		else
		{
			NetworkMemberObject->TryToConnect();
		}
	}
}
