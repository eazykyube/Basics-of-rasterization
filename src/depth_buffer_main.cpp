#include "depth_buffer.h"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        cg::ZCulling* render = new cg::ZCulling(1920, 1080, "models/CornellBox-Original.obj");

        render -> Clear();

        render -> DrawScene();

        render -> Save("results/depthBuffer.png");

        system("start results/depthBuffer.png");
    }
    catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
}