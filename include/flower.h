#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class Flower {
public:
    Flower(int petalCount = 8, int petalSegments = 16, float petalLength = 1.0f, float petalWidth = 0.5f);
    
    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;
    int getVertexCount() const;
    int getIndexCount() const;

private:
    void generateGeometry();
    void generatePetal(float angleOffset, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int& indexOffset);
    void generateCenter(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int& indexOffset);
    void generateStem(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int& indexOffset);

    std::vector<Vertex> vertices_;
    std::vector<unsigned int> indices_;
    
    int petalCount_;
    int petalSegments_;
    float petalLength_;
    float petalWidth_;
};