#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>

namespace GameEngine {

    /**
     * @file RenderingPipeline.h
     * @brief High-performance multi-threaded rendering engine for real-time graphics
     * @author Graphics Engine Team
     * @version 3.2.0
     *
     * ARCHITECTURE OVERVIEW
     * ====================
     *
     * The rendering pipeline uses a producer-consumer pattern with the following components:
     *
     * Main Thread (Producer):
     * - Submits render commands to thread-safe queue
     * - Manages scene updates and culling
     * - Handles user input and game logic
     *
     * Render Thread (Consumer):
     * - Processes render commands from queue
     * - Executes GPU operations and state changes
     * - Manages resource uploads and shader compilation
     *
     * Thread Safety Model:
     * - Command queue protected by mutex and condition variable
     * - Render state isolated to render thread only
     * - Metrics updated atomically for lock-free access
     *
     * Performance Targets:
     * - 60+ FPS at 1920x1080 resolution
     * - <16.67ms frame time for smooth gameplay
     * - Support for 100,000+ triangles per frame
     * - Dynamic LOD and frustum culling
     *
     * @warning Graphics context must be current on render thread only.
     *          Violating this constraint will cause undefined behavior.
     */
    class RenderingPipeline {
    public:
        struct RenderConfig {
            int screenWidth, screenHeight;
            bool enableHDR;
            bool enableAntiAliasing;
            int maxTextureSize;
            std::string shaderDirectory;
        };

        struct PerformanceMetrics {
            double frameTime;
            int trianglesRendered;
            int drawCalls;
            double gpuMemoryUsed;
        };

    private:
        std::unique_ptr<class GraphicsContext> context;
        std::queue<std::function<void()>> renderQueue;
        std::mutex queueMutex;
        std::condition_variable queueCondition;
        std::atomic<bool> isRunning;
        std::thread renderThread;
        PerformanceMetrics metrics;

    public:
        explicit RenderingPipeline(const RenderConfig& config);
        ~RenderingPipeline();

        bool initialize();
        void shutdown();

        void submitRenderCommand(std::function<void()> command);

        template<typename MeshType, typename MaterialType>
        void renderMesh(const MeshType& mesh, const MaterialType& material,
            const glm::mat4& transform);

        void beginFrame();
        void endFrame();

        PerformanceMetrics getMetrics() const;
        void optimizePerformance(double targetFrameTime);

    private:
        void renderLoop();
        void processRenderQueue();
        void updateMetrics();
    };

    class EntityComponentSystem {
    public:
        using EntityId = uint64_t;
        using ComponentTypeId = size_t;

        template<typename ComponentType>
        EntityId createEntity();

        template<typename ComponentType>
        void addComponent(EntityId entity, ComponentType&& component);

        template<typename ComponentType>
        ComponentType* getComponent(EntityId entity);

        template<typename... ComponentTypes>
        void forEachEntity(std::function<void(EntityId, ComponentTypes&...)> callback);

        void destroyEntity(EntityId entity);

        template<typename SystemType>
        void registerSystem(std::unique_ptr<SystemType> system);

        void updateSystems(double deltaTime);

    private:
        struct ComponentPool;
        std::vector<std::unique_ptr<ComponentPool>> componentPools;
        std::vector<EntityId> entities;
        EntityId nextEntityId;
    };

}

