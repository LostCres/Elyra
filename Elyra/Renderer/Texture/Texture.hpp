#pragma once
#include "ElyraAPI.hpp"
#include "Elyrapch.hpp"
#include "Core/Core.hpp"

namespace Elyra {

class ELYRA_API Texture2D {
public:
    virtual ~Texture2D() = default;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual uint32_t GetRendererID() const = 0;

    virtual void Bind(uint32_t slot = 0) const = 0;

    virtual bool operator==(const Texture2D& other) const = 0;

    static Ref<Texture2D> Create(const std::string& path);
};

}
