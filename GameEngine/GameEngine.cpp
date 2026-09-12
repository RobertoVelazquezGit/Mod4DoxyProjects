/// @file GameEngine.cpp
/// @brief Implements the mock engine and its rendering command worker.
#include "GameEngine.h"

#include <algorithm>
#include <iostream>


namespace GameEngine {

    /*
     * Mock graphics context.
     *
     * In a real game engine this class could manage the graphics API,
     * GPU resources, device context, command buffers, etc.
     */
    /// @brief Mock graphics context that only logs creation and destruction.
    class GraphicsContext
    {
    public:

        /// @brief Logs context creation without allocating graphics resources.
        GraphicsContext()
        {
            std::cout << "[GraphicsContext] Created\n";
        }

        /// @brief Logs context destruction.
        ~GraphicsContext()
        {
            std::cout << "[GraphicsContext] Destroyed\n";
        }
    };


    /*
     * ============================================================
     * RenderingPipeline
     * ============================================================
     */


    RenderingPipeline::RenderingPipeline(const RenderConfig& config)
        : context(nullptr),
        isRunning(false),
        metrics{ 0.0, 0, 0, 0.0 }
    {
        std::cout
            << "[RenderingPipeline] Created for "
            << config.screenWidth
            << "x"
            << config.screenHeight
            << '\n';
    }


    RenderingPipeline::~RenderingPipeline()
    {
        shutdown();

        std::cout << "[RenderingPipeline] Destroyed\n";
    }


    bool RenderingPipeline::initialize()
    {
        if (isRunning)
        {
            return true;
        }

        std::cout << "[RenderingPipeline] Initializing...\n";

        // Mock graphics context.
        context = std::make_unique<GraphicsContext>();

        isRunning = true;

        // Start the rendering worker thread.
        renderThread =
            std::thread(&RenderingPipeline::renderLoop, this);

        std::cout << "[RenderingPipeline] Initialized\n";

        return true;
    }


    void RenderingPipeline::shutdown()
    {
        if (!isRunning)
        {
            return;
        }

        std::cout << "[RenderingPipeline] Shutting down...\n";

        isRunning = false;

        // Wake up the rendering thread in case it is waiting.
        queueCondition.notify_all();

        if (renderThread.joinable())
        {
            renderThread.join();
        }

		context.reset();  // a reset unique pointer to release the graphics context 

        std::cout << "[RenderingPipeline] Shutdown complete\n";
    }


    void RenderingPipeline::submitRenderCommand(
        std::function<void()> command)
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);

            renderQueue.push(std::move(command));
        }

        // Notify the rendering thread that work is available.
        queueCondition.notify_one();
    }


    void RenderingPipeline::beginFrame()
    {
        std::cout << "[RenderingPipeline] Begin frame\n";
    }


    void RenderingPipeline::endFrame()
    {
        std::cout << "[RenderingPipeline] End frame\n";

        updateMetrics();
    }


    RenderingPipeline::PerformanceMetrics
        RenderingPipeline::getMetrics() const
    {
        return metrics;
    }


    void RenderingPipeline::optimizePerformance(
        double targetFrameTime)
    {
        std::cout
            << "[RenderingPipeline] Optimizing for target frame time: "
            << targetFrameTime
            << " ms\n";
    }


    void RenderingPipeline::renderLoop()
    {
        std::cout << "[RenderingPipeline] Render thread started\n";

        while (true)
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            queueCondition.wait(
                lock,
                [this]()
                {
                    return !renderQueue.empty() || !isRunning;
                });

            // Stop when shutdown was requested and
            // there are no remaining commands.
            if (!isRunning && renderQueue.empty())
            {
                break;
            }

            lock.unlock();

            processRenderQueue();
        }

        std::cout << "[RenderingPipeline] Render thread finished\n";
    }


    void RenderingPipeline::processRenderQueue()
    {
        while (true)
        {
            std::function<void()> command;

            {
                std::lock_guard<std::mutex> lock(queueMutex);

                if (renderQueue.empty())
                {
                    break;
                }

                command = std::move(renderQueue.front());

                renderQueue.pop();
            }

            if (command)
            {
                command();
            }
        }
    }


    void RenderingPipeline::updateMetrics()
    {
        /*
         * Mock values.
         *
         * A real implementation would obtain these values from
         * timers and the graphics API.
         */

        metrics.frameTime = 16.67;
        metrics.trianglesRendered = 1000;
        metrics.drawCalls = 10;
        metrics.gpuMemoryUsed = 128.0;

        std::cout << "[RenderingPipeline] Metrics updated\n";
    }



    /*
     * ============================================================
     * EntityComponentSystem
     * ============================================================
     */


     /*
      * Mock component pool.
      *
      * Later this could become a type-erased base class used to
      * store pools of different component types.
      */
    /// @brief Empty placeholder for future component storage.
    struct EntityComponentSystem::ComponentPool
    {
    };


    EntityComponentSystem::EntityComponentSystem()
        : nextEntityId(1)
    {
        std::cout << "[ECS] Created\n";
    }


    EntityComponentSystem::~EntityComponentSystem()
    {
        std::cout << "[ECS] Destroyed\n";
    }


    void EntityComponentSystem::destroyEntity(EntityId entity)
    {
        auto it = std::find(
            entities.begin(),
            entities.end(),
            entity);

        if (it != entities.end())
        {
            entities.erase(it);

            std::cout
                << "[ECS] Entity "
                << entity
                << " destroyed\n";
        }
        else
        {
            std::cout
                << "[ECS] Entity "
                << entity
                << " not found\n";
        }
    }


    void EntityComponentSystem::updateSystems(double deltaTime)
    {
        std::cout
            << "[ECS] Updating systems. deltaTime = "
            << deltaTime
            << " s\n";
    }

}
