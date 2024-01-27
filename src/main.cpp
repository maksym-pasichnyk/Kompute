#include "dispatcher.hpp"
#include "file_utils.hpp"

#include "SDL_video.h"
#include "SDL_vulkan.h"
#include "SDL_events.h"

static constexpr u32 MAX_FRAMES_IN_FLIGHT = 3;

struct VulkanApplication {
    SDL_Window* WindowPlatform;

    VkDeviceDispatcher* DeviceDispatcher;
    VkContextDispatcher* ContextDispatcher;
    VkInstanceDispatcher* InstanceDispatcher;

    u32 InstanceLayerPropertyCount;
    VkLayerProperties* InstanceLayerProperties;

    VkInstance Instance;
    VkDebugUtilsMessengerEXT DebugUtilsMessengerEXT;
    u32 PhysicalDeviceCount;
    VkPhysicalDevice* PhysicalDevices;
    VkPhysicalDevice PhysicalDevice;
    VkDevice LogicalDevice;
    VkSurfaceCapabilitiesKHR SurfaceCapabilities;

    VkSurfaceKHR Surface;
    VkSwapchainKHR Swapchain;
    u32 SurfaceImageIndex;
    u32 SurfaceImageCount;
    VkImage* SurfaceImages;
    VkImageView* SurfaceImageViews;

    VkImage ComputeImage;
    VkImageView ComputeImageView;
    VkDeviceMemory ComputeImageMemory;

    VkQueue Queue;
    u32 QueueIndex;
    u32 QueueFamilyIndex;

    VkFence* Fences;
    VkSemaphore* SubmitSemaphores;
    VkSemaphore* AcquireSemaphores;
    VkCommandPool* CommandPools;
    VkCommandBuffer* CommandBuffers;
    VkDescriptorPool* DescriptorPools;
    VkSemaphore TimelineSemaphore;

    VkPipeline ComputePipeline;
    VkPipelineLayout ComputePipelineLayout;
    VkDescriptorSetLayout ComputeDescriptorSetLayout;

    VulkanApplication() {
        this->CreateWindowPlatform();
        this->CreateVulkanInstance();
        this->CreateLogicalDevice();
        this->CreateDeviceObjects();
        this->CreateVulkanShaders();
        this->CreateVulkanTextures();
    }

    ~VulkanApplication() {
        this->DeleteVulkanTextures();
        this->DeleteVulkanShaders();
        this->DeleteDeviceObjects();
        this->DeleteLogicalDevice();
        this->DeleteVulkanInstance();
        this->DeleteWindowPlatform();
    }

    void CreateWindowPlatform(this VulkanApplication& Self) {
        Self.WindowPlatform = SDL_CreateWindow("Kompute", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_VULKAN);
    }

    void DeleteWindowPlatform(this VulkanApplication& Self) {
        SDL_DestroyWindow(Self.WindowPlatform);
    }

