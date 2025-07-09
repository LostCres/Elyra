#include "Elyrapch.hpp"
#include "Renderer/Mesh/Mesh.hpp"

namespace Elyra {

    Mesh::Mesh() {
        m_VertexArray = VertexArray::Create(); // Keep it minimal for ECS compatibility
    }

    Mesh::~Mesh() {}

    Ref<Mesh> Mesh::Create(const std::vector<float>& vertices, const std::vector<uint32_t>& indices) {
        Ref<Mesh> mesh = CreateRef<Mesh>();

        mesh->m_VertexArray = VertexArray::Create();

        mesh->m_VertexBuffer = VertexBuffer::Create(vertices.data(), static_cast<uint32_t>(vertices.size()) * sizeof(float));
        mesh->m_VertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float3, "a_Normal" },
            { ShaderDataType::Float2, "a_TexCoord" }
        });

        mesh->m_VertexArray->AddVertexBuffer(mesh->m_VertexBuffer);

        mesh->m_IndexBuffer = IndexBuffer::Create(indices.data(), static_cast<uint32_t>(indices.size()));
        mesh->m_VertexArray->SetIndexBuffer(mesh->m_IndexBuffer);

        return mesh;
    }
    void Mesh::Bind() const {
        m_VertexArray->Bind();
    }

    void Mesh::Unbind() const {
        m_VertexArray->Unbind();
    }


}
