#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include <array>
#include <iostream>
#include <vector>

namespace vkTools
{
namespace vkPrimitives
{
struct SVertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;

    static VkVertexInputBindingDescription GetInputBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> GetAttributeBindingDescription();
};

struct SMesh
{
    std::string name;
    std::vector<SVertex> vertices;
    std::vector<uint16_t> indices;
};

struct SMVP
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

struct STransform
{
    glm::vec3 translate{1.0f};
    glm::vec3 scale{1.0f};
    glm::vec3 rotate{1.0f};
};

} // namespace vkPrimitives
} // namespace vkTools