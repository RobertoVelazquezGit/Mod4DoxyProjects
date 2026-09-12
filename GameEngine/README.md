# GameEngine

Educational C++ project demonstrating a basic game engine structure:
a rendering pipeline and an entity-component system (ECS).
It provides an example for exploring source code and its documentation with Doxygen.

Graphics operations and component management are simulated through console
messages. The command queue, rendering thread and entity identifier registry
have functional implementations.

## Main Classes

- GameEngine::RenderingPipeline: manages a command queue processed by a worker
  thread. It supports starting and stopping processing, marking frame boundaries
  and retrieving simulated metrics.
- GameEngine::EntityComponentSystem: creates and removes entity identifiers.
  It provides example component and system methods, without actually storing
  or processing those elements yet.
- GameEngine::GraphicsContext: represents a mock graphics context that logs
  its creation and destruction.

GameEngine::RenderingPipeline::RenderConfig groups the rendering settings.
GameEngine::RenderingPipeline::PerformanceMetrics holds frame statistics,
with time in milliseconds and GPU memory in megabytes.

## Example Execution

The main() function demonstrates the following sequence:

1. Prepares a 1920 x 1080 screen configuration and initializes the pipeline.
2. Begins a frame and submits a command that prints a message from the rendering thread.
3. Ends the frame, retrieves simulated metrics and logs a performance target.
4. Creates two entities, requests a system update and removes one entity.
5. Shuts down the pipeline, waits for pending commands to finish and releases the context.

## Scope of the Mocks

- No window is opened and no meshes are drawn; `renderMesh()` only prints a message.
- Metrics contain fixed values and do not represent hardware measurements.
- Graphics configuration options are not applied, and optimization only logs a message.
- Components are not stored, and `getComponent()` always returns `nullptr`.
- Entity iteration does not invoke the callback, and systems are neither stored nor executed.

## Project Files

- `GameEngine.h`: class and structure declarations and template methods.
- `GameEngine.cpp`: implementation of the pipeline, graphics context and ECS.
- `main.cpp`: demonstration program.
- `GameEngine.vcxproj`: Visual Studio project.
- `Doxyfile`: documentation generation configuration.
- `README.md`: project overview for the Doxygen main page.

## Development Environment

The project uses Visual Studio Community and the MSVC compiler.
The GLM library provides the `glm::mat4` type used by the rendering interface.
To build and run the example, open the solution in Visual Studio and select
GameEngine as the startup project, with GLM available in the include paths.

## Doxygen Documentation

The source code uses `///` comments with tags such as `@brief`, `@param`,
`@tparam` and `@return`. Fully qualified class names on this page allow navigation
to their documentation when Doxygen processes the source files.

To use this document as the main page, configure the following in `Doxyfile`:

```text
USE_MDFILE_AS_MAINPAGE = README.md
```

Include this file in the Doxygen input and enable Markdown processing.
From the `GameEngine` directory, generate the documentation with:

```powershell
doxygen Doxyfile
```

If HTML output is configured in `docs/html`, open `docs/html/index.html`
to view the result. Dot-based diagrams require Graphviz.
