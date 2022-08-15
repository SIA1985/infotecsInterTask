#include <memory>

#include "Program1Classes.h"
#include "Network.h"
#include "Output.h"
#include <signal.h>

#define XOPEN_SOURCE_EXTENDED 1

int main()
{
	sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL); 

	NetworkClient Client;

	Buffer<std::string>* PtrCommonBuffer = new Buffer<std::string>();
	OfflineBuffer* PtrOfflineBuffer = new OfflineBuffer(); 

	Subprogram_1* PtrSubprogram_1 = new Subprogram_1(PtrCommonBuffer, &Client);
	Subprogram_2* PtrSubprogram_2 = new Subprogram_2(PtrCommonBuffer, PtrOfflineBuffer, &Client);

	PtrSubprogram_2->GetNetworkMemberObject()->OnReconnect.Subscribe(PtrSubprogram_2, &Subprogram::OnReconnect);
	PtrSubprogram_2->GetBuffer()->OnBufferSetSignature.Subscribe(PtrSubprogram_2, &Subprogram::OnBufferSet);

	Client.Connect();

	std::thread Thread2(&Subprogram_2::TaskExecution, PtrSubprogram_2);
	Thread2.detach();

	PtrSubprogram_1->TaskExecution();

	delete PtrCommonBuffer;
	delete PtrOfflineBuffer;
	delete PtrSubprogram_1;
	delete PtrSubprogram_2;
}