    void CreateVulkanInstance(this VulkanApplication& Self) {
        Self.ContextDispatcher = new VkContextDispatcher(PFN_vkGetInstanceProcAddr(SDL_Vulkan_GetVkGetInstanceProcAddr()));
        Self.ContextDispatcher->vkEnumerateInstanceLayerProperties(&Self.InstanceLayerPropertyCount, nullptr);
        Self.InstanceLayerProperties = new VkLayerProperties[Self.InstanceLayerPropertyCount];
        Self.ContextDispatcher->vkEnumerateInstanceLayerProperties(&Self.InstanceLayerPropertyCount, Self.InstanceLayerProperties);

        char const* EnabledLayerNames[] = {
            "VK_LAYER_KHRONOS_validation",
        };
        char const* EnabledExtensionNames[] = {
            "VK_KHR_surface",
            "VK_EXT_debug_utils",
            "VK_MVK_macos_surface",
            "VK_KHR_portability_enumeration",
            "VK_KHR_get_physical_device_properties2"
        };
        Self.ContextDispatcher->vkCreateInstance(
            (VkInstanceCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
                .pApplicationInfo = (VkApplicationInfo[]) {{
                    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                    .pApplicationName = "Demo",
                    .applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0),
                    .pEngineName = "Kompute",
                    .engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0),
                    .apiVersion = VK_API_VERSION_1_2
                }},
                .enabledLayerCount = std::size(EnabledLayerNames),
                .ppEnabledLayerNames = std::data(EnabledLayerNames),
                .enabledExtensionCount = std::size(EnabledExtensionNames),
                .ppEnabledExtensionNames = std::data(EnabledExtensionNames),
            }},
            nullptr,
            &Self.Instance
        );
        Self.InstanceDispatcher = new VkInstanceDispatcher(Self.ContextDispatcher->vkGetInstanceProcAddr, Self.Instance);
        Self.InstanceDispatcher->vkCreateDebugUtilsMessengerEXT(
            Self.Instance,
            (VkDebugUtilsMessengerCreateInfoEXT[]){{
                .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
                .flags = {},
                .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
                .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT,
                .pfnUserCallback = &DebugUtilsCallback
            }},
            nullptr,
            &Self.DebugUtilsMessengerEXT
        );
        Self.InstanceDispatcher->vkEnumeratePhysicalDevices(Self.Instance, &Self.PhysicalDeviceCount, nullptr);
        Self.PhysicalDevices = new VkPhysicalDevice[Self.PhysicalDeviceCount];
        Self.InstanceDispatcher->vkEnumeratePhysicalDevices(Self.Instance, &Self.PhysicalDeviceCount, Self.PhysicalDevices);

        SDL_Vulkan_CreateSurface(Self.WindowPlatform, Self.Instance, &Self.Surface);
    }

    void DeleteVulkanInstance(this VulkanApplication& Self) {
        Self.InstanceDispatcher->vkDestroySurfaceKHR(Self.Instance, Self.Surface, nullptr);
        Self.InstanceDispatcher->vkDestroyDebugUtilsMessengerEXT(Self.Instance, Self.DebugUtilsMessengerEXT, nullptr);
        Self.InstanceDispatcher->vkDestroyInstance(Self.Instance, nullptr);
        delete[] Self.PhysicalDevices;
        delete[] Self.InstanceLayerProperties;
    }

    void CreateLogicalDevice(this VulkanApplication& Self) {
//        for (u32 i = 0; i < Self.PhysicalDeviceCount; i += 1) {
//            auto Core_1_3 = VkPhysicalDeviceVulkan13Features{
//                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
//                .pNext = {}
//            };
//            auto Core_1_2 = VkPhysicalDeviceVulkan12Features{
//                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
//                .pNext = &Core_1_3
//            };
//            auto Core_1_1 = VkPhysicalDeviceVulkan11Features{
//                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
//                .pNext = &Core_1_2
//            };
//            auto Features2 = VkPhysicalDeviceFeatures2{
//                .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
//                .pNext = &Core_1_1,
//                .features = {}
//            };
//
//            auto PhysicalDevice = Self.PhysicalDevices[i];
//            PhysicalDevice->GetPhysicalDeviceFeatures2(&Features2);
//        }

        auto EnabledExtensionNames = std::array{
            "VK_KHR_swapchain",
            "VK_KHR_copy_commands2",
            "VK_KHR_synchronization2",
            "VK_KHR_timeline_semaphore",
            "VK_KHR_portability_subset",
        };

        Self.PhysicalDevice = Self.PhysicalDevices[0];
        Self.QueueIndex = 0;
        Self.QueueFamilyIndex = 0;

        auto QueueCreateInfos = std::array{
            VkDeviceQueueCreateInfo{
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                .pNext = {},
                .queueFamilyIndex = Self.QueueFamilyIndex,
                .queueCount = 1,
                .pQueuePriorities = (f32[]) {1.0f}
            }
        };

        auto Core_1_1 = VkPhysicalDeviceVulkan11Features{
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES,
            .pNext = {}
        };
        auto Core_1_2 = VkPhysicalDeviceVulkan12Features{
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
            .pNext = &Core_1_1,
            .timelineSemaphore = VK_TRUE,
            .bufferDeviceAddress = VK_TRUE
        };
        auto Core_1_3 = VkPhysicalDeviceSynchronization2Features{
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES,
            .pNext = &Core_1_2,
            .synchronization2 = VK_TRUE
        };
//        auto Core_1_3 = VkPhysicalDeviceVulkan13Features{
//            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
//            .pNext = &Core_1_2,
//            .synchronization2 = VK_TRUE
//        };
        auto Features2 = VkPhysicalDeviceFeatures2{
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
            .pNext = &Core_1_3,
            .features = {
                .shaderInt64 = VK_TRUE
            }
        };
        Self.InstanceDispatcher->vkCreateDevice(
            Self.PhysicalDevice,
            (VkDeviceCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                .pNext = &Features2,
                .queueCreateInfoCount = QueueCreateInfos.size(),
                .pQueueCreateInfos = QueueCreateInfos.data(),
                .enabledLayerCount = 0,
                .ppEnabledLayerNames = {},
                .enabledExtensionCount = EnabledExtensionNames.size(),
                .ppEnabledExtensionNames = EnabledExtensionNames.data()
            }},
            nullptr,
            &Self.LogicalDevice
        );
        Self.DeviceDispatcher = new VkDeviceDispatcher(Self.InstanceDispatcher->vkGetDeviceProcAddr, Self.LogicalDevice);
        Self.DeviceDispatcher->vkGetDeviceQueue2(
            Self.LogicalDevice,
            (VkDeviceQueueInfo2[]){{
                .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2,
                .pNext = {},
                .flags = {},
                .queueFamilyIndex = Self.QueueFamilyIndex,
                .queueIndex = Self.QueueIndex
            }},
            &Self.Queue
        );
    }

    void DeleteLogicalDevice(this VulkanApplication& Self) {
        Self.DeviceDispatcher->vkDestroyDevice(Self.LogicalDevice, nullptr);
    }

    void CreateDeviceObjects(this VulkanApplication& Self) {
        Self.Fences = new VkFence[MAX_FRAMES_IN_FLIGHT];
        Self.SubmitSemaphores = new VkSemaphore[MAX_FRAMES_IN_FLIGHT];
        Self.AcquireSemaphores = new VkSemaphore[MAX_FRAMES_IN_FLIGHT];
        Self.CommandPools = new VkCommandPool[MAX_FRAMES_IN_FLIGHT];
        Self.CommandBuffers = new VkCommandBuffer[MAX_FRAMES_IN_FLIGHT];
        Self.DescriptorPools = new VkDescriptorPool[MAX_FRAMES_IN_FLIGHT];
        Self.DeviceDispatcher->vkCreateSemaphore(
            Self.LogicalDevice,
            (VkSemaphoreCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .pNext = (VkSemaphoreTypeCreateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                    .pNext = {},
                    .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
                    .initialValue = 0
                }}
            }},
            nullptr,
            &Self.TimelineSemaphore
        );
        for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i += 1) {
            Self.DeviceDispatcher->vkCreateFence(
                Self.LogicalDevice,
                (VkFenceCreateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                    .flags = {},
                }},
                nullptr,
                &Self.Fences[i]
            );
            Self.DeviceDispatcher->vkCreateSemaphore(
                Self.LogicalDevice,
                (VkSemaphoreCreateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                    .pNext = (VkSemaphoreTypeCreateInfo[]){{
                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                        .pNext = {},
                        .semaphoreType = VK_SEMAPHORE_TYPE_BINARY,
                    }}
                }},
                nullptr,
                &Self.SubmitSemaphores[i]
            );
            Self.DeviceDispatcher->vkCreateSemaphore(
                Self.LogicalDevice,
                (VkSemaphoreCreateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                    .pNext = (VkSemaphoreTypeCreateInfo[]){{
                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
                        .pNext = {},
                        .semaphoreType = VK_SEMAPHORE_TYPE_BINARY,
                    }}
                }},
                nullptr,
                &Self.AcquireSemaphores[i]
            );
            Self.DeviceDispatcher->vkCreateCommandPool(
                Self.LogicalDevice,
                (VkCommandPoolCreateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                    .pNext = {},
                    .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                    .queueFamilyIndex = Self.QueueFamilyIndex
                }},
                nullptr,
                &Self.CommandPools[i]
            );
            Self.DeviceDispatcher->vkAllocateCommandBuffers(
                Self.LogicalDevice,
                (VkCommandBufferAllocateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                    .commandPool = Self.CommandPools[i],
                    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                    .commandBufferCount = 1,
                }},
                &Self.CommandBuffers[i]
            );
            Self.DeviceDispatcher->vkCreateDescriptorPool(
                Self.LogicalDevice,
                (VkDescriptorPoolCreateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                    .pNext = {},
                    .flags = {},
                    .maxSets = 1,
                    .poolSizeCount = 1,
                    .pPoolSizes = (VkDescriptorPoolSize[]) {
                        VkDescriptorPoolSize(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1)
                    }
                }},
                nullptr,
                &Self.DescriptorPools[i]
            );
        }
    }

    void DeleteDeviceObjects(this VulkanApplication& Self) {
        for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i += 1) {
            Self.DeviceDispatcher->vkDestroyFence(Self.LogicalDevice, Self.Fences[i], nullptr);
            Self.DeviceDispatcher->vkDestroyCommandPool(Self.LogicalDevice, Self.CommandPools[i], nullptr);
            Self.DeviceDispatcher->vkDestroySemaphore(Self.LogicalDevice, Self.SubmitSemaphores[i], nullptr);
            Self.DeviceDispatcher->vkDestroySemaphore(Self.LogicalDevice, Self.AcquireSemaphores[i], nullptr);
            Self.DeviceDispatcher->vkDestroyDescriptorPool(Self.LogicalDevice, Self.DescriptorPools[i], nullptr);
        }
        Self.DeviceDispatcher->vkDestroySemaphore(Self.LogicalDevice, Self.TimelineSemaphore, nullptr);
        delete[] Self.Fences;
        delete[] Self.CommandPools;
        delete[] Self.CommandBuffers;
        delete[] Self.DescriptorPools;
        delete[] Self.SubmitSemaphores;
        delete[] Self.AcquireSemaphores;
    }

    void CreateVulkanShaders(this VulkanApplication& Self) {
        auto ComputeShaderBytes = file_read_bytes("../shaders/ps.comp.spv").value();

        Self.DeviceDispatcher->vkCreateDescriptorSetLayout(
            Self.LogicalDevice,
            (VkDescriptorSetLayoutCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                .pNext = {},
                .flags = {},
                .bindingCount = 1,
                .pBindings = (VkDescriptorSetLayoutBinding[]){
                    VkDescriptorSetLayoutBinding{
                        .binding = 0,
                        .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
                        .descriptorCount = 1,
                        .stageFlags = VK_SHADER_STAGE_COMPUTE_BIT,
                        .pImmutableSamplers = nullptr
                    }
                }
            }},
            nullptr,
            &Self.ComputeDescriptorSetLayout
        );
        Self.DeviceDispatcher->vkCreatePipelineLayout(
            Self.LogicalDevice,
            (VkPipelineLayoutCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                .pNext = {},
                .flags = {},
                .setLayoutCount = 1,
                .pSetLayouts = (VkDescriptorSetLayout[]){
                    Self.ComputeDescriptorSetLayout
                },
            }},
            nullptr,
            &Self.ComputePipelineLayout
        );

        VkShaderModule ComputeShaderModule;
        Self.DeviceDispatcher->vkCreateShaderModule(
            Self.LogicalDevice,
            (VkShaderModuleCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                .pNext = {},
                .flags = {},
                .codeSize = ComputeShaderBytes.size(),
                .pCode = std::bit_cast<u32 const*>(ComputeShaderBytes.data()),
            }},
            nullptr,
            &ComputeShaderModule
        );

        Self.DeviceDispatcher->vkCreateComputePipelines(
            Self.LogicalDevice,
            nullptr,
            1,
            (VkComputePipelineCreateInfo[]) {{
                .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
                .pNext = {},
                .flags = VK_PIPELINE_CREATE_DISPATCH_BASE_BIT,
                .stage = VkPipelineShaderStageCreateInfo{
                    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    .pNext = {},
                    .flags = {},
                    .stage = VK_SHADER_STAGE_COMPUTE_BIT,
                    .module = ComputeShaderModule,
                    .pName = "main",
                    .pSpecializationInfo = (VkSpecializationInfo[]){{
                        .mapEntryCount = 3,
                        .pMapEntries = (VkSpecializationMapEntry[]){
                            VkSpecializationMapEntry(0, 0, sizeof(u32)),
                            VkSpecializationMapEntry(1, 4, sizeof(u32)),
                            VkSpecializationMapEntry(2, 8, sizeof(u32)),
                        },
                        .dataSize = sizeof(u32[3]),
                        .pData = (u32[]){32, 32, 1}
                    }},
                },
                .layout = Self.ComputePipelineLayout,
                .basePipelineHandle = {},
                .basePipelineIndex = {}
            }},
            nullptr,
            &Self.ComputePipeline
        );
        Self.DeviceDispatcher->vkDestroyShaderModule(Self.LogicalDevice, ComputeShaderModule, nullptr);
    }

    void DeleteVulkanShaders(this VulkanApplication& Self) {
        Self.DeviceDispatcher->vkDestroyPipeline(Self.LogicalDevice, Self.ComputePipeline, nullptr);
        Self.DeviceDispatcher->vkDestroyPipelineLayout(Self.LogicalDevice, Self.ComputePipelineLayout, nullptr);
        Self.DeviceDispatcher->vkDestroyDescriptorSetLayout(Self.LogicalDevice, Self.ComputeDescriptorSetLayout, nullptr);
    }

    void CreateVulkanTextures(this VulkanApplication& Self) {
        Self.InstanceDispatcher->vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Self.PhysicalDevice, Self.Surface, &Self.SurfaceCapabilities);
        Self.DeviceDispatcher->vkCreateSwapchainKHR(
            Self.LogicalDevice,
            (VkSwapchainCreateInfoKHR[]){{
                .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                .pNext = {},
                .flags = {},
                .surface = Self.Surface,
                .minImageCount = 3,
                .imageFormat = VK_FORMAT_B8G8R8A8_UNORM,
                .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
                .imageExtent = Self.SurfaceCapabilities.currentExtent,
                .imageArrayLayers = 1,
                .imageUsage = Self.SurfaceCapabilities.supportedUsageFlags,
                .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
                .queueFamilyIndexCount = 0,
                .pQueueFamilyIndices = {},
                .preTransform = Self.SurfaceCapabilities.currentTransform,
                .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                .presentMode = VK_PRESENT_MODE_FIFO_KHR,
                .clipped = VK_FALSE,
                .oldSwapchain = {},
            }},
            nullptr,
            &Self.Swapchain
        );
        Self.DeviceDispatcher->vkGetSwapchainImagesKHR(Self.LogicalDevice, Self.Swapchain, &Self.SurfaceImageCount, nullptr);
        Self.SurfaceImages = new VkImage[Self.SurfaceImageCount];
        Self.DeviceDispatcher->vkGetSwapchainImagesKHR(Self.LogicalDevice, Self.Swapchain, &Self.SurfaceImageCount, Self.SurfaceImages);

        Self.SurfaceImageViews = new VkImageView[Self.SurfaceImageCount];
        for (u32 i = 0; i < Self.SurfaceImageCount; i += 1) {
            Self.DeviceDispatcher->vkCreateImageView(
                Self.LogicalDevice,
                (VkImageViewCreateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                    .pNext = {},
                    .flags = {},
                    .image = Self.SurfaceImages[i],
                    .viewType = VK_IMAGE_VIEW_TYPE_2D,
                    .format = VK_FORMAT_B8G8R8A8_UNORM,
                    .components = VkComponentMapping{
                        .r = VK_COMPONENT_SWIZZLE_R,
                        .g = VK_COMPONENT_SWIZZLE_G,
                        .b = VK_COMPONENT_SWIZZLE_B,
                        .a = VK_COMPONENT_SWIZZLE_A,
                    },
                    .subresourceRange = VkImageSubresourceRange{
                        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                        .baseMipLevel = 0,
                        .levelCount = 1,
                        .baseArrayLayer = 0,
                        .layerCount = 1
                    }
                }},
                nullptr,
                &Self.SurfaceImageViews[i]
            );
        }
        Self.DeviceDispatcher->vkCreateImage(
            Self.LogicalDevice,
            (VkImageCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
                .pNext = {},
                .flags = {},
                .imageType = VK_IMAGE_TYPE_2D,
                .format = VK_FORMAT_R8G8B8A8_UNORM,
                .extent = VkExtent3D{
                    .width = Self.SurfaceCapabilities.currentExtent.width,
                    .height = Self.SurfaceCapabilities.currentExtent.height,
                    .depth = 1
                },
                .mipLevels = 1,
                .arrayLayers = 1,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .tiling = VK_IMAGE_TILING_OPTIMAL,
                .usage = VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
                .queueFamilyIndexCount = 0,
                .pQueueFamilyIndices = {},
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            }},
            nullptr,
            &Self.ComputeImage
        );
        VkMemoryRequirements ComputeImageMemoryRequirements;
        Self.DeviceDispatcher->vkGetImageMemoryRequirements(Self.LogicalDevice, Self.ComputeImage, &ComputeImageMemoryRequirements);
        Self.DeviceDispatcher->vkAllocateMemory(
            Self.LogicalDevice,
            (VkMemoryAllocateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .pNext = (VkMemoryAllocateFlagsInfo[]) {{
                    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
                    .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT
                }},
                .allocationSize = ComputeImageMemoryRequirements.size,
                .memoryTypeIndex = 0
            }},
            nullptr,
            &Self.ComputeImageMemory
        );
        Self.DeviceDispatcher->vkBindImageMemory(Self.LogicalDevice, Self.ComputeImage, Self.ComputeImageMemory, 0zu);
        Self.DeviceDispatcher->vkCreateImageView(
            Self.LogicalDevice,
            (VkImageViewCreateInfo[]){{
                .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                .pNext = {},
                .flags = {},
                .image = Self.ComputeImage,
                .viewType = VK_IMAGE_VIEW_TYPE_2D,
                .format = VK_FORMAT_R8G8B8A8_UNORM,
                .components = VkComponentMapping{
                    .r = VK_COMPONENT_SWIZZLE_R,
                    .g = VK_COMPONENT_SWIZZLE_G,
                    .b = VK_COMPONENT_SWIZZLE_B,
                    .a = VK_COMPONENT_SWIZZLE_A,
                },
                .subresourceRange = VkImageSubresourceRange{
                    .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                    .baseMipLevel = 0,
                    .levelCount = 1,
                    .baseArrayLayer = 0,
                    .layerCount = 1
                }
            }},
            nullptr,
            &Self.ComputeImageView
        );
    }

    void DeleteVulkanTextures(this VulkanApplication& Self) {
        for (u32 i = 0; i < Self.SurfaceImageCount; i += 1) {
            Self.DeviceDispatcher->vkDestroyImageView(Self.LogicalDevice, Self.SurfaceImageViews[i], nullptr);
        }
        Self.DeviceDispatcher->vkDestroySwapchainKHR(Self.LogicalDevice, Self.Swapchain, nullptr);

        Self.DeviceDispatcher->vkDestroyImageView(Self.LogicalDevice, Self.ComputeImageView, nullptr);
        Self.DeviceDispatcher->vkDestroyImage(Self.LogicalDevice, Self.ComputeImage, nullptr);
        Self.DeviceDispatcher->vkFreeMemory(Self.LogicalDevice, Self.ComputeImageMemory, nullptr);

        delete[] Self.SurfaceImages;
        delete[] Self.SurfaceImageViews;
    }

    void StartLoop(this VulkanApplication& Self) {
        u32 FrameIndex = 0;
        u32 TotalFrameIndex = 0;

        bool Quit = false;
        while (!Quit) {
            SDL_Event Event;
            while (SDL_PollEvent(&Event) == 1) {
                if (Event.type == SDL_QUIT) {
                    Quit = true;
                }
            }

            if (TotalFrameIndex >= MAX_FRAMES_IN_FLIGHT) {
                Self.DeviceDispatcher->vkWaitSemaphoresKHR(
                    Self.LogicalDevice,
                    (VkSemaphoreWaitInfo[]){{
                        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
                        .pNext = {},
                        .flags = {},
                        .semaphoreCount = 1,
                        .pSemaphores = (VkSemaphore[]){ Self.TimelineSemaphore },
                        .pValues = (u64[]) { TotalFrameIndex - MAX_FRAMES_IN_FLIGHT + 1 },
                    }},
                    std::numeric_limits<u64>::max()
                );
//                Self.DeviceDispatcher->vkWaitForFences(Self.LogicalDevice, 1, &Self.Fences[FrameIndex], VK_TRUE, UINT64_MAX);
//                Self.DeviceDispatcher->vkResetFences(Self.LogicalDevice, 1, &Self.Fences[FrameIndex]);
                Self.DeviceDispatcher->vkResetDescriptorPool(Self.LogicalDevice, Self.DescriptorPools[FrameIndex], VkDescriptorPoolResetFlags());
            }

            Self.DeviceDispatcher->vkAcquireNextImage2KHR(
                Self.LogicalDevice,
                (VkAcquireNextImageInfoKHR[]){{
                    .sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR,
                    .pNext = {},
                    .swapchain = Self.Swapchain,
                    .timeout = std::numeric_limits<u64>::max(),
                    .semaphore = Self.AcquireSemaphores[FrameIndex],
                    .fence = {},
                    .deviceMask = 1
                }},
                &Self.SurfaceImageIndex
            );
            Self.DeviceDispatcher->vkBeginCommandBuffer(
                Self.CommandBuffers[FrameIndex],
                (VkCommandBufferBeginInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
                }}
            );
            Self.DeviceDispatcher->vkCmdPipelineBarrier2(
                Self.CommandBuffers[FrameIndex],
                (VkDependencyInfo[]) {{
                    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                    .pNext = {},
                    .dependencyFlags = {},
                    .imageMemoryBarrierCount = 1,
                    .pImageMemoryBarriers = (VkImageMemoryBarrier2[]) {
                        VkImageMemoryBarrier2{
                            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                            .srcStageMask = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT,
                            .srcAccessMask = VK_ACCESS_2_NONE,
                            .dstStageMask = VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT,
                            .dstAccessMask = VK_ACCESS_2_SHADER_STORAGE_READ_BIT | VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT,
                            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                            .newLayout = VK_IMAGE_LAYOUT_GENERAL,
                            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .image = Self.ComputeImage,
                            .subresourceRange = VkImageSubresourceRange{
                                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                .baseMipLevel = 0,
                                .levelCount = 1,
                                .baseArrayLayer = 0,
                                .layerCount = 1
                            }
                        }
                    }
                }}
            );

            VkDescriptorSet ComputeDescriptorSet;
            Self.DeviceDispatcher->vkAllocateDescriptorSets(
                Self.LogicalDevice,
                (VkDescriptorSetAllocateInfo[]){{
                    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                    .pNext = {},
                    .descriptorPool = Self.DescriptorPools[FrameIndex],
                    .descriptorSetCount = 1,
                    .pSetLayouts = (VkDescriptorSetLayout[]){
                        Self.ComputeDescriptorSetLayout
                    }
                }},
                &ComputeDescriptorSet
            );

            Self.DeviceDispatcher->vkUpdateDescriptorSets(
                Self.LogicalDevice,
                1, (VkWriteDescriptorSet[]){
                    VkWriteDescriptorSet{
                        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                        .pNext = {},
                        .dstSet = ComputeDescriptorSet,
                        .dstBinding = 0,
                        .dstArrayElement = 0,
                        .descriptorCount = 1,
                        .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
                        .pImageInfo = (VkDescriptorImageInfo[]){{
                            .sampler = {},
                            .imageView = Self.ComputeImageView,
                            .imageLayout = VK_IMAGE_LAYOUT_GENERAL
                        }},
                        .pBufferInfo = {},
                        .pTexelBufferView = {},
                    }
                },
                0, (VkCopyDescriptorSet[]){}
            );

            Self.DeviceDispatcher->vkCmdBindPipeline(Self.CommandBuffers[FrameIndex], VK_PIPELINE_BIND_POINT_COMPUTE, Self.ComputePipeline);
            Self.DeviceDispatcher->vkCmdBindDescriptorSets(Self.CommandBuffers[FrameIndex], VK_PIPELINE_BIND_POINT_COMPUTE, Self.ComputePipelineLayout, 0, 1, &ComputeDescriptorSet, 0, {});

            auto GroupSizeX = (Self.SurfaceCapabilities.currentExtent.width + 32 - 1) / 32;
            auto GroupSizeY = (Self.SurfaceCapabilities.currentExtent.height + 32 - 1) / 32;
            Self.DeviceDispatcher->vkCmdDispatchBase(Self.CommandBuffers[FrameIndex], 0, 0, 0, GroupSizeX, GroupSizeY, 1);
            Self.DeviceDispatcher->vkCmdPipelineBarrier2(
                Self.CommandBuffers[FrameIndex],
                (VkDependencyInfo[]) {{
                    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                    .pNext = {},
                    .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT,
                    .imageMemoryBarrierCount = 2,
                    .pImageMemoryBarriers = (VkImageMemoryBarrier2[]) {
                        VkImageMemoryBarrier2{
                            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                            .srcStageMask = VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT,
                            .srcAccessMask = VK_ACCESS_2_SHADER_STORAGE_READ_BIT | VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT,
                            .dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
                            .dstAccessMask = VK_ACCESS_2_TRANSFER_READ_BIT,
                            .oldLayout = VK_IMAGE_LAYOUT_GENERAL,
                            .newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .image = Self.ComputeImage,
                            .subresourceRange = VkImageSubresourceRange{
                                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                .baseMipLevel = 0,
                                .levelCount = 1,
                                .baseArrayLayer = 0,
                                .layerCount = 1
                            }
                        },
                        VkImageMemoryBarrier2{
                            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                            .srcStageMask = VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT,
                            .srcAccessMask = VK_ACCESS_2_NONE,
                            .dstStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
                            .dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
                            .oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                            .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .image = Self.SurfaceImages[Self.SurfaceImageIndex],
                            .subresourceRange = VkImageSubresourceRange{
                                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                .baseMipLevel = 0,
                                .levelCount = 1,
                                .baseArrayLayer = 0,
                                .layerCount = 1
                            }
                        }
                    }
                }}
            );

            Self.DeviceDispatcher->vkCmdBlitImage2(
                Self.CommandBuffers[FrameIndex],
                (VkBlitImageInfo2[]){{
                    .sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2,
                    .pNext = {},
                    .srcImage = Self.ComputeImage,
                    .srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                    .dstImage = Self.SurfaceImages[Self.SurfaceImageIndex],
                    .dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    .regionCount = 1,
                    .pRegions = (VkImageBlit2[]){
                        VkImageBlit2{
                            .sType = VK_STRUCTURE_TYPE_IMAGE_BLIT_2,
                            .pNext = {},
                            .srcSubresource = VkImageSubresourceLayers{
                                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                .mipLevel = 0,
                                .baseArrayLayer = 0,
                                .layerCount = 1
                            },
                            .srcOffsets = {
                                VkOffset3D{
                                    .x = 0,
                                    .y = 0,
                                    .z = 0
                                },
                                VkOffset3D{
                                    .x = i32(Self.SurfaceCapabilities.currentExtent.width),
                                    .y = i32(Self.SurfaceCapabilities.currentExtent.height),
                                    .z = 1
                                },
                            },
                            .dstSubresource = VkImageSubresourceLayers{
                                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                .mipLevel = 0,
                                .baseArrayLayer = 0,
                                .layerCount = 1
                            },
                            .dstOffsets = {
                                VkOffset3D{
                                    .x = 0,
                                    .y = 0,
                                    .z = 0
                                },
                                VkOffset3D{
                                    .x = i32(Self.SurfaceCapabilities.currentExtent.width),
                                    .y = i32(Self.SurfaceCapabilities.currentExtent.height),
                                    .z = 1
                                },
                            }
                        }
                    },
                    .filter = VK_FILTER_NEAREST
                }}
            );
            Self.DeviceDispatcher->vkCmdPipelineBarrier2(
                Self.CommandBuffers[FrameIndex],
                (VkDependencyInfo[]) {{
                    .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
                    .pNext = {},
                    .dependencyFlags = {},
                    .imageMemoryBarrierCount = 1,
                    .pImageMemoryBarriers = (VkImageMemoryBarrier2[]) {
                        VkImageMemoryBarrier2{
                            .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
                            .srcStageMask = VK_PIPELINE_STAGE_2_TRANSFER_BIT,
                            .srcAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT,
                            .dstStageMask = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT,
                            .dstAccessMask = VK_ACCESS_2_NONE,
                            .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                            .newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
                            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                            .image = Self.SurfaceImages[Self.SurfaceImageIndex],
                            .subresourceRange = VkImageSubresourceRange{
                                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                .baseMipLevel = 0,
                                .levelCount = 1,
                                .baseArrayLayer = 0,
                                .layerCount = 1
                            }
                        }
                    }
                }}
            );
            Self.DeviceDispatcher->vkEndCommandBuffer(Self.CommandBuffers[FrameIndex]);
            Self.DeviceDispatcher->vkQueueSubmit2(
                Self.Queue,
                1,
                (VkSubmitInfo2[]){{
                    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
                    .pNext = {},
                    .flags = {},
                    .waitSemaphoreInfoCount = 1,
                    .pWaitSemaphoreInfos = (VkSemaphoreSubmitInfo[]) {
                        VkSemaphoreSubmitInfo{
                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                            .pNext = {},
                            .semaphore = Self.AcquireSemaphores[FrameIndex],
                            .stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                        }
                    },
                    .commandBufferInfoCount = 1,
                    .pCommandBufferInfos = (VkCommandBufferSubmitInfo[]){{
                        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
                        .pNext = {},
                        .commandBuffer = Self.CommandBuffers[FrameIndex],
                        .deviceMask = 0
                    }},
                    .signalSemaphoreInfoCount = 2,
                    .pSignalSemaphoreInfos = (VkSemaphoreSubmitInfo[]) {
                        VkSemaphoreSubmitInfo{
                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                            .pNext = {},
                            .semaphore = Self.SubmitSemaphores[FrameIndex],
                            .stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                        },
                        VkSemaphoreSubmitInfo{
                            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
                            .pNext = {},
                            .semaphore = Self.TimelineSemaphore,
                            .value = TotalFrameIndex + 1,
                            .stageMask = VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT,
                        },
                    }
                }},
                nullptr // Self.Fences[FrameIndex]
            );
            Self.DeviceDispatcher->vkQueuePresentKHR(
                Self.Queue,
                (VkPresentInfoKHR[]) {{
                    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                    .pNext = {},
                    .waitSemaphoreCount = 1,
                    .pWaitSemaphores = (VkSemaphore[]) {
                        Self.SubmitSemaphores[FrameIndex]
                    },
                    .swapchainCount = 1,
                    .pSwapchains = (VkSwapchainKHR[]) {
                        Self.Swapchain
                    },
                    .pImageIndices = (u32[]) {
                        Self.SurfaceImageIndex
                    },
                    .pResults = {}
                }}
            );
            TotalFrameIndex += 1;
            FrameIndex += 1;
            FrameIndex %= MAX_FRAMES_IN_FLIGHT;
        }

        Self.DeviceDispatcher->vkDeviceWaitIdle(Self.LogicalDevice);
    }

    static VKAPI_ATTR auto VKAPI_CALL DebugUtilsCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData, void* pUserData) -> VkBool32 {
        switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: {
            std::println(stdout, "[verbose]: {}", pCallbackData->pMessage);
            break;
        }
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: {
            std::println(stdout, "[info]: {}", pCallbackData->pMessage);
            break;
        }
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: {
            std::println(stdout, "[warning]: {}", pCallbackData->pMessage);
            break;
        }
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: {
            std::println(stderr, "[error]: {}", pCallbackData->pMessage);
            break;
        }
        default: {
            std::unreachable();
        }
        }
        return VK_FALSE;
    }
};

auto main() -> i32 {
    auto* VulkanApplicationInstance = new VulkanApplication();
    VulkanApplicationInstance->StartLoop();
    delete VulkanApplicationInstance;
    return 0;
}
