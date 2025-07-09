#pragma once
#include "ElyraAPI.hpp"
#include "Core/Core.hpp"
#include "Renderer/Core/VertexArray.hpp"
#include "Renderer/Core/Buffer.hpp"

namespace Elyra {

    class ELYRA_API Mesh {
    public:

        Mesh(); // Default constructor for ECS or placeholder use
        ~Mesh();

        static Ref<Mesh> Create(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
        void Bind() const;
        void Unbind() const;
        const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }

    private:
        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
    };

}
