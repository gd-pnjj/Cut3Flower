#include "application.h"
#include <iostream>

int main() {
    Application app(800, 500, "3D Flower");
    
    if (!app.initialize()) {
        std::cerr << "Failed to initialize application\n";
        return -1;
    }
    
    app.run();
    app.shutdown();
    
    return 0;
}