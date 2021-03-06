#pragma once
#include "CBufferImageManager.hpp"
#include "CDevice.hpp"
#include "CObject.hpp"
#include "vkPrimitives.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <vulkan/vulkan.h>


struct SModelProps
{
    std::string modelName;
    std::string objectFile;
    std::string textureFile;
    vkTools::vkPrimitives::STransform modelTransform{};
};

class CGameObject : public CObject
{
  public:
    explicit CGameObject(SModelProps modelProps);

    void UpdateUniformBuffers() override;
    void Draw() const override;
    void ObjectCleanup() override;

    uint32_t GetVerticesSize() const
    {
        return static_cast<uint32_t>(sizeof(vkTools::vkPrimitives::SVertex) * m_mesh.vertices.size());
    }
    uint16_t GetIndicesSize() const
    {
        return static_cast<uint16_t>(sizeof(uint16_t) * m_mesh.indices.size());
    }
    uint32_t GetUniformSize() const
    {
        return static_cast<uint32_t>(sizeof(m_mvp));
    }
  private:
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateUniformBuffers();
    void CreateDescriptorSets();
    void CreateTextureImage();
    void CreateTextureSampler();

    CDevice *mp_deviceInstance;

    SBufferHandles m_vertexBufferHandles{};
    SBufferHandles m_indexBufferHandles{};
    std::vector<SBufferHandles> m_vecUniformBufferHandles{};
    std::vector<VkDescriptorSet> m_vecDescriptorSets;
    SImageHandles m_textureImageHandles{};
    VkSampler m_textureSampler;

    vkTools::vkPrimitives::SMesh m_mesh;
    vkTools::vkPrimitives::SMVP m_mvp{};
    SModelProps m_modelProps{};
};