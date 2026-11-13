#include "application.h"
#include "version.h"
#include <iostream>

int main() {
    Application app(800, 500, FLOWER3D_PROJECT_NAME " v" FLOWER3D_PROJECT_VERSION);

    std::cout << FLOWER3D_PROJECT_NAME << " v" << FLOWER3D_PROJECT_VERSION << '\n';

    if (!app.initialize()) {
        std::cerr << "Failed to initialize application\n";
        return -1;
    }

    app.run();
    app.shutdown();

    return 0;
}