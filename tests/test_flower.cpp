#include "flower.h"

#include <iostream>

int main() {
    Flower flower(8, 16, 1.0f, 0.5f);

    const int vertexCount = flower.getVertexCount();
    const int indexCount = flower.getIndexCount();

    if (vertexCount <= 0) {
        std::cerr << "Expected positive vertex count, got " << vertexCount << '\n';
        return 1;
    }
    if (indexCount <= 0) {
        std::cerr << "Expected positive index count, got " << indexCount << '\n';
        return 1;
    }
    if (static_cast<int>(flower.getVertices().size()) != vertexCount) {
        std::cerr << "Vertex buffer size does not match vertex count\n";
        return 1;
    }
    if (static_cast<int>(flower.getIndices().size()) != indexCount) {
        std::cerr << "Index buffer size does not match index count\n";
        return 1;
    }

    // Basic sanity: indices must reference existing vertices
    for (unsigned int idx : flower.getIndices()) {
        if (idx >= static_cast<unsigned int>(vertexCount)) {
            std::cerr << "Index out of range: " << idx << " >= " << vertexCount << '\n';
            return 1;
        }
    }

    std::cout << "test_flower passed (" << vertexCount << " vertices, " << indexCount << " indices)\n";
    return 0;
}
