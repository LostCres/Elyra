# Elyra Engine

Elyra is a lightweight, modular game engine designed for learning and experimentation. It provides a clean and extensible architecture for building 3D applications and games.

## Features

- **Entity-Component System (ECS):** Flexible and efficient ECS for managing game objects and their behaviors.
- **Renderer:** OpenGL-based renderer with support for materials, shaders, and primitives.
- **Scene Management:** Create, update, and manage scenes with multiple entities.
- **UI Integration:** ImGui-based UI system for debugging and in-game tools.
- **Input System:** Keyboard and mouse input handling.
- **Camera System:** Perspective and orthographic cameras with controller support.
- **Scripting:** Bind custom scripts to entities for dynamic behavior.
- **Platform:** Built with CMake for easy compilation on Windows.(Windows Only)

## Getting Started

### Prerequisites

- **CMake** (version 3.17 or higher)
- **GLFW** (included as a vendor library)
- **GLM** (included as a vendor library)
- **ImGui** (included as a vendor library)
- **OpenGL** (required for rendering)

### Building the Engine

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/elyra.git
   cd elyra
   ```

2. Create a build directory and configure the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. Build the project:
   ```bash
   cmake --build . --config Debug
   ```

### Running the Sandbox Application

The Sandbox application demonstrates the features of the Elyra Engine. After building, you can run the Sandbox executable from the `build/Sandbox` directory.

### Project Structure

- **Elyra/**: The core engine source code.
- **Sandbox/**: A sample application showcasing the engine's features.
- **vendor/**: Third-party libraries (GLFW, GLM, ImGui, etc.).

### Key Components

#### Entity-Component System (ECS)

The ECS allows you to create entities and attach components to them. Components define the data, and systems operate on entities with specific components.

Example:
```cpp
auto entity = scene->CreateEntity("Player");
entity.AddComponent<TransformComponent>();
entity.AddComponent<CameraComponent>();
```

#### Renderer

The renderer supports basic primitives, materials, and shaders. You can create and render objects like cubes, planes, and spheres.

Example:
```cpp
auto cubeMesh = Elyra::Primitives::Cube();
auto material = Elyra::Material::Create();
material->Set("u_BaseColor", glm::vec3(1.0f, 0.0f, 0.0f)); // Red
```

#### Scripting

Bind custom scripts to entities for dynamic behavior.

Example:
```cpp
class SpinScript : public Elyra::ScriptableEntity {
public:
    void OnUpdate(Elyra::TimeStep ts) override {
        auto& transform = GetComponent<Elyra::TransformComponent>();
        transform.Rotation.y += ts * glm::radians(180.0f);
    }
};
```

#### UI System

Use the ImGui-based UI system for debugging and in-game tools.

Example:
```cpp
Elyra::UI::BeginPanel("Debug Panel");
Elyra::UI::Text("Hello, Elyra!");
Elyra::UI::EndPanel();
```

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests to improve the engine.

## License

Elyra is licensed under the [Apache License 2.0](LICENSE).

## Acknowledgments

Elyra uses the following third-party libraries:
- [GLFW](https://www.glfw.org/)
- [GLM](https://github.com/g-truc/glm)
- [ImGui](https://github.com/ocornut/imgui)
- [stb_image](https://github.com/nothings/stb)

Happy coding!
