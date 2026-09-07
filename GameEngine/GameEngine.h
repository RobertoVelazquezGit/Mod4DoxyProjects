#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <atomic>
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

namespace GameEngine {

    // Forward declaration.
    // The actual mock implementation will be in GameEngine.cpp.
    class GraphicsContext;


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

        std::unique_ptr<GraphicsContext> context;

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
        void renderMesh(const MeshType& mesh,
            const MaterialType& material,
            const glm::mat4& transform)
        {
            // Mock implementation.
            // For now, the mesh, material and transform are not processed.

            std::cout << "[RenderingPipeline] renderMesh() called\n";
        }

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

        EntityComponentSystem();
        ~EntityComponentSystem();


        template<typename ComponentType>
        EntityId createEntity()
        {
            EntityId entity = nextEntityId++;

            entities.push_back(entity);

            std::cout
                << "[ECS] Entity created. ID = "
                << entity
                << '\n';

            return entity;
        }


        template<typename ComponentType>
        void addComponent(EntityId entity, ComponentType&& component)
        {
            // Mock implementation.
            // The component is not actually stored yet.

            std::cout
                << "[ECS] Component added to entity "
                << entity
                << '\n';
        }


        template<typename ComponentType>
        ComponentType* getComponent(EntityId entity)
        {
            // Mock implementation.
            // No real component storage exists yet.

            std::cout
                << "[ECS] getComponent() for entity "
                << entity
                << '\n';

            return nullptr;
        }


        template<typename... ComponentTypes>
        void forEachEntity(
            std::function<void(EntityId, ComponentTypes&...)> callback)
        {
            // Mock implementation.
            // A real ECS would find entities containing all requested
            // component types and invoke the callback for each one.

            std::cout << "[ECS] forEachEntity() called\n";
        }


        void destroyEntity(EntityId entity);


        template<typename SystemType>
        void registerSystem(std::unique_ptr<SystemType> system)
        {
            // Mock implementation.
            // The system is not stored yet.

            std::cout << "[ECS] System registered\n";
        }


        void updateSystems(double deltaTime);

    private:

        struct ComponentPool;

        std::vector<std::unique_ptr<ComponentPool>> componentPools;
        std::vector<EntityId> entities;

        EntityId nextEntityId;
    };

}