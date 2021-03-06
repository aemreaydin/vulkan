cmake_minimum_required(VERSION 3.17)
project(VkEngine)

set(CMAKE_CXX_STANDARD 17)

set(Vulkan_INCLUDE_DIRS "$ENV{VULKAN_SDK}/Include")
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VULKAN_LIBRARY "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")
    set(SHADERC_LIBRARY "$ENV{VULKAN_SDK}/Lib/shaderc_shared.lib")
    set(VULKAN_STATIC_LIBRARY "$ENV{VULKAN_SDK}/Lib/vkstatic.1.lib")
else ()
    set(VULKAN_LIBRARY "$ENV{VULKAN_SDK}/Lib32/vulkan-1.lib")
    set(SHADERC_LIBRARY "$ENV{VULKAN_SDK}/Lib32/shaderc_shared.lib")
    set(VULKAN_STATIC_LIBRARY "$ENV{VULKAN_SDK}/Lib32/vkstatic.1.lib")
endif ()

include_directories(${Vulkan_INCLUDE_DIRS})
list(APPEND LIBS ${VULKAN_LIBRARY})
list(APPEND LIBS ${SHADERC_LIBRARY})
message(STATUS "Vulkan Include dirs: ${Vulkan_INCLUDE_DIRS} and libs: ${LIBS}, $ENV{VULKAN_SDK}")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(ThirdParty/glfw)
include_directories(ThirdParty/glfw/include)
list(APPEND LIBS glfw)

include_directories(ThirdParty/glm)
include_directories(ThirdParty/loaders)
include_directories(ThirdParty/imgui)

add_subdirectory(vkTools)
list(APPEND LIBS VkTools)

include_directories(src)
file(GLOB SRC "src/*.cpp")
add_executable(${PROJECT_NAME} main.cpp ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})
target_sources(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_demo.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_draw.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_widgets.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_impl_vulkan.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui/imgui_impl_glfw.cpp"
        )

# Copy assets to build
#
#set(ASSETS ${CMAKE_SOURCE_DIR}/assets)
#set(DESTINATION_ASSETS ${CMAKE_CURRENT_BINARY_DIR}/assets)
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS} ${DESTINATION_ASSETS}
#        COMMENT "copy folder from ${ASSETS} => ${DESTINATION_ASSETS}")
