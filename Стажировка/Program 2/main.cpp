#include "Program2Classes.h"
#include "Network.h"
#include <signal.h>

int main()
{
    sigaction(SIGPIPE, &(struct sigaction){SIG_IGN}, NULL);

    NetworkServer Server;

    MainSubprogram* PtrMainSubprogram = new MainSubprogram(nullptr, &Server);

    PtrMainSubprogram->TaskExecution();

    delete PtrMainSubprogram;
}
