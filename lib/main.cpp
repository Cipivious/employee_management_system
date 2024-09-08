#include "manager.h"

int main() {
    std::vector<AbstractModule*> modules = {
        new AddPersonModule,
        new DeletePersonModule,
        new DisplayPersonModule,
        new EditPersonModule,
        new SearchPersonModule,
        new CopyPersonModule,
        new ExitPersonModule
    };
    Manager manager(modules);
    manager.start();
    return 0;
}