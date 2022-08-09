#include "Appliation1Classes.h"
//Add delegate OnBreakConnection
int main()
{
	Buffer<std::string>* PtrCommonBuffer = new Buffer<std::string>();
	OfflineBuffer* PtrOfflineBuffer = new OfflineBuffer(); //Buffer<vector<int>>

	Subprogram_1* PtrSubprogram_1 = new Subprogram_1(PtrCommonBuffer);
	Subprogram_2* PtrSubprogram_2 = new Subprogram_2(PtrCommonBuffer, PtrOfflineBuffer);

	PtrSubprogram_2->GetBuffer()->OnBufferSetSignature.Subscribe(PtrSubprogram_2, &Subprogram::OnBufferSet);
	//add thread


	std::thread Thread2(&Subprogram_2::TaskExecution, PtrSubprogram_2);
	Thread2.detach();

	PtrSubprogram_1->TaskExecution();
}