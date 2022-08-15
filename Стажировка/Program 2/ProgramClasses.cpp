#include "ProgramClasses.h"
#include "Network.h"


void Delegate::Call()
{
	if(subscriberData)
		subscriberData->Call();
}

void Delegate::Subscribe(Subprogram* Object, void(Subprogram::* Function)())
{
	if (subscriberData)
		delete subscriberData;

	subscriberData = new DelegateContainer<Subprogram, void(Subprogram::*)()>(Object, Function);
}

Subprogram::Subprogram(Buffer<std::string>* __buffer, NetworkMember* __networkMemberObject) 
{
	 buffer = __buffer; 
	 networkMemberObject = __networkMemberObject; 
}

Subprogram::~Subprogram()
{
	delete buffer;
	delete networkMemberObject;
}