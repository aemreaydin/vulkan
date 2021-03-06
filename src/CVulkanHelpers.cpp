#include "CVulkanHelpers.hpp"
// TODO MOVE TO vkTools
std::vector<const char *> CVulkanHelpers::GetVulkanInstanceExtensions()
{
    if (glfwVulkanSupported() == GLFW_FALSE)
        throw std::runtime_error("Vulkan is not supported.");
    uint32_t glfwExtensionCount;
    const auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> vExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    // TODO add debug check
    vExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return vExtensions;
}
std::vector<VkExtensionProperties> CVulkanHelpers::GetVulkanDeviceExtensions(VkPhysicalDevice const &physicalDevice)
{
    uint32_t extPropsCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extPropsCount, nullptr);
    std::vector<VkExtensionProperties> extensionProps(extPropsCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extPropsCount, extensionProps.data());
    return extensionProps;
}
std::vector<VkLayerProperties> CVulkanHelpers::GetVulkanLayers()
{
    uint32_t layerPropsCount;
    vkEnumerateInstanceLayerProperties(&layerPropsCount, nullptr);
    std::vector<VkLayerProperties> layerProps(layerPropsCount);
    vkEnumerateInstanceLayerProperties(&layerPropsCount, layerProps.data());
    return layerProps;
}
bool CVulkanHelpers::CheckForVulkanInstanceExtensions(VkPhysicalDevice const &physicalDevice,
                                                      const std::vector<const char *> &extensionsToCheck)
{
    const auto extensions = GetVulkanDeviceExtensions(physicalDevice);

    for (const auto &vulkanLayer : extensionsToCheck)
    {
        auto found = false;
        for (const auto &extension : extensions)
        {
            if (strcmp(vulkanLayer, extension.extensionName) == 0)
            {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }

    return true;
}
bool CVulkanHelpers::CheckForVulkanLayers(const std::vector<const char *> &layersToCheck)
{
    const auto layerProps = GetVulkanLayers();

    for (const auto &vulkanLayer : layersToCheck)
    {
        auto found = false;
        for (const auto &layer : layerProps)
        {
            if (strcmp(vulkanLayer, layer.layerName) == 0)
            {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }

    return true;
}

void CVulkanHelpers::GetSupportForSwapchain(const VkPhysicalDevice &device, const VkSurfaceKHR &surface,
                                            SSwapchainSupport &swapchainSupport)
{
    swapchainSupport = {};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &swapchainSupport.surfaceCapabilities);

    uint32_t surfaceFormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &surfaceFormatCount, nullptr);
    swapchainSupport.surfaceFormats.resize(surfaceFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &surfaceFormatCount, swapchainSupport.surfaceFormats.data());

    uint32_t surfacePresentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &surfacePresentModeCount, nullptr);
    swapchainSupport.surfacePresentModes.resize(surfacePresentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &surfacePresentModeCount,
                                              swapchainSupport.surfacePresentModes.data());
}
