#include "Elyra.hpp"

int main() {

    Elyra::Log::Init();
    Elyra::Application app;
    EL_INFO("Sandbox launching...");
    app.Run();
    EL_INFO("Sandbox exiting.");
    return 0;
}
