#include "CubeMesh.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"

namespace Elyra {

    Ref<VertexArray> CubeMesh::Create()
    {
        Ref<VertexArray> vertexArray = VertexArray::Create();

        float vertices[] = {
            // Positions       
            -0.5f, -0.5f, -0.5f, 
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f
        };

        uint32_t indices[] = {
            0, 1, 2, 2, 3, 0, // back
            4, 5, 6, 6, 7, 4, // front
            0, 4, 7, 7, 3, 0, // left
            1, 5, 6, 6, 2, 1, // right
            3, 2, 6, 6, 7, 3, // top
            0, 1, 5, 5, 4, 0  // bottom
        };

        Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
        });

        vertexArray->AddVertexBuffer(vertexBuffer);

        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        vertexArray->SetIndexBuffer(indexBuffer);

        return vertexArray;
    }

} // namespace Elyra
