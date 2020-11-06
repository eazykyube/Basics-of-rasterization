#include "depth_buffer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


cg::ZCulling::ZCulling(unsigned short width, unsigned short height, std::string objFile) : TriangleRasterization(width, height, objFile) {
	depthBuffer.reserve(static_cast<size_t>(width * height));
}

cg::ZCulling::~ZCulling() { }

void cg::ZCulling::Clear() {

    depthBuffer.clear();
    depthBuffer.resize(static_cast<size_t>(width * height));
    depthBuffer.resize(static_cast<size_t>(width * height), 1.f);
}

void cg::ZCulling::DrawTriangle(cg::face face) {

    float xMin = std::min(std::min(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
    float xMax = std::max(std::max(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
    float yMin = std::min(std::min(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);
    float yMax = std::max(std::max(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);

    bool ccw = false;
    float direction = ccw ? -1.f : 1.f;
    float area = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), face.vertexes[2].xy());

    for (float x = xMin; x <= xMax; x += 1.f) {
        for (float y = yMin; y <= yMax; y += 1.f) {
            float2 point{ x, y };

            float e0 = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), point);
            float e1 = direction * EdgeFunction(face.vertexes[1].xy(), face.vertexes[2].xy(), point);
            float e2 = direction * EdgeFunction(face.vertexes[2].xy(), face.vertexes[0].xy(), point);

            if (e0 >= 0.f && e1 >= 0.f && e2 >= 0.f) {
                float3 bary{ e1 / area, e2 / area, e0 / area };
                float z = 1.f - (bary.x * face.vertexes[0].z + bary.y * face.vertexes[1].z + bary.z * face.vertexes[2].z);
                SetPixel(round(x), round(y), PixelShader(point, bary, face.primitiveId), z);
            }
        }
    }
}

void cg::ZCulling::SetPixel(unsigned short x, unsigned short y, color color, float z) {
    if (depthBuffer[y * width + x] > z) {
        frameBuffer[y * width + x] = color;
        depthBuffer[y * width + x] = z;
    }
}


