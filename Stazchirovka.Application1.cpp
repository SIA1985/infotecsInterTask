#include "ProgramClasses.h"

int main()
{
	Buffer<std::string>* PtrCommonBuffer = new Buffer<std::string>();
	OfflineBuffer* PtrOfflineBuffer = new OfflineBuffer(); //Buffer<vector<int>>

	Subprogram_1* PtrSubprogram_1 = new Subprogram_1(PtrCommonBuffer);
	Subprogram_2* PtrSubprogram_2 = new Subprogram_2(PtrCommonBuffer, PtrOfflineBuffer);

	PtrSubprogram_2->GetBuffer()->StateDelegate.Subscribe(PtrSubprogram_2, &Subprogram::DelegateFunction);
	//add thread

	while (1)
	{
		PtrSubprogram_1->TaskExecution();
	}
}