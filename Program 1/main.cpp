#include <memory>

#include "Program1Classes.h"
#include "Network.h"
#include "Output.h"
#include <signal.h>

//Make thread for 1 program, cause of connection? (against rhe task)
int main()
{
	sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL); //Add delegate OnBreakConnection

	NetworkClient Client;

	Buffer<std::string>* PtrCommonBuffer = new Buffer<std::string>();
	OfflineBuffer* PtrOfflineBuffer = new OfflineBuffer(); //Buffer<vector<int>>
//  Delete offline buffer!
	Subprogram_1* PtrSubprogram_1 = new Subprogram_1(PtrCommonBuffer, &Client);
	Subprogram_2* PtrSubprogram_2 = new Subprogram_2(PtrCommonBuffer, PtrOfflineBuffer, &Client);

	PtrSubprogram_2->GetBuffer()->OnBufferSetSignature.Subscribe(PtrSubprogram_2, &Subprogram::OnBufferSet);
	//Need delegate?

	Client.Connect();

	std::thread Thread2(&Subprogram_2::TaskExecution, PtrSubprogram_2);
	Thread2.detach();

	PtrSubprogram_1->TaskExecution();

	// delete PtrCommonBuffer;
	// delete PtrOfflineBuffer;
	// delete PtrSubprogram_1;
	// delete PtrSubprogram_2;
}
