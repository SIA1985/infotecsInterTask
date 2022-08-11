#include "Program2Classes.h"
#include "Network.h"

int main()
{
    NetworkServer Server;

    MainSubprogram* PtrMainSubprogram = new MainSubprogram(nullptr, &Server);

    PtrMainSubprogram->TaskExecution();
}
