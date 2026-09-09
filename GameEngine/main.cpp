

#include <iostream>
#include "GameEngine.h"

using namespace GameEngine;

int main()
{
    // ============================================================
    // RenderingPipeline
    // ============================================================
        RenderingPipeline::RenderConfig config{
            1920,           // screenWidth
            1080,           // screenHeight
            true,           // enableHDR
            true,           // enableAntiAliasing
            4096,           // maxTextureSize
            "./shaders"     // shaderDirectory
    };

    // Create the rendering pipeline.
    RenderingPipeline pipeline(config);

    // Initialize the rendering system and its worker thread.
    if (!pipeline.initialize())
    {
        std::cout << "Error initializing RenderingPipeline\n";
        return 1;
    }

    pipeline.beginFrame();

    // Submit a simple command to the rendering thread.
    pipeline.submitRenderCommand(
        []()
        {
            std::cout << "Executing render command\n";
        });

    pipeline.endFrame();

    // Get the mock performance metrics.
    auto metrics = pipeline.getMetrics();

    std::cout << "\n--- Performance metrics ---\n";
    std::cout << "Frame time: " << metrics.frameTime << " ms\n";
    std::cout << "Triangles:  " << metrics.trianglesRendered << '\n';
    std::cout << "Draw calls: " << metrics.drawCalls << '\n';
    std::cout << "GPU memory: " << metrics.gpuMemoryUsed << " MB\n";

    pipeline.optimizePerformance(16.67);


    // ============================================================
    // EntityComponentSystem
    // ============================================================

    EntityComponentSystem ecs;

    auto player = ecs.createEntity<int>();
    auto enemy = ecs.createEntity<int>();

    ecs.updateSystems(0.016);

    ecs.destroyEntity(enemy);


    // ============================================================
    // Shutdown
    // ============================================================

    pipeline.shutdown();

    return 0;
}

