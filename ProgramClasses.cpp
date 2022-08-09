#include "ProgramClasses.h"


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
