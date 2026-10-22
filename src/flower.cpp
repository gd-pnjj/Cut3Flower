#include "flower.h"
#include <glm/gtc/constants.hpp>
#include <cmath>

Flower::Flower(int petalCount, int petalSegments, float petalLength, float petalWidth)
    : petalCount_(petalCount), petalSegments_(petalSegments), petalLength_(petalLength), petalWidth_(petalWidth) {
    generateGeometry();
}

const std::vector<Vertex>& Flower::getVertices() const {
    return vertices_;
}

const std::vector<unsigned int>& Flower::getIndices() const {
    return indices_;
}

int Flower::getVertexCount() const {
    return static_cast<int>(vertices_.size());
}

int Flower::getIndexCount() const {
    return static_cast<int>(indices_.size());
}

void Flower::generateGeometry() {
    vertices_.clear();
    indices_.clear();
    unsigned int indexOffset = 0;

    generateCenter(vertices_, indices_, indexOffset);
    generateStem(vertices_, indices_, indexOffset);

    for (int i = 0; i < petalCount_; ++i) {
        float angleOffset = (2.0f * glm::pi<float>() * i) / petalCount_;
        generatePetal(angleOffset, vertices_, indices_, indexOffset);
    }
}

void Flower::generatePetal(float angleOffset, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int& indexOffset) {
    const float baseRadius = 0.15f;
    const float centerY = 0.0f;

    for (int seg = 0; seg <= petalSegments_; ++seg) {
        float t = static_cast<float>(seg) / petalSegments_;
        float angle = angleOffset;
        
        float width = petalWidth_ * sin(t * glm::pi<float>());
        float height = 0.3f * sin(t * glm::pi<float>());

        float x1 = (baseRadius + width) * cos(angle);
        float z1 = (baseRadius + width) * sin(angle);
        float x2 = (baseRadius - width) * cos(angle);
        float z2 = (baseRadius - width) * sin(angle);

        Vertex v1;
        v1.position = glm::vec3(x1, centerY + height, z1);
        v1.normal = glm::vec3(0.0f, 1.0f, 0.0f);
        v1.texCoord = glm::vec2(t, 0.0f);
        vertices.push_back(v1);

        Vertex v2;
        v2.position = glm::vec3(x2, centerY + height, z2);
        v2.normal = glm::vec3(0.0f, 1.0f, 0.0f);
        v2.texCoord = glm::vec2(t, 1.0f);
        vertices.push_back(v2);
    }

    for (int seg = 0; seg < petalSegments_; ++seg) {
        unsigned int base = indexOffset + seg * 2;
        indices.push_back(base);
        indices.push_back(base + 1);
        indices.push_back(base + 2);
        indices.push_back(base + 1);
        indices.push_back(base + 3);
        indices.push_back(base + 2);
    }
    indexOffset += (petalSegments_ + 1) * 2;
}

void Flower::generateCenter(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int& indexOffset) {
    const int segments = 16;
    const float radius = 0.15f;
    const float height = 0.05f;

    Vertex center;
    center.position = glm::vec3(0.0f, height, 0.0f);
    center.normal = glm::vec3(0.0f, 1.0f, 0.0f);
    center.texCoord = glm::vec2(0.5f, 0.5f);
    vertices.push_back(center);

    for (int i = 0; i <= segments; ++i) {
        float angle = (2.0f * glm::pi<float>() * i) / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        Vertex v;
        v.position = glm::vec3(x, 0.0f, z);
        v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
        v.texCoord = glm::vec2(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
        vertices.push_back(v);
    }

    for (int i = 0; i < segments; ++i) {
        indices.push_back(indexOffset);
        indices.push_back(indexOffset + i + 1);
        indices.push_back(indexOffset + ((i + 1) % segments) + 1);
    }
    indexOffset += segments + 1;
}

void Flower::generateStem(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, unsigned int& indexOffset) {
    const int segments = 8;
    const float radius = 0.03f;
    const float length = 1.5f;

    for (int ring = 0; ring <= 2; ++ring) {
        float y = -length * ring / 2.0f;
        for (int i = 0; i <= segments; ++i) {
            float angle = (2.0f * glm::pi<float>() * i) / segments;
            float x = radius * cos(angle);
            float z = radius * sin(angle);

            Vertex v;
            v.position = glm::vec3(x, y, z);
            v.normal = glm::normalize(glm::vec3(x, 0.0f, z));
            v.texCoord = glm::vec2(static_cast<float>(i) / segments, static_cast<float>(ring) / 2.0f);
            vertices.push_back(v);
        }
    }

    for (int ring = 0; ring < 2; ++ring) {
        for (int i = 0; i < segments; ++i) {
            unsigned int current = indexOffset + ring * (segments + 1) + i;
            unsigned int next = indexOffset + ring * (segments + 1) + i + 1;
            unsigned int currentNext = indexOffset + (ring + 1) * (segments + 1) + i;
            unsigned int nextNext = indexOffset + (ring + 1) * (segments + 1) + i + 1;

            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(currentNext);
            indices.push_back(next);
            indices.push_back(nextNext);
            indices.push_back(currentNext);
        }
    }
    indexOffset += 3 * (segments + 1);
}