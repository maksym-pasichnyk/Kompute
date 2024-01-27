//
// Created by Maksym Pasichnyk on 20.10.2023.
//

#pragma once

#define VK_NO_PROTOTYPES
#define VK_ENABLE_BETA_EXTENSIONS
#include "vulkan/vulkan.h"

using PFN_dummy = void ( * )();

class VkContextDispatcher {
public:
    VkContextDispatcher(PFN_vkGetInstanceProcAddr getProcAddr)
        : vkGetInstanceProcAddr(getProcAddr)
        //=== VK_VERSION_1_0 ===
        , vkCreateInstance(PFN_vkCreateInstance(getProcAddr(nullptr, "vkCreateInstance")))
        , vkEnumerateInstanceExtensionProperties(PFN_vkEnumerateInstanceExtensionProperties(getProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties")))
        , vkEnumerateInstanceLayerProperties(PFN_vkEnumerateInstanceLayerProperties(getProcAddr(nullptr, "vkEnumerateInstanceLayerProperties")))
        //=== VK_VERSION_1_1 ===
        , vkEnumerateInstanceVersion(PFN_vkEnumerateInstanceVersion(getProcAddr(nullptr, "vkEnumerateInstanceVersion"))) {
    }
public:
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = nullptr;

    //=== VK_VERSION_1_0 ===
    PFN_vkCreateInstance                       vkCreateInstance                       = nullptr;
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties = nullptr;
    PFN_vkEnumerateInstanceLayerProperties     vkEnumerateInstanceLayerProperties     = nullptr;

    //=== VK_VERSION_1_1 ===
    PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion = nullptr;
};

class VkInstanceDispatcher {
public:
    VkInstanceDispatcher( PFN_vkGetInstanceProcAddr getProcAddr, VkInstance instance ) : vkGetInstanceProcAddr( getProcAddr )
    {
        //=== VK_VERSION_1_0 ===
        vkDestroyInstance           = PFN_vkDestroyInstance( vkGetInstanceProcAddr( instance, "vkDestroyInstance" ) );
        vkEnumeratePhysicalDevices  = PFN_vkEnumeratePhysicalDevices( vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDevices" ) );
        vkGetPhysicalDeviceFeatures = PFN_vkGetPhysicalDeviceFeatures( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFeatures" ) );
        vkGetPhysicalDeviceFormatProperties =
            PFN_vkGetPhysicalDeviceFormatProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFormatProperties" ) );
        vkGetPhysicalDeviceImageFormatProperties =
            PFN_vkGetPhysicalDeviceImageFormatProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceImageFormatProperties" ) );
        vkGetPhysicalDeviceProperties = PFN_vkGetPhysicalDeviceProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceProperties" ) );
        vkGetPhysicalDeviceQueueFamilyProperties =
            PFN_vkGetPhysicalDeviceQueueFamilyProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyProperties" ) );
        vkGetPhysicalDeviceMemoryProperties =
            PFN_vkGetPhysicalDeviceMemoryProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMemoryProperties" ) );
        vkCreateDevice = PFN_vkCreateDevice( vkGetInstanceProcAddr( instance, "vkCreateDevice" ) );
        vkEnumerateDeviceExtensionProperties =
            PFN_vkEnumerateDeviceExtensionProperties( vkGetInstanceProcAddr( instance, "vkEnumerateDeviceExtensionProperties" ) );
        vkEnumerateDeviceLayerProperties = PFN_vkEnumerateDeviceLayerProperties( vkGetInstanceProcAddr( instance, "vkEnumerateDeviceLayerProperties" ) );
        vkGetPhysicalDeviceSparseImageFormatProperties =
            PFN_vkGetPhysicalDeviceSparseImageFormatProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSparseImageFormatProperties" ) );

        //=== VK_VERSION_1_1 ===
        vkEnumeratePhysicalDeviceGroups = PFN_vkEnumeratePhysicalDeviceGroups( vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceGroups" ) );
        vkGetPhysicalDeviceFeatures2    = PFN_vkGetPhysicalDeviceFeatures2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFeatures2" ) );
        vkGetPhysicalDeviceProperties2  = PFN_vkGetPhysicalDeviceProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceProperties2" ) );
        vkGetPhysicalDeviceFormatProperties2 =
            PFN_vkGetPhysicalDeviceFormatProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFormatProperties2" ) );
        vkGetPhysicalDeviceImageFormatProperties2 =
            PFN_vkGetPhysicalDeviceImageFormatProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceImageFormatProperties2" ) );
        vkGetPhysicalDeviceQueueFamilyProperties2 =
            PFN_vkGetPhysicalDeviceQueueFamilyProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyProperties2" ) );
        vkGetPhysicalDeviceMemoryProperties2 =
            PFN_vkGetPhysicalDeviceMemoryProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMemoryProperties2" ) );
        vkGetPhysicalDeviceSparseImageFormatProperties2 =
            PFN_vkGetPhysicalDeviceSparseImageFormatProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSparseImageFormatProperties2" ) );
        vkGetPhysicalDeviceExternalBufferProperties =
            PFN_vkGetPhysicalDeviceExternalBufferProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalBufferProperties" ) );
        vkGetPhysicalDeviceExternalFenceProperties =
            PFN_vkGetPhysicalDeviceExternalFenceProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalFenceProperties" ) );
        vkGetPhysicalDeviceExternalSemaphoreProperties =
            PFN_vkGetPhysicalDeviceExternalSemaphoreProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalSemaphoreProperties" ) );

        //=== VK_VERSION_1_3 ===
        vkGetPhysicalDeviceToolProperties = PFN_vkGetPhysicalDeviceToolProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceToolProperties" ) );

        //=== VK_KHR_surface ===
        vkDestroySurfaceKHR = PFN_vkDestroySurfaceKHR( vkGetInstanceProcAddr( instance, "vkDestroySurfaceKHR" ) );
        vkGetPhysicalDeviceSurfaceSupportKHR =
            PFN_vkGetPhysicalDeviceSurfaceSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceSupportKHR" ) );
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR =
            PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR" ) );
        vkGetPhysicalDeviceSurfaceFormatsKHR =
            PFN_vkGetPhysicalDeviceSurfaceFormatsKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceFormatsKHR" ) );
        vkGetPhysicalDeviceSurfacePresentModesKHR =
            PFN_vkGetPhysicalDeviceSurfacePresentModesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfacePresentModesKHR" ) );

        //=== VK_KHR_swapchain ===
        vkGetPhysicalDevicePresentRectanglesKHR =
            PFN_vkGetPhysicalDevicePresentRectanglesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDevicePresentRectanglesKHR" ) );

        //=== VK_KHR_display ===
        vkGetPhysicalDeviceDisplayPropertiesKHR =
            PFN_vkGetPhysicalDeviceDisplayPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayPropertiesKHR" ) );
        vkGetPhysicalDeviceDisplayPlanePropertiesKHR =
            PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR" ) );
        vkGetDisplayPlaneSupportedDisplaysKHR =
            PFN_vkGetDisplayPlaneSupportedDisplaysKHR( vkGetInstanceProcAddr( instance, "vkGetDisplayPlaneSupportedDisplaysKHR" ) );
        vkGetDisplayModePropertiesKHR    = PFN_vkGetDisplayModePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetDisplayModePropertiesKHR" ) );
        vkCreateDisplayModeKHR           = PFN_vkCreateDisplayModeKHR( vkGetInstanceProcAddr( instance, "vkCreateDisplayModeKHR" ) );
        vkGetDisplayPlaneCapabilitiesKHR = PFN_vkGetDisplayPlaneCapabilitiesKHR( vkGetInstanceProcAddr( instance, "vkGetDisplayPlaneCapabilitiesKHR" ) );
        vkCreateDisplayPlaneSurfaceKHR   = PFN_vkCreateDisplayPlaneSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateDisplayPlaneSurfaceKHR" ) );

#  if defined( VK_USE_PLATFORM_XLIB_KHR )
        //=== VK_KHR_xlib_surface ===
        vkCreateXlibSurfaceKHR = PFN_vkCreateXlibSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateXlibSurfaceKHR" ) );
        vkGetPhysicalDeviceXlibPresentationSupportKHR =
          PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR" ) );
#  endif /*VK_USE_PLATFORM_XLIB_KHR*/

#  if defined( VK_USE_PLATFORM_XCB_KHR )
        //=== VK_KHR_xcb_surface ===
        vkCreateXcbSurfaceKHR = PFN_vkCreateXcbSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateXcbSurfaceKHR" ) );
        vkGetPhysicalDeviceXcbPresentationSupportKHR =
          PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR" ) );
#  endif /*VK_USE_PLATFORM_XCB_KHR*/

#  if defined( VK_USE_PLATFORM_WAYLAND_KHR )
        //=== VK_KHR_wayland_surface ===
        vkCreateWaylandSurfaceKHR = PFN_vkCreateWaylandSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateWaylandSurfaceKHR" ) );
        vkGetPhysicalDeviceWaylandPresentationSupportKHR =
          PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR" ) );
#  endif /*VK_USE_PLATFORM_WAYLAND_KHR*/

#  if defined( VK_USE_PLATFORM_ANDROID_KHR )
        //=== VK_KHR_android_surface ===
        vkCreateAndroidSurfaceKHR = PFN_vkCreateAndroidSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateAndroidSurfaceKHR" ) );
#  endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_win32_surface ===
        vkCreateWin32SurfaceKHR = PFN_vkCreateWin32SurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateWin32SurfaceKHR" ) );
        vkGetPhysicalDeviceWin32PresentationSupportKHR =
          PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_EXT_debug_report ===
        vkCreateDebugReportCallbackEXT  = PFN_vkCreateDebugReportCallbackEXT( vkGetInstanceProcAddr( instance, "vkCreateDebugReportCallbackEXT" ) );
        vkDestroyDebugReportCallbackEXT = PFN_vkDestroyDebugReportCallbackEXT( vkGetInstanceProcAddr( instance, "vkDestroyDebugReportCallbackEXT" ) );
        vkDebugReportMessageEXT         = PFN_vkDebugReportMessageEXT( vkGetInstanceProcAddr( instance, "vkDebugReportMessageEXT" ) );

        //=== VK_KHR_video_queue ===
        vkGetPhysicalDeviceVideoCapabilitiesKHR =
            PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceVideoCapabilitiesKHR" ) );
        vkGetPhysicalDeviceVideoFormatPropertiesKHR =
            PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceVideoFormatPropertiesKHR" ) );

#  if defined( VK_USE_PLATFORM_GGP )
        //=== VK_GGP_stream_descriptor_surface ===
        vkCreateStreamDescriptorSurfaceGGP = PFN_vkCreateStreamDescriptorSurfaceGGP( vkGetInstanceProcAddr( instance, "vkCreateStreamDescriptorSurfaceGGP" ) );
#  endif /*VK_USE_PLATFORM_GGP*/

        //=== VK_NV_external_memory_capabilities ===
        vkGetPhysicalDeviceExternalImageFormatPropertiesNV =
            PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV" ) );

        //=== VK_KHR_get_physical_device_properties2 ===
        vkGetPhysicalDeviceFeatures2KHR = PFN_vkGetPhysicalDeviceFeatures2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFeatures2KHR" ) );
        if ( !vkGetPhysicalDeviceFeatures2 )
            vkGetPhysicalDeviceFeatures2 = vkGetPhysicalDeviceFeatures2KHR;
        vkGetPhysicalDeviceProperties2KHR = PFN_vkGetPhysicalDeviceProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceProperties2 )
            vkGetPhysicalDeviceProperties2 = vkGetPhysicalDeviceProperties2KHR;
        vkGetPhysicalDeviceFormatProperties2KHR =
            PFN_vkGetPhysicalDeviceFormatProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFormatProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceFormatProperties2 )
            vkGetPhysicalDeviceFormatProperties2 = vkGetPhysicalDeviceFormatProperties2KHR;
        vkGetPhysicalDeviceImageFormatProperties2KHR =
            PFN_vkGetPhysicalDeviceImageFormatProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceImageFormatProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceImageFormatProperties2 )
            vkGetPhysicalDeviceImageFormatProperties2 = vkGetPhysicalDeviceImageFormatProperties2KHR;
        vkGetPhysicalDeviceQueueFamilyProperties2KHR =
            PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceQueueFamilyProperties2 )
            vkGetPhysicalDeviceQueueFamilyProperties2 = vkGetPhysicalDeviceQueueFamilyProperties2KHR;
        vkGetPhysicalDeviceMemoryProperties2KHR =
            PFN_vkGetPhysicalDeviceMemoryProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMemoryProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceMemoryProperties2 )
            vkGetPhysicalDeviceMemoryProperties2 = vkGetPhysicalDeviceMemoryProperties2KHR;
        vkGetPhysicalDeviceSparseImageFormatProperties2KHR =
            PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceSparseImageFormatProperties2 )
            vkGetPhysicalDeviceSparseImageFormatProperties2 = vkGetPhysicalDeviceSparseImageFormatProperties2KHR;

#  if defined( VK_USE_PLATFORM_VI_NN )
        //=== VK_NN_vi_surface ===
        vkCreateViSurfaceNN = PFN_vkCreateViSurfaceNN( vkGetInstanceProcAddr( instance, "vkCreateViSurfaceNN" ) );
#  endif /*VK_USE_PLATFORM_VI_NN*/

        //=== VK_KHR_device_group_creation ===
        vkEnumeratePhysicalDeviceGroupsKHR = PFN_vkEnumeratePhysicalDeviceGroupsKHR( vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceGroupsKHR" ) );
        if ( !vkEnumeratePhysicalDeviceGroups )
            vkEnumeratePhysicalDeviceGroups = vkEnumeratePhysicalDeviceGroupsKHR;

        //=== VK_KHR_external_memory_capabilities ===
        vkGetPhysicalDeviceExternalBufferPropertiesKHR =
            PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalBufferPropertiesKHR" ) );
        if ( !vkGetPhysicalDeviceExternalBufferProperties )
            vkGetPhysicalDeviceExternalBufferProperties = vkGetPhysicalDeviceExternalBufferPropertiesKHR;

        //=== VK_KHR_external_semaphore_capabilities ===
        vkGetPhysicalDeviceExternalSemaphorePropertiesKHR =
            PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR" ) );
        if ( !vkGetPhysicalDeviceExternalSemaphoreProperties )
            vkGetPhysicalDeviceExternalSemaphoreProperties = vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;

        //=== VK_EXT_direct_mode_display ===
        vkReleaseDisplayEXT = PFN_vkReleaseDisplayEXT( vkGetInstanceProcAddr( instance, "vkReleaseDisplayEXT" ) );

#  if defined( VK_USE_PLATFORM_XLIB_XRANDR_EXT )
        //=== VK_EXT_acquire_xlib_display ===
        vkAcquireXlibDisplayEXT    = PFN_vkAcquireXlibDisplayEXT( vkGetInstanceProcAddr( instance, "vkAcquireXlibDisplayEXT" ) );
        vkGetRandROutputDisplayEXT = PFN_vkGetRandROutputDisplayEXT( vkGetInstanceProcAddr( instance, "vkGetRandROutputDisplayEXT" ) );
#  endif /*VK_USE_PLATFORM_XLIB_XRANDR_EXT*/

        //=== VK_EXT_display_surface_counter ===
        vkGetPhysicalDeviceSurfaceCapabilities2EXT =
            PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT" ) );

        //=== VK_KHR_external_fence_capabilities ===
        vkGetPhysicalDeviceExternalFencePropertiesKHR =
            PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalFencePropertiesKHR" ) );
        if ( !vkGetPhysicalDeviceExternalFenceProperties )
            vkGetPhysicalDeviceExternalFenceProperties = vkGetPhysicalDeviceExternalFencePropertiesKHR;

        //=== VK_KHR_performance_query ===
        vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
            vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR" ) );
        vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
            vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR" ) );

        //=== VK_KHR_get_surface_capabilities2 ===
        vkGetPhysicalDeviceSurfaceCapabilities2KHR =
            PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR" ) );
        vkGetPhysicalDeviceSurfaceFormats2KHR =
            PFN_vkGetPhysicalDeviceSurfaceFormats2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceFormats2KHR" ) );

        //=== VK_KHR_get_display_properties2 ===
        vkGetPhysicalDeviceDisplayProperties2KHR =
            PFN_vkGetPhysicalDeviceDisplayProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayProperties2KHR" ) );
        vkGetPhysicalDeviceDisplayPlaneProperties2KHR =
            PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR" ) );
        vkGetDisplayModeProperties2KHR    = PFN_vkGetDisplayModeProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetDisplayModeProperties2KHR" ) );
        vkGetDisplayPlaneCapabilities2KHR = PFN_vkGetDisplayPlaneCapabilities2KHR( vkGetInstanceProcAddr( instance, "vkGetDisplayPlaneCapabilities2KHR" ) );

#  if defined( VK_USE_PLATFORM_IOS_MVK )
        //=== VK_MVK_ios_surface ===
        vkCreateIOSSurfaceMVK = PFN_vkCreateIOSSurfaceMVK( vkGetInstanceProcAddr( instance, "vkCreateIOSSurfaceMVK" ) );
#  endif /*VK_USE_PLATFORM_IOS_MVK*/

#  if defined( VK_USE_PLATFORM_MACOS_MVK )
        //=== VK_MVK_macos_surface ===
        vkCreateMacOSSurfaceMVK = PFN_vkCreateMacOSSurfaceMVK( vkGetInstanceProcAddr( instance, "vkCreateMacOSSurfaceMVK" ) );
#  endif /*VK_USE_PLATFORM_MACOS_MVK*/

        //=== VK_EXT_debug_utils ===
        vkCreateDebugUtilsMessengerEXT  = PFN_vkCreateDebugUtilsMessengerEXT( vkGetInstanceProcAddr( instance, "vkCreateDebugUtilsMessengerEXT" ) );
        vkDestroyDebugUtilsMessengerEXT = PFN_vkDestroyDebugUtilsMessengerEXT( vkGetInstanceProcAddr( instance, "vkDestroyDebugUtilsMessengerEXT" ) );
        vkSubmitDebugUtilsMessageEXT    = PFN_vkSubmitDebugUtilsMessageEXT( vkGetInstanceProcAddr( instance, "vkSubmitDebugUtilsMessageEXT" ) );

        //=== VK_EXT_sample_locations ===
        vkGetPhysicalDeviceMultisamplePropertiesEXT =
            PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT" ) );

        //=== VK_EXT_calibrated_timestamps ===
        vkGetPhysicalDeviceCalibrateableTimeDomainsEXT =
            PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT" ) );

#  if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_imagepipe_surface ===
        vkCreateImagePipeSurfaceFUCHSIA = PFN_vkCreateImagePipeSurfaceFUCHSIA( vkGetInstanceProcAddr( instance, "vkCreateImagePipeSurfaceFUCHSIA" ) );
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

#  if defined( VK_USE_PLATFORM_METAL_EXT )
        //=== VK_EXT_metal_surface ===
        vkCreateMetalSurfaceEXT = PFN_vkCreateMetalSurfaceEXT( vkGetInstanceProcAddr( instance, "vkCreateMetalSurfaceEXT" ) );
#  endif /*VK_USE_PLATFORM_METAL_EXT*/

        //=== VK_KHR_fragment_shading_rate ===
        vkGetPhysicalDeviceFragmentShadingRatesKHR =
            PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR" ) );

        //=== VK_EXT_tooling_info ===
        vkGetPhysicalDeviceToolPropertiesEXT =
            PFN_vkGetPhysicalDeviceToolPropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceToolPropertiesEXT" ) );
        if ( !vkGetPhysicalDeviceToolProperties )
            vkGetPhysicalDeviceToolProperties = vkGetPhysicalDeviceToolPropertiesEXT;

        //=== VK_NV_cooperative_matrix ===
        vkGetPhysicalDeviceCooperativeMatrixPropertiesNV =
            PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV" ) );

        //=== VK_NV_coverage_reduction_mode ===
        vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
            vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV" ) );

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_EXT_full_screen_exclusive ===
        vkGetPhysicalDeviceSurfacePresentModes2EXT =
          PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_EXT_headless_surface ===
        vkCreateHeadlessSurfaceEXT = PFN_vkCreateHeadlessSurfaceEXT( vkGetInstanceProcAddr( instance, "vkCreateHeadlessSurfaceEXT" ) );

        //=== VK_EXT_acquire_drm_display ===
        vkAcquireDrmDisplayEXT = PFN_vkAcquireDrmDisplayEXT( vkGetInstanceProcAddr( instance, "vkAcquireDrmDisplayEXT" ) );
        vkGetDrmDisplayEXT     = PFN_vkGetDrmDisplayEXT( vkGetInstanceProcAddr( instance, "vkGetDrmDisplayEXT" ) );

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
        //=== VK_KHR_video_encode_queue ===
        vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
            vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR" ) );
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_NV_acquire_winrt_display ===
        vkAcquireWinrtDisplayNV = PFN_vkAcquireWinrtDisplayNV( vkGetInstanceProcAddr( instance, "vkAcquireWinrtDisplayNV" ) );
        vkGetWinrtDisplayNV     = PFN_vkGetWinrtDisplayNV( vkGetInstanceProcAddr( instance, "vkGetWinrtDisplayNV" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

#  if defined( VK_USE_PLATFORM_DIRECTFB_EXT )
        //=== VK_EXT_directfb_surface ===
        vkCreateDirectFBSurfaceEXT = PFN_vkCreateDirectFBSurfaceEXT( vkGetInstanceProcAddr( instance, "vkCreateDirectFBSurfaceEXT" ) );
        vkGetPhysicalDeviceDirectFBPresentationSupportEXT =
          PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT" ) );
#  endif /*VK_USE_PLATFORM_DIRECTFB_EXT*/

#  if defined( VK_USE_PLATFORM_SCREEN_QNX )
        //=== VK_QNX_screen_surface ===
        vkCreateScreenSurfaceQNX = PFN_vkCreateScreenSurfaceQNX( vkGetInstanceProcAddr( instance, "vkCreateScreenSurfaceQNX" ) );
        vkGetPhysicalDeviceScreenPresentationSupportQNX =
          PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceScreenPresentationSupportQNX" ) );
#  endif /*VK_USE_PLATFORM_SCREEN_QNX*/

        //=== VK_NV_optical_flow ===
        vkGetPhysicalDeviceOpticalFlowImageFormatsNV =
            PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV" ) );

        //=== VK_KHR_cooperative_matrix ===
        vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR =
            PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR" ) );

        vkGetDeviceProcAddr = PFN_vkGetDeviceProcAddr( vkGetInstanceProcAddr( instance, "vkGetDeviceProcAddr" ) );
    }

public:
    //=== VK_VERSION_1_0 ===
    PFN_vkDestroyInstance                              vkDestroyInstance                              = nullptr;
    PFN_vkEnumeratePhysicalDevices                     vkEnumeratePhysicalDevices                     = nullptr;
    PFN_vkGetPhysicalDeviceFeatures                    vkGetPhysicalDeviceFeatures                    = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties            vkGetPhysicalDeviceFormatProperties            = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties       vkGetPhysicalDeviceImageFormatProperties       = nullptr;
    PFN_vkGetPhysicalDeviceProperties                  vkGetPhysicalDeviceProperties                  = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties       vkGetPhysicalDeviceQueueFamilyProperties       = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties            vkGetPhysicalDeviceMemoryProperties            = nullptr;
    PFN_vkGetInstanceProcAddr                          vkGetInstanceProcAddr                          = nullptr;
    PFN_vkCreateDevice                                 vkCreateDevice                                 = nullptr;
    PFN_vkEnumerateDeviceExtensionProperties           vkEnumerateDeviceExtensionProperties           = nullptr;
    PFN_vkEnumerateDeviceLayerProperties               vkEnumerateDeviceLayerProperties               = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties = nullptr;

    //=== VK_VERSION_1_1 ===
    PFN_vkEnumeratePhysicalDeviceGroups                 vkEnumeratePhysicalDeviceGroups                 = nullptr;
    PFN_vkGetPhysicalDeviceFeatures2                    vkGetPhysicalDeviceFeatures2                    = nullptr;
    PFN_vkGetPhysicalDeviceProperties2                  vkGetPhysicalDeviceProperties2                  = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties2            vkGetPhysicalDeviceFormatProperties2            = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties2       vkGetPhysicalDeviceImageFormatProperties2       = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2       vkGetPhysicalDeviceQueueFamilyProperties2       = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties2            vkGetPhysicalDeviceMemoryProperties2            = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
    PFN_vkGetPhysicalDeviceExternalBufferProperties     vkGetPhysicalDeviceExternalBufferProperties     = nullptr;
    PFN_vkGetPhysicalDeviceExternalFenceProperties      vkGetPhysicalDeviceExternalFenceProperties      = nullptr;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties  vkGetPhysicalDeviceExternalSemaphoreProperties  = nullptr;

    //=== VK_VERSION_1_3 ===
    PFN_vkGetPhysicalDeviceToolProperties vkGetPhysicalDeviceToolProperties = nullptr;

    //=== VK_KHR_surface ===
    PFN_vkDestroySurfaceKHR                       vkDestroySurfaceKHR                       = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR      vkGetPhysicalDeviceSurfaceSupportKHR      = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR      vkGetPhysicalDeviceSurfaceFormatsKHR      = nullptr;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR = nullptr;

    //=== VK_KHR_swapchain ===
    PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR = nullptr;

    //=== VK_KHR_display ===
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR      vkGetPhysicalDeviceDisplayPropertiesKHR      = nullptr;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR = nullptr;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR        vkGetDisplayPlaneSupportedDisplaysKHR        = nullptr;
    PFN_vkGetDisplayModePropertiesKHR                vkGetDisplayModePropertiesKHR                = nullptr;
    PFN_vkCreateDisplayModeKHR                       vkCreateDisplayModeKHR                       = nullptr;
    PFN_vkGetDisplayPlaneCapabilitiesKHR             vkGetDisplayPlaneCapabilitiesKHR             = nullptr;
    PFN_vkCreateDisplayPlaneSurfaceKHR               vkCreateDisplayPlaneSurfaceKHR               = nullptr;

#  if defined( VK_USE_PLATFORM_XLIB_KHR )
    //=== VK_KHR_xlib_surface ===
      PFN_vkCreateXlibSurfaceKHR                        vkCreateXlibSurfaceKHR                        = nullptr;
      PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR = nullptr;
#  else
    PFN_dummy vkCreateXlibSurfaceKHR_placeholder                                  = nullptr;
    PFN_dummy vkGetPhysicalDeviceXlibPresentationSupportKHR_placeholder           = nullptr;
#  endif /*VK_USE_PLATFORM_XLIB_KHR*/

#  if defined( VK_USE_PLATFORM_XCB_KHR )
    //=== VK_KHR_xcb_surface ===
      PFN_vkCreateXcbSurfaceKHR                        vkCreateXcbSurfaceKHR                        = nullptr;
      PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR = nullptr;
#  else
    PFN_dummy vkCreateXcbSurfaceKHR_placeholder                                   = nullptr;
    PFN_dummy vkGetPhysicalDeviceXcbPresentationSupportKHR_placeholder            = nullptr;
#  endif /*VK_USE_PLATFORM_XCB_KHR*/

#  if defined( VK_USE_PLATFORM_WAYLAND_KHR )
    //=== VK_KHR_wayland_surface ===
      PFN_vkCreateWaylandSurfaceKHR                        vkCreateWaylandSurfaceKHR                        = nullptr;
      PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR = nullptr;
#  else
    PFN_dummy vkCreateWaylandSurfaceKHR_placeholder                               = nullptr;
    PFN_dummy vkGetPhysicalDeviceWaylandPresentationSupportKHR_placeholder        = nullptr;
#  endif /*VK_USE_PLATFORM_WAYLAND_KHR*/

#  if defined( VK_USE_PLATFORM_ANDROID_KHR )
    //=== VK_KHR_android_surface ===
      PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR = nullptr;
#  else
    PFN_dummy vkCreateAndroidSurfaceKHR_placeholder                               = nullptr;
#  endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_KHR_win32_surface ===
      PFN_vkCreateWin32SurfaceKHR                        vkCreateWin32SurfaceKHR                        = nullptr;
      PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR = nullptr;
#  else
    PFN_dummy vkCreateWin32SurfaceKHR_placeholder                                 = nullptr;
    PFN_dummy vkGetPhysicalDeviceWin32PresentationSupportKHR_placeholder          = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

    //=== VK_EXT_debug_report ===
    PFN_vkCreateDebugReportCallbackEXT  vkCreateDebugReportCallbackEXT  = nullptr;
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = nullptr;
    PFN_vkDebugReportMessageEXT         vkDebugReportMessageEXT         = nullptr;

    //=== VK_KHR_video_queue ===
    PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR     vkGetPhysicalDeviceVideoCapabilitiesKHR     = nullptr;
    PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR vkGetPhysicalDeviceVideoFormatPropertiesKHR = nullptr;

#  if defined( VK_USE_PLATFORM_GGP )
    //=== VK_GGP_stream_descriptor_surface ===
      PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP = nullptr;
#  else
    PFN_dummy vkCreateStreamDescriptorSurfaceGGP_placeholder                      = nullptr;
#  endif /*VK_USE_PLATFORM_GGP*/

    //=== VK_NV_external_memory_capabilities ===
    PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV = nullptr;

    //=== VK_KHR_get_physical_device_properties2 ===
    PFN_vkGetPhysicalDeviceFeatures2KHR                    vkGetPhysicalDeviceFeatures2KHR                    = nullptr;
    PFN_vkGetPhysicalDeviceProperties2KHR                  vkGetPhysicalDeviceProperties2KHR                  = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties2KHR            vkGetPhysicalDeviceFormatProperties2KHR            = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties2KHR       vkGetPhysicalDeviceImageFormatProperties2KHR       = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR       vkGetPhysicalDeviceQueueFamilyProperties2KHR       = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties2KHR            vkGetPhysicalDeviceMemoryProperties2KHR            = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR = nullptr;

#  if defined( VK_USE_PLATFORM_VI_NN )
    //=== VK_NN_vi_surface ===
      PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN = nullptr;
#  else
    PFN_dummy vkCreateViSurfaceNN_placeholder                                     = nullptr;
#  endif /*VK_USE_PLATFORM_VI_NN*/

    //=== VK_KHR_device_group_creation ===
    PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR = nullptr;

    //=== VK_KHR_external_memory_capabilities ===
    PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR = nullptr;

    //=== VK_KHR_external_semaphore_capabilities ===
    PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = nullptr;

    //=== VK_EXT_direct_mode_display ===
    PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT = nullptr;

#  if defined( VK_USE_PLATFORM_XLIB_XRANDR_EXT )
    //=== VK_EXT_acquire_xlib_display ===
      PFN_vkAcquireXlibDisplayEXT    vkAcquireXlibDisplayEXT    = nullptr;
      PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT = nullptr;
#  else
    PFN_dummy vkAcquireXlibDisplayEXT_placeholder                                 = nullptr;
    PFN_dummy vkGetRandROutputDisplayEXT_placeholder                              = nullptr;
#  endif /*VK_USE_PLATFORM_XLIB_XRANDR_EXT*/

    //=== VK_EXT_display_surface_counter ===
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT = nullptr;

    //=== VK_KHR_external_fence_capabilities ===
    PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR = nullptr;

    //=== VK_KHR_performance_query ===
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR         vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR         = nullptr;

    //=== VK_KHR_get_surface_capabilities2 ===
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR      vkGetPhysicalDeviceSurfaceFormats2KHR      = nullptr;

    //=== VK_KHR_get_display_properties2 ===
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR      vkGetPhysicalDeviceDisplayProperties2KHR      = nullptr;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR = nullptr;
    PFN_vkGetDisplayModeProperties2KHR                vkGetDisplayModeProperties2KHR                = nullptr;
    PFN_vkGetDisplayPlaneCapabilities2KHR             vkGetDisplayPlaneCapabilities2KHR             = nullptr;

#  if defined( VK_USE_PLATFORM_IOS_MVK )
    //=== VK_MVK_ios_surface ===
      PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK = nullptr;
#  else
    PFN_dummy vkCreateIOSSurfaceMVK_placeholder                                   = nullptr;
#  endif /*VK_USE_PLATFORM_IOS_MVK*/

#  if defined( VK_USE_PLATFORM_MACOS_MVK )
    //=== VK_MVK_macos_surface ===
      PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK = nullptr;
#  else
    PFN_dummy vkCreateMacOSSurfaceMVK_placeholder                                 = nullptr;
#  endif /*VK_USE_PLATFORM_MACOS_MVK*/

    //=== VK_EXT_debug_utils ===
    PFN_vkCreateDebugUtilsMessengerEXT  vkCreateDebugUtilsMessengerEXT  = nullptr;
    PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = nullptr;
    PFN_vkSubmitDebugUtilsMessageEXT    vkSubmitDebugUtilsMessageEXT    = nullptr;

    //=== VK_EXT_sample_locations ===
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT = nullptr;

    //=== VK_EXT_calibrated_timestamps ===
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = nullptr;

#  if defined( VK_USE_PLATFORM_FUCHSIA )
    //=== VK_FUCHSIA_imagepipe_surface ===
      PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA = nullptr;
#  else
    PFN_dummy vkCreateImagePipeSurfaceFUCHSIA_placeholder                         = nullptr;
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

#  if defined( VK_USE_PLATFORM_METAL_EXT )
    //=== VK_EXT_metal_surface ===
      PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT = nullptr;
#  else
    PFN_dummy vkCreateMetalSurfaceEXT_placeholder                                 = nullptr;
#  endif /*VK_USE_PLATFORM_METAL_EXT*/

    //=== VK_KHR_fragment_shading_rate ===
    PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR = nullptr;

    //=== VK_EXT_tooling_info ===
    PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT = nullptr;

    //=== VK_NV_cooperative_matrix ===
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = nullptr;

    //=== VK_NV_coverage_reduction_mode ===
    PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = nullptr;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_EXT_full_screen_exclusive ===
      PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT = nullptr;
#  else
    PFN_dummy vkGetPhysicalDeviceSurfacePresentModes2EXT_placeholder              = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

    //=== VK_EXT_headless_surface ===
    PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT = nullptr;

    //=== VK_EXT_acquire_drm_display ===
    PFN_vkAcquireDrmDisplayEXT vkAcquireDrmDisplayEXT = nullptr;
    PFN_vkGetDrmDisplayEXT     vkGetDrmDisplayEXT     = nullptr;

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
    //=== VK_KHR_video_encode_queue ===
    PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = nullptr;
#  else
    PFN_dummy vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR_placeholder = nullptr;
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_NV_acquire_winrt_display ===
      PFN_vkAcquireWinrtDisplayNV vkAcquireWinrtDisplayNV = nullptr;
      PFN_vkGetWinrtDisplayNV     vkGetWinrtDisplayNV     = nullptr;
#  else
    PFN_dummy vkAcquireWinrtDisplayNV_placeholder                                 = nullptr;
    PFN_dummy vkGetWinrtDisplayNV_placeholder                                     = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

#  if defined( VK_USE_PLATFORM_DIRECTFB_EXT )
    //=== VK_EXT_directfb_surface ===
      PFN_vkCreateDirectFBSurfaceEXT                        vkCreateDirectFBSurfaceEXT                        = nullptr;
      PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT = nullptr;
#  else
    PFN_dummy vkCreateDirectFBSurfaceEXT_placeholder                              = nullptr;
    PFN_dummy vkGetPhysicalDeviceDirectFBPresentationSupportEXT_placeholder       = nullptr;
#  endif /*VK_USE_PLATFORM_DIRECTFB_EXT*/

#  if defined( VK_USE_PLATFORM_SCREEN_QNX )
    //=== VK_QNX_screen_surface ===
      PFN_vkCreateScreenSurfaceQNX                        vkCreateScreenSurfaceQNX                        = nullptr;
      PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX = nullptr;
#  else
    PFN_dummy vkCreateScreenSurfaceQNX_placeholder                                = nullptr;
    PFN_dummy vkGetPhysicalDeviceScreenPresentationSupportQNX_placeholder         = nullptr;
#  endif /*VK_USE_PLATFORM_SCREEN_QNX*/

    //=== VK_NV_optical_flow ===
    PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV vkGetPhysicalDeviceOpticalFlowImageFormatsNV = nullptr;

    //=== VK_KHR_cooperative_matrix ===
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = nullptr;

    PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr = nullptr;
};

class VkDeviceDispatcher
{
public:
    VkDeviceDispatcher( PFN_vkGetDeviceProcAddr getProcAddr, VkDevice device ) : vkGetDeviceProcAddr( getProcAddr )
    {
        //=== VK_VERSION_1_0 ===
        vkGetDeviceProcAddr                = PFN_vkGetDeviceProcAddr( vkGetDeviceProcAddr( device, "vkGetDeviceProcAddr" ) );
        vkDestroyDevice                    = PFN_vkDestroyDevice( vkGetDeviceProcAddr( device, "vkDestroyDevice" ) );
        vkGetDeviceQueue                   = PFN_vkGetDeviceQueue( vkGetDeviceProcAddr( device, "vkGetDeviceQueue" ) );
        vkQueueSubmit                      = PFN_vkQueueSubmit( vkGetDeviceProcAddr( device, "vkQueueSubmit" ) );
        vkQueueWaitIdle                    = PFN_vkQueueWaitIdle( vkGetDeviceProcAddr( device, "vkQueueWaitIdle" ) );
        vkDeviceWaitIdle                   = PFN_vkDeviceWaitIdle( vkGetDeviceProcAddr( device, "vkDeviceWaitIdle" ) );
        vkAllocateMemory                   = PFN_vkAllocateMemory( vkGetDeviceProcAddr( device, "vkAllocateMemory" ) );
        vkFreeMemory                       = PFN_vkFreeMemory( vkGetDeviceProcAddr( device, "vkFreeMemory" ) );
        vkMapMemory                        = PFN_vkMapMemory( vkGetDeviceProcAddr( device, "vkMapMemory" ) );
        vkUnmapMemory                      = PFN_vkUnmapMemory( vkGetDeviceProcAddr( device, "vkUnmapMemory" ) );
        vkFlushMappedMemoryRanges          = PFN_vkFlushMappedMemoryRanges( vkGetDeviceProcAddr( device, "vkFlushMappedMemoryRanges" ) );
        vkInvalidateMappedMemoryRanges     = PFN_vkInvalidateMappedMemoryRanges( vkGetDeviceProcAddr( device, "vkInvalidateMappedMemoryRanges" ) );
        vkGetDeviceMemoryCommitment        = PFN_vkGetDeviceMemoryCommitment( vkGetDeviceProcAddr( device, "vkGetDeviceMemoryCommitment" ) );
        vkBindBufferMemory                 = PFN_vkBindBufferMemory( vkGetDeviceProcAddr( device, "vkBindBufferMemory" ) );
        vkBindImageMemory                  = PFN_vkBindImageMemory( vkGetDeviceProcAddr( device, "vkBindImageMemory" ) );
        vkGetBufferMemoryRequirements      = PFN_vkGetBufferMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetBufferMemoryRequirements" ) );
        vkGetImageMemoryRequirements       = PFN_vkGetImageMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetImageMemoryRequirements" ) );
        vkGetImageSparseMemoryRequirements = PFN_vkGetImageSparseMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetImageSparseMemoryRequirements" ) );
        vkQueueBindSparse                  = PFN_vkQueueBindSparse( vkGetDeviceProcAddr( device, "vkQueueBindSparse" ) );
        vkCreateFence                      = PFN_vkCreateFence( vkGetDeviceProcAddr( device, "vkCreateFence" ) );
        vkDestroyFence                     = PFN_vkDestroyFence( vkGetDeviceProcAddr( device, "vkDestroyFence" ) );
        vkResetFences                      = PFN_vkResetFences( vkGetDeviceProcAddr( device, "vkResetFences" ) );
        vkGetFenceStatus                   = PFN_vkGetFenceStatus( vkGetDeviceProcAddr( device, "vkGetFenceStatus" ) );
        vkWaitForFences                    = PFN_vkWaitForFences( vkGetDeviceProcAddr( device, "vkWaitForFences" ) );
        vkCreateSemaphore                  = PFN_vkCreateSemaphore( vkGetDeviceProcAddr( device, "vkCreateSemaphore" ) );
        vkDestroySemaphore                 = PFN_vkDestroySemaphore( vkGetDeviceProcAddr( device, "vkDestroySemaphore" ) );
        vkCreateEvent                      = PFN_vkCreateEvent( vkGetDeviceProcAddr( device, "vkCreateEvent" ) );
        vkDestroyEvent                     = PFN_vkDestroyEvent( vkGetDeviceProcAddr( device, "vkDestroyEvent" ) );
        vkGetEventStatus                   = PFN_vkGetEventStatus( vkGetDeviceProcAddr( device, "vkGetEventStatus" ) );
        vkSetEvent                         = PFN_vkSetEvent( vkGetDeviceProcAddr( device, "vkSetEvent" ) );
        vkResetEvent                       = PFN_vkResetEvent( vkGetDeviceProcAddr( device, "vkResetEvent" ) );
        vkCreateQueryPool                  = PFN_vkCreateQueryPool( vkGetDeviceProcAddr( device, "vkCreateQueryPool" ) );
        vkDestroyQueryPool                 = PFN_vkDestroyQueryPool( vkGetDeviceProcAddr( device, "vkDestroyQueryPool" ) );
        vkGetQueryPoolResults              = PFN_vkGetQueryPoolResults( vkGetDeviceProcAddr( device, "vkGetQueryPoolResults" ) );
        vkCreateBuffer                     = PFN_vkCreateBuffer( vkGetDeviceProcAddr( device, "vkCreateBuffer" ) );
        vkDestroyBuffer                    = PFN_vkDestroyBuffer( vkGetDeviceProcAddr( device, "vkDestroyBuffer" ) );
        vkCreateBufferView                 = PFN_vkCreateBufferView( vkGetDeviceProcAddr( device, "vkCreateBufferView" ) );
        vkDestroyBufferView                = PFN_vkDestroyBufferView( vkGetDeviceProcAddr( device, "vkDestroyBufferView" ) );
        vkCreateImage                      = PFN_vkCreateImage( vkGetDeviceProcAddr( device, "vkCreateImage" ) );
        vkDestroyImage                     = PFN_vkDestroyImage( vkGetDeviceProcAddr( device, "vkDestroyImage" ) );
        vkGetImageSubresourceLayout        = PFN_vkGetImageSubresourceLayout( vkGetDeviceProcAddr( device, "vkGetImageSubresourceLayout" ) );
        vkCreateImageView                  = PFN_vkCreateImageView( vkGetDeviceProcAddr( device, "vkCreateImageView" ) );
        vkDestroyImageView                 = PFN_vkDestroyImageView( vkGetDeviceProcAddr( device, "vkDestroyImageView" ) );
        vkCreateShaderModule               = PFN_vkCreateShaderModule( vkGetDeviceProcAddr( device, "vkCreateShaderModule" ) );
        vkDestroyShaderModule              = PFN_vkDestroyShaderModule( vkGetDeviceProcAddr( device, "vkDestroyShaderModule" ) );
        vkCreatePipelineCache              = PFN_vkCreatePipelineCache( vkGetDeviceProcAddr( device, "vkCreatePipelineCache" ) );
        vkDestroyPipelineCache             = PFN_vkDestroyPipelineCache( vkGetDeviceProcAddr( device, "vkDestroyPipelineCache" ) );
        vkGetPipelineCacheData             = PFN_vkGetPipelineCacheData( vkGetDeviceProcAddr( device, "vkGetPipelineCacheData" ) );
        vkMergePipelineCaches              = PFN_vkMergePipelineCaches( vkGetDeviceProcAddr( device, "vkMergePipelineCaches" ) );
        vkCreateGraphicsPipelines          = PFN_vkCreateGraphicsPipelines( vkGetDeviceProcAddr( device, "vkCreateGraphicsPipelines" ) );
        vkCreateComputePipelines           = PFN_vkCreateComputePipelines( vkGetDeviceProcAddr( device, "vkCreateComputePipelines" ) );
        vkDestroyPipeline                  = PFN_vkDestroyPipeline( vkGetDeviceProcAddr( device, "vkDestroyPipeline" ) );
        vkCreatePipelineLayout             = PFN_vkCreatePipelineLayout( vkGetDeviceProcAddr( device, "vkCreatePipelineLayout" ) );
        vkDestroyPipelineLayout            = PFN_vkDestroyPipelineLayout( vkGetDeviceProcAddr( device, "vkDestroyPipelineLayout" ) );
        vkCreateSampler                    = PFN_vkCreateSampler( vkGetDeviceProcAddr( device, "vkCreateSampler" ) );
        vkDestroySampler                   = PFN_vkDestroySampler( vkGetDeviceProcAddr( device, "vkDestroySampler" ) );
        vkCreateDescriptorSetLayout        = PFN_vkCreateDescriptorSetLayout( vkGetDeviceProcAddr( device, "vkCreateDescriptorSetLayout" ) );
        vkDestroyDescriptorSetLayout       = PFN_vkDestroyDescriptorSetLayout( vkGetDeviceProcAddr( device, "vkDestroyDescriptorSetLayout" ) );
        vkCreateDescriptorPool             = PFN_vkCreateDescriptorPool( vkGetDeviceProcAddr( device, "vkCreateDescriptorPool" ) );
        vkDestroyDescriptorPool            = PFN_vkDestroyDescriptorPool( vkGetDeviceProcAddr( device, "vkDestroyDescriptorPool" ) );
        vkResetDescriptorPool              = PFN_vkResetDescriptorPool( vkGetDeviceProcAddr( device, "vkResetDescriptorPool" ) );
        vkAllocateDescriptorSets           = PFN_vkAllocateDescriptorSets( vkGetDeviceProcAddr( device, "vkAllocateDescriptorSets" ) );
        vkFreeDescriptorSets               = PFN_vkFreeDescriptorSets( vkGetDeviceProcAddr( device, "vkFreeDescriptorSets" ) );
        vkUpdateDescriptorSets             = PFN_vkUpdateDescriptorSets( vkGetDeviceProcAddr( device, "vkUpdateDescriptorSets" ) );
        vkCreateFramebuffer                = PFN_vkCreateFramebuffer( vkGetDeviceProcAddr( device, "vkCreateFramebuffer" ) );
        vkDestroyFramebuffer               = PFN_vkDestroyFramebuffer( vkGetDeviceProcAddr( device, "vkDestroyFramebuffer" ) );
        vkCreateRenderPass                 = PFN_vkCreateRenderPass( vkGetDeviceProcAddr( device, "vkCreateRenderPass" ) );
        vkDestroyRenderPass                = PFN_vkDestroyRenderPass( vkGetDeviceProcAddr( device, "vkDestroyRenderPass" ) );
        vkGetRenderAreaGranularity         = PFN_vkGetRenderAreaGranularity( vkGetDeviceProcAddr( device, "vkGetRenderAreaGranularity" ) );
        vkCreateCommandPool                = PFN_vkCreateCommandPool( vkGetDeviceProcAddr( device, "vkCreateCommandPool" ) );
        vkDestroyCommandPool               = PFN_vkDestroyCommandPool( vkGetDeviceProcAddr( device, "vkDestroyCommandPool" ) );
        vkResetCommandPool                 = PFN_vkResetCommandPool( vkGetDeviceProcAddr( device, "vkResetCommandPool" ) );
        vkAllocateCommandBuffers           = PFN_vkAllocateCommandBuffers( vkGetDeviceProcAddr( device, "vkAllocateCommandBuffers" ) );
        vkFreeCommandBuffers               = PFN_vkFreeCommandBuffers( vkGetDeviceProcAddr( device, "vkFreeCommandBuffers" ) );
        vkBeginCommandBuffer               = PFN_vkBeginCommandBuffer( vkGetDeviceProcAddr( device, "vkBeginCommandBuffer" ) );
        vkEndCommandBuffer                 = PFN_vkEndCommandBuffer( vkGetDeviceProcAddr( device, "vkEndCommandBuffer" ) );
        vkResetCommandBuffer               = PFN_vkResetCommandBuffer( vkGetDeviceProcAddr( device, "vkResetCommandBuffer" ) );
        vkCmdBindPipeline                  = PFN_vkCmdBindPipeline( vkGetDeviceProcAddr( device, "vkCmdBindPipeline" ) );
        vkCmdSetViewport                   = PFN_vkCmdSetViewport( vkGetDeviceProcAddr( device, "vkCmdSetViewport" ) );
        vkCmdSetScissor                    = PFN_vkCmdSetScissor( vkGetDeviceProcAddr( device, "vkCmdSetScissor" ) );
        vkCmdSetLineWidth                  = PFN_vkCmdSetLineWidth( vkGetDeviceProcAddr( device, "vkCmdSetLineWidth" ) );
        vkCmdSetDepthBias                  = PFN_vkCmdSetDepthBias( vkGetDeviceProcAddr( device, "vkCmdSetDepthBias" ) );
        vkCmdSetBlendConstants             = PFN_vkCmdSetBlendConstants( vkGetDeviceProcAddr( device, "vkCmdSetBlendConstants" ) );
        vkCmdSetDepthBounds                = PFN_vkCmdSetDepthBounds( vkGetDeviceProcAddr( device, "vkCmdSetDepthBounds" ) );
        vkCmdSetStencilCompareMask         = PFN_vkCmdSetStencilCompareMask( vkGetDeviceProcAddr( device, "vkCmdSetStencilCompareMask" ) );
        vkCmdSetStencilWriteMask           = PFN_vkCmdSetStencilWriteMask( vkGetDeviceProcAddr( device, "vkCmdSetStencilWriteMask" ) );
        vkCmdSetStencilReference           = PFN_vkCmdSetStencilReference( vkGetDeviceProcAddr( device, "vkCmdSetStencilReference" ) );
        vkCmdBindDescriptorSets            = PFN_vkCmdBindDescriptorSets( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorSets" ) );
        vkCmdBindIndexBuffer               = PFN_vkCmdBindIndexBuffer( vkGetDeviceProcAddr( device, "vkCmdBindIndexBuffer" ) );
        vkCmdBindVertexBuffers             = PFN_vkCmdBindVertexBuffers( vkGetDeviceProcAddr( device, "vkCmdBindVertexBuffers" ) );
        vkCmdDraw                          = PFN_vkCmdDraw( vkGetDeviceProcAddr( device, "vkCmdDraw" ) );
        vkCmdDrawIndexed                   = PFN_vkCmdDrawIndexed( vkGetDeviceProcAddr( device, "vkCmdDrawIndexed" ) );
        vkCmdDrawIndirect                  = PFN_vkCmdDrawIndirect( vkGetDeviceProcAddr( device, "vkCmdDrawIndirect" ) );
        vkCmdDrawIndexedIndirect           = PFN_vkCmdDrawIndexedIndirect( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirect" ) );
        vkCmdDispatch                      = PFN_vkCmdDispatch( vkGetDeviceProcAddr( device, "vkCmdDispatch" ) );
        vkCmdDispatchIndirect              = PFN_vkCmdDispatchIndirect( vkGetDeviceProcAddr( device, "vkCmdDispatchIndirect" ) );
        vkCmdCopyBuffer                    = PFN_vkCmdCopyBuffer( vkGetDeviceProcAddr( device, "vkCmdCopyBuffer" ) );
        vkCmdCopyImage                     = PFN_vkCmdCopyImage( vkGetDeviceProcAddr( device, "vkCmdCopyImage" ) );
        vkCmdBlitImage                     = PFN_vkCmdBlitImage( vkGetDeviceProcAddr( device, "vkCmdBlitImage" ) );
        vkCmdCopyBufferToImage             = PFN_vkCmdCopyBufferToImage( vkGetDeviceProcAddr( device, "vkCmdCopyBufferToImage" ) );
        vkCmdCopyImageToBuffer             = PFN_vkCmdCopyImageToBuffer( vkGetDeviceProcAddr( device, "vkCmdCopyImageToBuffer" ) );
        vkCmdUpdateBuffer                  = PFN_vkCmdUpdateBuffer( vkGetDeviceProcAddr( device, "vkCmdUpdateBuffer" ) );
        vkCmdFillBuffer                    = PFN_vkCmdFillBuffer( vkGetDeviceProcAddr( device, "vkCmdFillBuffer" ) );
        vkCmdClearColorImage               = PFN_vkCmdClearColorImage( vkGetDeviceProcAddr( device, "vkCmdClearColorImage" ) );
        vkCmdClearDepthStencilImage        = PFN_vkCmdClearDepthStencilImage( vkGetDeviceProcAddr( device, "vkCmdClearDepthStencilImage" ) );
        vkCmdClearAttachments              = PFN_vkCmdClearAttachments( vkGetDeviceProcAddr( device, "vkCmdClearAttachments" ) );
        vkCmdResolveImage                  = PFN_vkCmdResolveImage( vkGetDeviceProcAddr( device, "vkCmdResolveImage" ) );
        vkCmdSetEvent                      = PFN_vkCmdSetEvent( vkGetDeviceProcAddr( device, "vkCmdSetEvent" ) );
        vkCmdResetEvent                    = PFN_vkCmdResetEvent( vkGetDeviceProcAddr( device, "vkCmdResetEvent" ) );
        vkCmdWaitEvents                    = PFN_vkCmdWaitEvents( vkGetDeviceProcAddr( device, "vkCmdWaitEvents" ) );
        vkCmdPipelineBarrier               = PFN_vkCmdPipelineBarrier( vkGetDeviceProcAddr( device, "vkCmdPipelineBarrier" ) );
        vkCmdBeginQuery                    = PFN_vkCmdBeginQuery( vkGetDeviceProcAddr( device, "vkCmdBeginQuery" ) );
        vkCmdEndQuery                      = PFN_vkCmdEndQuery( vkGetDeviceProcAddr( device, "vkCmdEndQuery" ) );
        vkCmdResetQueryPool                = PFN_vkCmdResetQueryPool( vkGetDeviceProcAddr( device, "vkCmdResetQueryPool" ) );
        vkCmdWriteTimestamp                = PFN_vkCmdWriteTimestamp( vkGetDeviceProcAddr( device, "vkCmdWriteTimestamp" ) );
        vkCmdCopyQueryPoolResults          = PFN_vkCmdCopyQueryPoolResults( vkGetDeviceProcAddr( device, "vkCmdCopyQueryPoolResults" ) );
        vkCmdPushConstants                 = PFN_vkCmdPushConstants( vkGetDeviceProcAddr( device, "vkCmdPushConstants" ) );
        vkCmdBeginRenderPass               = PFN_vkCmdBeginRenderPass( vkGetDeviceProcAddr( device, "vkCmdBeginRenderPass" ) );
        vkCmdNextSubpass                   = PFN_vkCmdNextSubpass( vkGetDeviceProcAddr( device, "vkCmdNextSubpass" ) );
        vkCmdEndRenderPass                 = PFN_vkCmdEndRenderPass( vkGetDeviceProcAddr( device, "vkCmdEndRenderPass" ) );
        vkCmdExecuteCommands               = PFN_vkCmdExecuteCommands( vkGetDeviceProcAddr( device, "vkCmdExecuteCommands" ) );

        //=== VK_VERSION_1_1 ===
        vkBindBufferMemory2                 = PFN_vkBindBufferMemory2( vkGetDeviceProcAddr( device, "vkBindBufferMemory2" ) );
        vkBindImageMemory2                  = PFN_vkBindImageMemory2( vkGetDeviceProcAddr( device, "vkBindImageMemory2" ) );
        vkGetDeviceGroupPeerMemoryFeatures  = PFN_vkGetDeviceGroupPeerMemoryFeatures( vkGetDeviceProcAddr( device, "vkGetDeviceGroupPeerMemoryFeatures" ) );
        vkCmdSetDeviceMask                  = PFN_vkCmdSetDeviceMask( vkGetDeviceProcAddr( device, "vkCmdSetDeviceMask" ) );
        vkCmdDispatchBase                   = PFN_vkCmdDispatchBase( vkGetDeviceProcAddr( device, "vkCmdDispatchBase" ) );
        vkGetImageMemoryRequirements2       = PFN_vkGetImageMemoryRequirements2( vkGetDeviceProcAddr( device, "vkGetImageMemoryRequirements2" ) );
        vkGetBufferMemoryRequirements2      = PFN_vkGetBufferMemoryRequirements2( vkGetDeviceProcAddr( device, "vkGetBufferMemoryRequirements2" ) );
        vkGetImageSparseMemoryRequirements2 = PFN_vkGetImageSparseMemoryRequirements2( vkGetDeviceProcAddr( device, "vkGetImageSparseMemoryRequirements2" ) );
        vkTrimCommandPool                   = PFN_vkTrimCommandPool( vkGetDeviceProcAddr( device, "vkTrimCommandPool" ) );
        vkGetDeviceQueue2                   = PFN_vkGetDeviceQueue2( vkGetDeviceProcAddr( device, "vkGetDeviceQueue2" ) );
        vkCreateSamplerYcbcrConversion      = PFN_vkCreateSamplerYcbcrConversion( vkGetDeviceProcAddr( device, "vkCreateSamplerYcbcrConversion" ) );
        vkDestroySamplerYcbcrConversion     = PFN_vkDestroySamplerYcbcrConversion( vkGetDeviceProcAddr( device, "vkDestroySamplerYcbcrConversion" ) );
        vkCreateDescriptorUpdateTemplate    = PFN_vkCreateDescriptorUpdateTemplate( vkGetDeviceProcAddr( device, "vkCreateDescriptorUpdateTemplate" ) );
        vkDestroyDescriptorUpdateTemplate   = PFN_vkDestroyDescriptorUpdateTemplate( vkGetDeviceProcAddr( device, "vkDestroyDescriptorUpdateTemplate" ) );
        vkUpdateDescriptorSetWithTemplate   = PFN_vkUpdateDescriptorSetWithTemplate( vkGetDeviceProcAddr( device, "vkUpdateDescriptorSetWithTemplate" ) );
        vkGetDescriptorSetLayoutSupport     = PFN_vkGetDescriptorSetLayoutSupport( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutSupport" ) );

        //=== VK_VERSION_1_2 ===
        vkCmdDrawIndirectCount          = PFN_vkCmdDrawIndirectCount( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectCount" ) );
        vkCmdDrawIndexedIndirectCount   = PFN_vkCmdDrawIndexedIndirectCount( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirectCount" ) );
        vkCreateRenderPass2             = PFN_vkCreateRenderPass2( vkGetDeviceProcAddr( device, "vkCreateRenderPass2" ) );
        vkCmdBeginRenderPass2           = PFN_vkCmdBeginRenderPass2( vkGetDeviceProcAddr( device, "vkCmdBeginRenderPass2" ) );
        vkCmdNextSubpass2               = PFN_vkCmdNextSubpass2( vkGetDeviceProcAddr( device, "vkCmdNextSubpass2" ) );
        vkCmdEndRenderPass2             = PFN_vkCmdEndRenderPass2( vkGetDeviceProcAddr( device, "vkCmdEndRenderPass2" ) );
        vkResetQueryPool                = PFN_vkResetQueryPool( vkGetDeviceProcAddr( device, "vkResetQueryPool" ) );
        vkGetSemaphoreCounterValue      = PFN_vkGetSemaphoreCounterValue( vkGetDeviceProcAddr( device, "vkGetSemaphoreCounterValue" ) );
        vkWaitSemaphores                = PFN_vkWaitSemaphores( vkGetDeviceProcAddr( device, "vkWaitSemaphores" ) );
        vkSignalSemaphore               = PFN_vkSignalSemaphore( vkGetDeviceProcAddr( device, "vkSignalSemaphore" ) );
        vkGetBufferDeviceAddress        = PFN_vkGetBufferDeviceAddress( vkGetDeviceProcAddr( device, "vkGetBufferDeviceAddress" ) );
        vkGetBufferOpaqueCaptureAddress = PFN_vkGetBufferOpaqueCaptureAddress( vkGetDeviceProcAddr( device, "vkGetBufferOpaqueCaptureAddress" ) );
        vkGetDeviceMemoryOpaqueCaptureAddress =
            PFN_vkGetDeviceMemoryOpaqueCaptureAddress( vkGetDeviceProcAddr( device, "vkGetDeviceMemoryOpaqueCaptureAddress" ) );

        //=== VK_VERSION_1_3 ===
        vkCreatePrivateDataSlot             = PFN_vkCreatePrivateDataSlot( vkGetDeviceProcAddr( device, "vkCreatePrivateDataSlot" ) );
        vkDestroyPrivateDataSlot            = PFN_vkDestroyPrivateDataSlot( vkGetDeviceProcAddr( device, "vkDestroyPrivateDataSlot" ) );
        vkSetPrivateData                    = PFN_vkSetPrivateData( vkGetDeviceProcAddr( device, "vkSetPrivateData" ) );
        vkGetPrivateData                    = PFN_vkGetPrivateData( vkGetDeviceProcAddr( device, "vkGetPrivateData" ) );
        vkCmdSetEvent2                      = PFN_vkCmdSetEvent2( vkGetDeviceProcAddr( device, "vkCmdSetEvent2" ) );
        vkCmdResetEvent2                    = PFN_vkCmdResetEvent2( vkGetDeviceProcAddr( device, "vkCmdResetEvent2" ) );
        vkCmdWaitEvents2                    = PFN_vkCmdWaitEvents2( vkGetDeviceProcAddr( device, "vkCmdWaitEvents2" ) );
        vkCmdPipelineBarrier2               = PFN_vkCmdPipelineBarrier2( vkGetDeviceProcAddr( device, "vkCmdPipelineBarrier2" ) );
        vkCmdWriteTimestamp2                = PFN_vkCmdWriteTimestamp2( vkGetDeviceProcAddr( device, "vkCmdWriteTimestamp2" ) );
        vkQueueSubmit2                      = PFN_vkQueueSubmit2( vkGetDeviceProcAddr( device, "vkQueueSubmit2" ) );
        vkCmdCopyBuffer2                    = PFN_vkCmdCopyBuffer2( vkGetDeviceProcAddr( device, "vkCmdCopyBuffer2" ) );
        vkCmdCopyImage2                     = PFN_vkCmdCopyImage2( vkGetDeviceProcAddr( device, "vkCmdCopyImage2" ) );
        vkCmdCopyBufferToImage2             = PFN_vkCmdCopyBufferToImage2( vkGetDeviceProcAddr( device, "vkCmdCopyBufferToImage2" ) );
        vkCmdCopyImageToBuffer2             = PFN_vkCmdCopyImageToBuffer2( vkGetDeviceProcAddr( device, "vkCmdCopyImageToBuffer2" ) );
        vkCmdBlitImage2                     = PFN_vkCmdBlitImage2( vkGetDeviceProcAddr( device, "vkCmdBlitImage2" ) );
        vkCmdResolveImage2                  = PFN_vkCmdResolveImage2( vkGetDeviceProcAddr( device, "vkCmdResolveImage2" ) );
        vkCmdBeginRendering                 = PFN_vkCmdBeginRendering( vkGetDeviceProcAddr( device, "vkCmdBeginRendering" ) );
        vkCmdEndRendering                   = PFN_vkCmdEndRendering( vkGetDeviceProcAddr( device, "vkCmdEndRendering" ) );
        vkCmdSetCullMode                    = PFN_vkCmdSetCullMode( vkGetDeviceProcAddr( device, "vkCmdSetCullMode" ) );
        vkCmdSetFrontFace                   = PFN_vkCmdSetFrontFace( vkGetDeviceProcAddr( device, "vkCmdSetFrontFace" ) );
        vkCmdSetPrimitiveTopology           = PFN_vkCmdSetPrimitiveTopology( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveTopology" ) );
        vkCmdSetViewportWithCount           = PFN_vkCmdSetViewportWithCount( vkGetDeviceProcAddr( device, "vkCmdSetViewportWithCount" ) );
        vkCmdSetScissorWithCount            = PFN_vkCmdSetScissorWithCount( vkGetDeviceProcAddr( device, "vkCmdSetScissorWithCount" ) );
        vkCmdBindVertexBuffers2             = PFN_vkCmdBindVertexBuffers2( vkGetDeviceProcAddr( device, "vkCmdBindVertexBuffers2" ) );
        vkCmdSetDepthTestEnable             = PFN_vkCmdSetDepthTestEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthTestEnable" ) );
        vkCmdSetDepthWriteEnable            = PFN_vkCmdSetDepthWriteEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthWriteEnable" ) );
        vkCmdSetDepthCompareOp              = PFN_vkCmdSetDepthCompareOp( vkGetDeviceProcAddr( device, "vkCmdSetDepthCompareOp" ) );
        vkCmdSetDepthBoundsTestEnable       = PFN_vkCmdSetDepthBoundsTestEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthBoundsTestEnable" ) );
        vkCmdSetStencilTestEnable           = PFN_vkCmdSetStencilTestEnable( vkGetDeviceProcAddr( device, "vkCmdSetStencilTestEnable" ) );
        vkCmdSetStencilOp                   = PFN_vkCmdSetStencilOp( vkGetDeviceProcAddr( device, "vkCmdSetStencilOp" ) );
        vkCmdSetRasterizerDiscardEnable     = PFN_vkCmdSetRasterizerDiscardEnable( vkGetDeviceProcAddr( device, "vkCmdSetRasterizerDiscardEnable" ) );
        vkCmdSetDepthBiasEnable             = PFN_vkCmdSetDepthBiasEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthBiasEnable" ) );
        vkCmdSetPrimitiveRestartEnable      = PFN_vkCmdSetPrimitiveRestartEnable( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveRestartEnable" ) );
        vkGetDeviceBufferMemoryRequirements = PFN_vkGetDeviceBufferMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetDeviceBufferMemoryRequirements" ) );
        vkGetDeviceImageMemoryRequirements  = PFN_vkGetDeviceImageMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetDeviceImageMemoryRequirements" ) );
        vkGetDeviceImageSparseMemoryRequirements =
            PFN_vkGetDeviceImageSparseMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetDeviceImageSparseMemoryRequirements" ) );

        //=== VK_KHR_swapchain ===
        vkCreateSwapchainKHR    = PFN_vkCreateSwapchainKHR( vkGetDeviceProcAddr( device, "vkCreateSwapchainKHR" ) );
        vkDestroySwapchainKHR   = PFN_vkDestroySwapchainKHR( vkGetDeviceProcAddr( device, "vkDestroySwapchainKHR" ) );
        vkGetSwapchainImagesKHR = PFN_vkGetSwapchainImagesKHR( vkGetDeviceProcAddr( device, "vkGetSwapchainImagesKHR" ) );
        vkAcquireNextImageKHR   = PFN_vkAcquireNextImageKHR( vkGetDeviceProcAddr( device, "vkAcquireNextImageKHR" ) );
        vkQueuePresentKHR       = PFN_vkQueuePresentKHR( vkGetDeviceProcAddr( device, "vkQueuePresentKHR" ) );
        vkGetDeviceGroupPresentCapabilitiesKHR =
            PFN_vkGetDeviceGroupPresentCapabilitiesKHR( vkGetDeviceProcAddr( device, "vkGetDeviceGroupPresentCapabilitiesKHR" ) );
        vkGetDeviceGroupSurfacePresentModesKHR =
            PFN_vkGetDeviceGroupSurfacePresentModesKHR( vkGetDeviceProcAddr( device, "vkGetDeviceGroupSurfacePresentModesKHR" ) );
        vkAcquireNextImage2KHR = PFN_vkAcquireNextImage2KHR( vkGetDeviceProcAddr( device, "vkAcquireNextImage2KHR" ) );

        //=== VK_KHR_display_swapchain ===
        vkCreateSharedSwapchainsKHR = PFN_vkCreateSharedSwapchainsKHR( vkGetDeviceProcAddr( device, "vkCreateSharedSwapchainsKHR" ) );

        //=== VK_EXT_debug_marker ===
        vkDebugMarkerSetObjectTagEXT  = PFN_vkDebugMarkerSetObjectTagEXT( vkGetDeviceProcAddr( device, "vkDebugMarkerSetObjectTagEXT" ) );
        vkDebugMarkerSetObjectNameEXT = PFN_vkDebugMarkerSetObjectNameEXT( vkGetDeviceProcAddr( device, "vkDebugMarkerSetObjectNameEXT" ) );
        vkCmdDebugMarkerBeginEXT      = PFN_vkCmdDebugMarkerBeginEXT( vkGetDeviceProcAddr( device, "vkCmdDebugMarkerBeginEXT" ) );
        vkCmdDebugMarkerEndEXT        = PFN_vkCmdDebugMarkerEndEXT( vkGetDeviceProcAddr( device, "vkCmdDebugMarkerEndEXT" ) );
        vkCmdDebugMarkerInsertEXT     = PFN_vkCmdDebugMarkerInsertEXT( vkGetDeviceProcAddr( device, "vkCmdDebugMarkerInsertEXT" ) );

        //=== VK_KHR_video_queue ===
        vkCreateVideoSessionKHR  = PFN_vkCreateVideoSessionKHR( vkGetDeviceProcAddr( device, "vkCreateVideoSessionKHR" ) );
        vkDestroyVideoSessionKHR = PFN_vkDestroyVideoSessionKHR( vkGetDeviceProcAddr( device, "vkDestroyVideoSessionKHR" ) );
        vkGetVideoSessionMemoryRequirementsKHR =
            PFN_vkGetVideoSessionMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetVideoSessionMemoryRequirementsKHR" ) );
        vkBindVideoSessionMemoryKHR        = PFN_vkBindVideoSessionMemoryKHR( vkGetDeviceProcAddr( device, "vkBindVideoSessionMemoryKHR" ) );
        vkCreateVideoSessionParametersKHR  = PFN_vkCreateVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkCreateVideoSessionParametersKHR" ) );
        vkUpdateVideoSessionParametersKHR  = PFN_vkUpdateVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkUpdateVideoSessionParametersKHR" ) );
        vkDestroyVideoSessionParametersKHR = PFN_vkDestroyVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkDestroyVideoSessionParametersKHR" ) );
        vkCmdBeginVideoCodingKHR           = PFN_vkCmdBeginVideoCodingKHR( vkGetDeviceProcAddr( device, "vkCmdBeginVideoCodingKHR" ) );
        vkCmdEndVideoCodingKHR             = PFN_vkCmdEndVideoCodingKHR( vkGetDeviceProcAddr( device, "vkCmdEndVideoCodingKHR" ) );
        vkCmdControlVideoCodingKHR         = PFN_vkCmdControlVideoCodingKHR( vkGetDeviceProcAddr( device, "vkCmdControlVideoCodingKHR" ) );

        //=== VK_KHR_video_decode_queue ===
        vkCmdDecodeVideoKHR = PFN_vkCmdDecodeVideoKHR( vkGetDeviceProcAddr( device, "vkCmdDecodeVideoKHR" ) );

        //=== VK_EXT_transform_feedback ===
        vkCmdBindTransformFeedbackBuffersEXT =
            PFN_vkCmdBindTransformFeedbackBuffersEXT( vkGetDeviceProcAddr( device, "vkCmdBindTransformFeedbackBuffersEXT" ) );
        vkCmdBeginTransformFeedbackEXT = PFN_vkCmdBeginTransformFeedbackEXT( vkGetDeviceProcAddr( device, "vkCmdBeginTransformFeedbackEXT" ) );
        vkCmdEndTransformFeedbackEXT   = PFN_vkCmdEndTransformFeedbackEXT( vkGetDeviceProcAddr( device, "vkCmdEndTransformFeedbackEXT" ) );
        vkCmdBeginQueryIndexedEXT      = PFN_vkCmdBeginQueryIndexedEXT( vkGetDeviceProcAddr( device, "vkCmdBeginQueryIndexedEXT" ) );
        vkCmdEndQueryIndexedEXT        = PFN_vkCmdEndQueryIndexedEXT( vkGetDeviceProcAddr( device, "vkCmdEndQueryIndexedEXT" ) );
        vkCmdDrawIndirectByteCountEXT  = PFN_vkCmdDrawIndirectByteCountEXT( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectByteCountEXT" ) );

        //=== VK_NVX_binary_import ===
        vkCreateCuModuleNVX    = PFN_vkCreateCuModuleNVX( vkGetDeviceProcAddr( device, "vkCreateCuModuleNVX" ) );
        vkCreateCuFunctionNVX  = PFN_vkCreateCuFunctionNVX( vkGetDeviceProcAddr( device, "vkCreateCuFunctionNVX" ) );
        vkDestroyCuModuleNVX   = PFN_vkDestroyCuModuleNVX( vkGetDeviceProcAddr( device, "vkDestroyCuModuleNVX" ) );
        vkDestroyCuFunctionNVX = PFN_vkDestroyCuFunctionNVX( vkGetDeviceProcAddr( device, "vkDestroyCuFunctionNVX" ) );
        vkCmdCuLaunchKernelNVX = PFN_vkCmdCuLaunchKernelNVX( vkGetDeviceProcAddr( device, "vkCmdCuLaunchKernelNVX" ) );

        //=== VK_NVX_image_view_handle ===
        vkGetImageViewHandleNVX  = PFN_vkGetImageViewHandleNVX( vkGetDeviceProcAddr( device, "vkGetImageViewHandleNVX" ) );
        vkGetImageViewAddressNVX = PFN_vkGetImageViewAddressNVX( vkGetDeviceProcAddr( device, "vkGetImageViewAddressNVX" ) );

        //=== VK_AMD_draw_indirect_count ===
        vkCmdDrawIndirectCountAMD = PFN_vkCmdDrawIndirectCountAMD( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectCountAMD" ) );
        if ( !vkCmdDrawIndirectCount )
            vkCmdDrawIndirectCount = vkCmdDrawIndirectCountAMD;
        vkCmdDrawIndexedIndirectCountAMD = PFN_vkCmdDrawIndexedIndirectCountAMD( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirectCountAMD" ) );
        if ( !vkCmdDrawIndexedIndirectCount )
            vkCmdDrawIndexedIndirectCount = vkCmdDrawIndexedIndirectCountAMD;

        //=== VK_AMD_shader_info ===
        vkGetShaderInfoAMD = PFN_vkGetShaderInfoAMD( vkGetDeviceProcAddr( device, "vkGetShaderInfoAMD" ) );

        //=== VK_KHR_dynamic_rendering ===
        vkCmdBeginRenderingKHR = PFN_vkCmdBeginRenderingKHR( vkGetDeviceProcAddr( device, "vkCmdBeginRenderingKHR" ) );
        if ( !vkCmdBeginRendering )
            vkCmdBeginRendering = vkCmdBeginRenderingKHR;
        vkCmdEndRenderingKHR = PFN_vkCmdEndRenderingKHR( vkGetDeviceProcAddr( device, "vkCmdEndRenderingKHR" ) );
        if ( !vkCmdEndRendering )
            vkCmdEndRendering = vkCmdEndRenderingKHR;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_NV_external_memory_win32 ===
        vkGetMemoryWin32HandleNV = PFN_vkGetMemoryWin32HandleNV( vkGetDeviceProcAddr( device, "vkGetMemoryWin32HandleNV" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_device_group ===
        vkGetDeviceGroupPeerMemoryFeaturesKHR =
            PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR( vkGetDeviceProcAddr( device, "vkGetDeviceGroupPeerMemoryFeaturesKHR" ) );
        if ( !vkGetDeviceGroupPeerMemoryFeatures )
            vkGetDeviceGroupPeerMemoryFeatures = vkGetDeviceGroupPeerMemoryFeaturesKHR;
        vkCmdSetDeviceMaskKHR = PFN_vkCmdSetDeviceMaskKHR( vkGetDeviceProcAddr( device, "vkCmdSetDeviceMaskKHR" ) );
        if ( !vkCmdSetDeviceMask )
            vkCmdSetDeviceMask = vkCmdSetDeviceMaskKHR;
        vkCmdDispatchBaseKHR = PFN_vkCmdDispatchBaseKHR( vkGetDeviceProcAddr( device, "vkCmdDispatchBaseKHR" ) );
        if ( !vkCmdDispatchBase )
            vkCmdDispatchBase = vkCmdDispatchBaseKHR;

        //=== VK_KHR_maintenance1 ===
        vkTrimCommandPoolKHR = PFN_vkTrimCommandPoolKHR( vkGetDeviceProcAddr( device, "vkTrimCommandPoolKHR" ) );
        if ( !vkTrimCommandPool )
            vkTrimCommandPool = vkTrimCommandPoolKHR;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_memory_win32 ===
        vkGetMemoryWin32HandleKHR           = PFN_vkGetMemoryWin32HandleKHR( vkGetDeviceProcAddr( device, "vkGetMemoryWin32HandleKHR" ) );
        vkGetMemoryWin32HandlePropertiesKHR = PFN_vkGetMemoryWin32HandlePropertiesKHR( vkGetDeviceProcAddr( device, "vkGetMemoryWin32HandlePropertiesKHR" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_memory_fd ===
        vkGetMemoryFdKHR           = PFN_vkGetMemoryFdKHR( vkGetDeviceProcAddr( device, "vkGetMemoryFdKHR" ) );
        vkGetMemoryFdPropertiesKHR = PFN_vkGetMemoryFdPropertiesKHR( vkGetDeviceProcAddr( device, "vkGetMemoryFdPropertiesKHR" ) );

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_semaphore_win32 ===
        vkImportSemaphoreWin32HandleKHR = PFN_vkImportSemaphoreWin32HandleKHR( vkGetDeviceProcAddr( device, "vkImportSemaphoreWin32HandleKHR" ) );
        vkGetSemaphoreWin32HandleKHR    = PFN_vkGetSemaphoreWin32HandleKHR( vkGetDeviceProcAddr( device, "vkGetSemaphoreWin32HandleKHR" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_semaphore_fd ===
        vkImportSemaphoreFdKHR = PFN_vkImportSemaphoreFdKHR( vkGetDeviceProcAddr( device, "vkImportSemaphoreFdKHR" ) );
        vkGetSemaphoreFdKHR    = PFN_vkGetSemaphoreFdKHR( vkGetDeviceProcAddr( device, "vkGetSemaphoreFdKHR" ) );

        //=== VK_KHR_push_descriptor ===
        vkCmdPushDescriptorSetKHR = PFN_vkCmdPushDescriptorSetKHR( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSetKHR" ) );
        vkCmdPushDescriptorSetWithTemplateKHR =
            PFN_vkCmdPushDescriptorSetWithTemplateKHR( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSetWithTemplateKHR" ) );

        //=== VK_EXT_conditional_rendering ===
        vkCmdBeginConditionalRenderingEXT = PFN_vkCmdBeginConditionalRenderingEXT( vkGetDeviceProcAddr( device, "vkCmdBeginConditionalRenderingEXT" ) );
        vkCmdEndConditionalRenderingEXT   = PFN_vkCmdEndConditionalRenderingEXT( vkGetDeviceProcAddr( device, "vkCmdEndConditionalRenderingEXT" ) );

        //=== VK_KHR_descriptor_update_template ===
        vkCreateDescriptorUpdateTemplateKHR = PFN_vkCreateDescriptorUpdateTemplateKHR( vkGetDeviceProcAddr( device, "vkCreateDescriptorUpdateTemplateKHR" ) );
        if ( !vkCreateDescriptorUpdateTemplate )
            vkCreateDescriptorUpdateTemplate = vkCreateDescriptorUpdateTemplateKHR;
        vkDestroyDescriptorUpdateTemplateKHR =
            PFN_vkDestroyDescriptorUpdateTemplateKHR( vkGetDeviceProcAddr( device, "vkDestroyDescriptorUpdateTemplateKHR" ) );
        if ( !vkDestroyDescriptorUpdateTemplate )
            vkDestroyDescriptorUpdateTemplate = vkDestroyDescriptorUpdateTemplateKHR;
        vkUpdateDescriptorSetWithTemplateKHR =
            PFN_vkUpdateDescriptorSetWithTemplateKHR( vkGetDeviceProcAddr( device, "vkUpdateDescriptorSetWithTemplateKHR" ) );
        if ( !vkUpdateDescriptorSetWithTemplate )
            vkUpdateDescriptorSetWithTemplate = vkUpdateDescriptorSetWithTemplateKHR;

        //=== VK_NV_clip_space_w_scaling ===
        vkCmdSetViewportWScalingNV = PFN_vkCmdSetViewportWScalingNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportWScalingNV" ) );

        //=== VK_EXT_display_control ===
        vkDisplayPowerControlEXT  = PFN_vkDisplayPowerControlEXT( vkGetDeviceProcAddr( device, "vkDisplayPowerControlEXT" ) );
        vkRegisterDeviceEventEXT  = PFN_vkRegisterDeviceEventEXT( vkGetDeviceProcAddr( device, "vkRegisterDeviceEventEXT" ) );
        vkRegisterDisplayEventEXT = PFN_vkRegisterDisplayEventEXT( vkGetDeviceProcAddr( device, "vkRegisterDisplayEventEXT" ) );
        vkGetSwapchainCounterEXT  = PFN_vkGetSwapchainCounterEXT( vkGetDeviceProcAddr( device, "vkGetSwapchainCounterEXT" ) );

        //=== VK_GOOGLE_display_timing ===
        vkGetRefreshCycleDurationGOOGLE   = PFN_vkGetRefreshCycleDurationGOOGLE( vkGetDeviceProcAddr( device, "vkGetRefreshCycleDurationGOOGLE" ) );
        vkGetPastPresentationTimingGOOGLE = PFN_vkGetPastPresentationTimingGOOGLE( vkGetDeviceProcAddr( device, "vkGetPastPresentationTimingGOOGLE" ) );

        //=== VK_EXT_discard_rectangles ===
        vkCmdSetDiscardRectangleEXT       = PFN_vkCmdSetDiscardRectangleEXT( vkGetDeviceProcAddr( device, "vkCmdSetDiscardRectangleEXT" ) );
        vkCmdSetDiscardRectangleEnableEXT = PFN_vkCmdSetDiscardRectangleEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDiscardRectangleEnableEXT" ) );
        vkCmdSetDiscardRectangleModeEXT   = PFN_vkCmdSetDiscardRectangleModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetDiscardRectangleModeEXT" ) );

        //=== VK_EXT_hdr_metadata ===
        vkSetHdrMetadataEXT = PFN_vkSetHdrMetadataEXT( vkGetDeviceProcAddr( device, "vkSetHdrMetadataEXT" ) );

        //=== VK_KHR_create_renderpass2 ===
        vkCreateRenderPass2KHR = PFN_vkCreateRenderPass2KHR( vkGetDeviceProcAddr( device, "vkCreateRenderPass2KHR" ) );
        if ( !vkCreateRenderPass2 )
            vkCreateRenderPass2 = vkCreateRenderPass2KHR;
        vkCmdBeginRenderPass2KHR = PFN_vkCmdBeginRenderPass2KHR( vkGetDeviceProcAddr( device, "vkCmdBeginRenderPass2KHR" ) );
        if ( !vkCmdBeginRenderPass2 )
            vkCmdBeginRenderPass2 = vkCmdBeginRenderPass2KHR;
        vkCmdNextSubpass2KHR = PFN_vkCmdNextSubpass2KHR( vkGetDeviceProcAddr( device, "vkCmdNextSubpass2KHR" ) );
        if ( !vkCmdNextSubpass2 )
            vkCmdNextSubpass2 = vkCmdNextSubpass2KHR;
        vkCmdEndRenderPass2KHR = PFN_vkCmdEndRenderPass2KHR( vkGetDeviceProcAddr( device, "vkCmdEndRenderPass2KHR" ) );
        if ( !vkCmdEndRenderPass2 )
            vkCmdEndRenderPass2 = vkCmdEndRenderPass2KHR;

        //=== VK_KHR_shared_presentable_image ===
        vkGetSwapchainStatusKHR = PFN_vkGetSwapchainStatusKHR( vkGetDeviceProcAddr( device, "vkGetSwapchainStatusKHR" ) );

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_fence_win32 ===
        vkImportFenceWin32HandleKHR = PFN_vkImportFenceWin32HandleKHR( vkGetDeviceProcAddr( device, "vkImportFenceWin32HandleKHR" ) );
        vkGetFenceWin32HandleKHR    = PFN_vkGetFenceWin32HandleKHR( vkGetDeviceProcAddr( device, "vkGetFenceWin32HandleKHR" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_fence_fd ===
        vkImportFenceFdKHR = PFN_vkImportFenceFdKHR( vkGetDeviceProcAddr( device, "vkImportFenceFdKHR" ) );
        vkGetFenceFdKHR    = PFN_vkGetFenceFdKHR( vkGetDeviceProcAddr( device, "vkGetFenceFdKHR" ) );

        //=== VK_KHR_performance_query ===
        vkAcquireProfilingLockKHR = PFN_vkAcquireProfilingLockKHR( vkGetDeviceProcAddr( device, "vkAcquireProfilingLockKHR" ) );
        vkReleaseProfilingLockKHR = PFN_vkReleaseProfilingLockKHR( vkGetDeviceProcAddr( device, "vkReleaseProfilingLockKHR" ) );

        //=== VK_EXT_debug_utils ===
        vkSetDebugUtilsObjectNameEXT    = PFN_vkSetDebugUtilsObjectNameEXT( vkGetDeviceProcAddr( device, "vkSetDebugUtilsObjectNameEXT" ) );
        vkSetDebugUtilsObjectTagEXT     = PFN_vkSetDebugUtilsObjectTagEXT( vkGetDeviceProcAddr( device, "vkSetDebugUtilsObjectTagEXT" ) );
        vkQueueBeginDebugUtilsLabelEXT  = PFN_vkQueueBeginDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkQueueBeginDebugUtilsLabelEXT" ) );
        vkQueueEndDebugUtilsLabelEXT    = PFN_vkQueueEndDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkQueueEndDebugUtilsLabelEXT" ) );
        vkQueueInsertDebugUtilsLabelEXT = PFN_vkQueueInsertDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkQueueInsertDebugUtilsLabelEXT" ) );
        vkCmdBeginDebugUtilsLabelEXT    = PFN_vkCmdBeginDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkCmdBeginDebugUtilsLabelEXT" ) );
        vkCmdEndDebugUtilsLabelEXT      = PFN_vkCmdEndDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkCmdEndDebugUtilsLabelEXT" ) );
        vkCmdInsertDebugUtilsLabelEXT   = PFN_vkCmdInsertDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkCmdInsertDebugUtilsLabelEXT" ) );

#  if defined( VK_USE_PLATFORM_ANDROID_KHR )
        //=== VK_ANDROID_external_memory_android_hardware_buffer ===
        vkGetAndroidHardwareBufferPropertiesANDROID =
          PFN_vkGetAndroidHardwareBufferPropertiesANDROID( vkGetDeviceProcAddr( device, "vkGetAndroidHardwareBufferPropertiesANDROID" ) );
        vkGetMemoryAndroidHardwareBufferANDROID =
          PFN_vkGetMemoryAndroidHardwareBufferANDROID( vkGetDeviceProcAddr( device, "vkGetMemoryAndroidHardwareBufferANDROID" ) );
#  endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
        //=== VK_AMDX_shader_enqueue ===
        vkCreateExecutionGraphPipelinesAMDX = PFN_vkCreateExecutionGraphPipelinesAMDX( vkGetDeviceProcAddr( device, "vkCreateExecutionGraphPipelinesAMDX" ) );
        vkGetExecutionGraphPipelineScratchSizeAMDX =
            PFN_vkGetExecutionGraphPipelineScratchSizeAMDX( vkGetDeviceProcAddr( device, "vkGetExecutionGraphPipelineScratchSizeAMDX" ) );
        vkGetExecutionGraphPipelineNodeIndexAMDX =
            PFN_vkGetExecutionGraphPipelineNodeIndexAMDX( vkGetDeviceProcAddr( device, "vkGetExecutionGraphPipelineNodeIndexAMDX" ) );
        vkCmdInitializeGraphScratchMemoryAMDX =
            PFN_vkCmdInitializeGraphScratchMemoryAMDX( vkGetDeviceProcAddr( device, "vkCmdInitializeGraphScratchMemoryAMDX" ) );
        vkCmdDispatchGraphAMDX              = PFN_vkCmdDispatchGraphAMDX( vkGetDeviceProcAddr( device, "vkCmdDispatchGraphAMDX" ) );
        vkCmdDispatchGraphIndirectAMDX      = PFN_vkCmdDispatchGraphIndirectAMDX( vkGetDeviceProcAddr( device, "vkCmdDispatchGraphIndirectAMDX" ) );
        vkCmdDispatchGraphIndirectCountAMDX = PFN_vkCmdDispatchGraphIndirectCountAMDX( vkGetDeviceProcAddr( device, "vkCmdDispatchGraphIndirectCountAMDX" ) );
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

        //=== VK_EXT_sample_locations ===
        vkCmdSetSampleLocationsEXT = PFN_vkCmdSetSampleLocationsEXT( vkGetDeviceProcAddr( device, "vkCmdSetSampleLocationsEXT" ) );

        //=== VK_KHR_get_memory_requirements2 ===
        vkGetImageMemoryRequirements2KHR = PFN_vkGetImageMemoryRequirements2KHR( vkGetDeviceProcAddr( device, "vkGetImageMemoryRequirements2KHR" ) );
        if ( !vkGetImageMemoryRequirements2 )
            vkGetImageMemoryRequirements2 = vkGetImageMemoryRequirements2KHR;
        vkGetBufferMemoryRequirements2KHR = PFN_vkGetBufferMemoryRequirements2KHR( vkGetDeviceProcAddr( device, "vkGetBufferMemoryRequirements2KHR" ) );
        if ( !vkGetBufferMemoryRequirements2 )
            vkGetBufferMemoryRequirements2 = vkGetBufferMemoryRequirements2KHR;
        vkGetImageSparseMemoryRequirements2KHR =
            PFN_vkGetImageSparseMemoryRequirements2KHR( vkGetDeviceProcAddr( device, "vkGetImageSparseMemoryRequirements2KHR" ) );
        if ( !vkGetImageSparseMemoryRequirements2 )
            vkGetImageSparseMemoryRequirements2 = vkGetImageSparseMemoryRequirements2KHR;

        //=== VK_KHR_acceleration_structure ===
        vkCreateAccelerationStructureKHR    = PFN_vkCreateAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCreateAccelerationStructureKHR" ) );
        vkDestroyAccelerationStructureKHR   = PFN_vkDestroyAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkDestroyAccelerationStructureKHR" ) );
        vkCmdBuildAccelerationStructuresKHR = PFN_vkCmdBuildAccelerationStructuresKHR( vkGetDeviceProcAddr( device, "vkCmdBuildAccelerationStructuresKHR" ) );
        vkCmdBuildAccelerationStructuresIndirectKHR =
            PFN_vkCmdBuildAccelerationStructuresIndirectKHR( vkGetDeviceProcAddr( device, "vkCmdBuildAccelerationStructuresIndirectKHR" ) );
        vkBuildAccelerationStructuresKHR = PFN_vkBuildAccelerationStructuresKHR( vkGetDeviceProcAddr( device, "vkBuildAccelerationStructuresKHR" ) );
        vkCopyAccelerationStructureKHR   = PFN_vkCopyAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCopyAccelerationStructureKHR" ) );
        vkCopyAccelerationStructureToMemoryKHR =
            PFN_vkCopyAccelerationStructureToMemoryKHR( vkGetDeviceProcAddr( device, "vkCopyAccelerationStructureToMemoryKHR" ) );
        vkCopyMemoryToAccelerationStructureKHR =
            PFN_vkCopyMemoryToAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCopyMemoryToAccelerationStructureKHR" ) );
        vkWriteAccelerationStructuresPropertiesKHR =
            PFN_vkWriteAccelerationStructuresPropertiesKHR( vkGetDeviceProcAddr( device, "vkWriteAccelerationStructuresPropertiesKHR" ) );
        vkCmdCopyAccelerationStructureKHR = PFN_vkCmdCopyAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCmdCopyAccelerationStructureKHR" ) );
        vkCmdCopyAccelerationStructureToMemoryKHR =
            PFN_vkCmdCopyAccelerationStructureToMemoryKHR( vkGetDeviceProcAddr( device, "vkCmdCopyAccelerationStructureToMemoryKHR" ) );
        vkCmdCopyMemoryToAccelerationStructureKHR =
            PFN_vkCmdCopyMemoryToAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToAccelerationStructureKHR" ) );
        vkGetAccelerationStructureDeviceAddressKHR =
            PFN_vkGetAccelerationStructureDeviceAddressKHR( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureDeviceAddressKHR" ) );
        vkCmdWriteAccelerationStructuresPropertiesKHR =
            PFN_vkCmdWriteAccelerationStructuresPropertiesKHR( vkGetDeviceProcAddr( device, "vkCmdWriteAccelerationStructuresPropertiesKHR" ) );
        vkGetDeviceAccelerationStructureCompatibilityKHR =
            PFN_vkGetDeviceAccelerationStructureCompatibilityKHR( vkGetDeviceProcAddr( device, "vkGetDeviceAccelerationStructureCompatibilityKHR" ) );
        vkGetAccelerationStructureBuildSizesKHR =
            PFN_vkGetAccelerationStructureBuildSizesKHR( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureBuildSizesKHR" ) );

        //=== VK_KHR_ray_tracing_pipeline ===
        vkCmdTraceRaysKHR              = PFN_vkCmdTraceRaysKHR( vkGetDeviceProcAddr( device, "vkCmdTraceRaysKHR" ) );
        vkCreateRayTracingPipelinesKHR = PFN_vkCreateRayTracingPipelinesKHR( vkGetDeviceProcAddr( device, "vkCreateRayTracingPipelinesKHR" ) );
        vkGetRayTracingShaderGroupHandlesKHR =
            PFN_vkGetRayTracingShaderGroupHandlesKHR( vkGetDeviceProcAddr( device, "vkGetRayTracingShaderGroupHandlesKHR" ) );
        vkGetRayTracingCaptureReplayShaderGroupHandlesKHR =
            PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR( vkGetDeviceProcAddr( device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR" ) );
        vkCmdTraceRaysIndirectKHR = PFN_vkCmdTraceRaysIndirectKHR( vkGetDeviceProcAddr( device, "vkCmdTraceRaysIndirectKHR" ) );
        vkGetRayTracingShaderGroupStackSizeKHR =
            PFN_vkGetRayTracingShaderGroupStackSizeKHR( vkGetDeviceProcAddr( device, "vkGetRayTracingShaderGroupStackSizeKHR" ) );
        vkCmdSetRayTracingPipelineStackSizeKHR =
            PFN_vkCmdSetRayTracingPipelineStackSizeKHR( vkGetDeviceProcAddr( device, "vkCmdSetRayTracingPipelineStackSizeKHR" ) );

        //=== VK_KHR_sampler_ycbcr_conversion ===
        vkCreateSamplerYcbcrConversionKHR = PFN_vkCreateSamplerYcbcrConversionKHR( vkGetDeviceProcAddr( device, "vkCreateSamplerYcbcrConversionKHR" ) );
        if ( !vkCreateSamplerYcbcrConversion )
            vkCreateSamplerYcbcrConversion = vkCreateSamplerYcbcrConversionKHR;
        vkDestroySamplerYcbcrConversionKHR = PFN_vkDestroySamplerYcbcrConversionKHR( vkGetDeviceProcAddr( device, "vkDestroySamplerYcbcrConversionKHR" ) );
        if ( !vkDestroySamplerYcbcrConversion )
            vkDestroySamplerYcbcrConversion = vkDestroySamplerYcbcrConversionKHR;

        //=== VK_KHR_bind_memory2 ===
        vkBindBufferMemory2KHR = PFN_vkBindBufferMemory2KHR( vkGetDeviceProcAddr( device, "vkBindBufferMemory2KHR" ) );
        if ( !vkBindBufferMemory2 )
            vkBindBufferMemory2 = vkBindBufferMemory2KHR;
        vkBindImageMemory2KHR = PFN_vkBindImageMemory2KHR( vkGetDeviceProcAddr( device, "vkBindImageMemory2KHR" ) );
        if ( !vkBindImageMemory2 )
            vkBindImageMemory2 = vkBindImageMemory2KHR;

        //=== VK_EXT_image_drm_format_modifier ===
        vkGetImageDrmFormatModifierPropertiesEXT =
            PFN_vkGetImageDrmFormatModifierPropertiesEXT( vkGetDeviceProcAddr( device, "vkGetImageDrmFormatModifierPropertiesEXT" ) );

        //=== VK_EXT_validation_cache ===
        vkCreateValidationCacheEXT  = PFN_vkCreateValidationCacheEXT( vkGetDeviceProcAddr( device, "vkCreateValidationCacheEXT" ) );
        vkDestroyValidationCacheEXT = PFN_vkDestroyValidationCacheEXT( vkGetDeviceProcAddr( device, "vkDestroyValidationCacheEXT" ) );
        vkMergeValidationCachesEXT  = PFN_vkMergeValidationCachesEXT( vkGetDeviceProcAddr( device, "vkMergeValidationCachesEXT" ) );
        vkGetValidationCacheDataEXT = PFN_vkGetValidationCacheDataEXT( vkGetDeviceProcAddr( device, "vkGetValidationCacheDataEXT" ) );

        //=== VK_NV_shading_rate_image ===
        vkCmdBindShadingRateImageNV = PFN_vkCmdBindShadingRateImageNV( vkGetDeviceProcAddr( device, "vkCmdBindShadingRateImageNV" ) );
        vkCmdSetViewportShadingRatePaletteNV =
            PFN_vkCmdSetViewportShadingRatePaletteNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportShadingRatePaletteNV" ) );
        vkCmdSetCoarseSampleOrderNV = PFN_vkCmdSetCoarseSampleOrderNV( vkGetDeviceProcAddr( device, "vkCmdSetCoarseSampleOrderNV" ) );

        //=== VK_NV_ray_tracing ===
        vkCreateAccelerationStructureNV  = PFN_vkCreateAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkCreateAccelerationStructureNV" ) );
        vkDestroyAccelerationStructureNV = PFN_vkDestroyAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkDestroyAccelerationStructureNV" ) );
        vkGetAccelerationStructureMemoryRequirementsNV =
            PFN_vkGetAccelerationStructureMemoryRequirementsNV( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureMemoryRequirementsNV" ) );
        vkBindAccelerationStructureMemoryNV = PFN_vkBindAccelerationStructureMemoryNV( vkGetDeviceProcAddr( device, "vkBindAccelerationStructureMemoryNV" ) );
        vkCmdBuildAccelerationStructureNV   = PFN_vkCmdBuildAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkCmdBuildAccelerationStructureNV" ) );
        vkCmdCopyAccelerationStructureNV    = PFN_vkCmdCopyAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkCmdCopyAccelerationStructureNV" ) );
        vkCmdTraceRaysNV                    = PFN_vkCmdTraceRaysNV( vkGetDeviceProcAddr( device, "vkCmdTraceRaysNV" ) );
        vkCreateRayTracingPipelinesNV       = PFN_vkCreateRayTracingPipelinesNV( vkGetDeviceProcAddr( device, "vkCreateRayTracingPipelinesNV" ) );
        vkGetRayTracingShaderGroupHandlesNV = PFN_vkGetRayTracingShaderGroupHandlesNV( vkGetDeviceProcAddr( device, "vkGetRayTracingShaderGroupHandlesNV" ) );
        if ( !vkGetRayTracingShaderGroupHandlesKHR )
            vkGetRayTracingShaderGroupHandlesKHR = vkGetRayTracingShaderGroupHandlesNV;
        vkGetAccelerationStructureHandleNV = PFN_vkGetAccelerationStructureHandleNV( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureHandleNV" ) );
        vkCmdWriteAccelerationStructuresPropertiesNV =
            PFN_vkCmdWriteAccelerationStructuresPropertiesNV( vkGetDeviceProcAddr( device, "vkCmdWriteAccelerationStructuresPropertiesNV" ) );
        vkCompileDeferredNV = PFN_vkCompileDeferredNV( vkGetDeviceProcAddr( device, "vkCompileDeferredNV" ) );

        //=== VK_KHR_maintenance3 ===
        vkGetDescriptorSetLayoutSupportKHR = PFN_vkGetDescriptorSetLayoutSupportKHR( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutSupportKHR" ) );
        if ( !vkGetDescriptorSetLayoutSupport )
            vkGetDescriptorSetLayoutSupport = vkGetDescriptorSetLayoutSupportKHR;

        //=== VK_KHR_draw_indirect_count ===
        vkCmdDrawIndirectCountKHR = PFN_vkCmdDrawIndirectCountKHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectCountKHR" ) );
        if ( !vkCmdDrawIndirectCount )
            vkCmdDrawIndirectCount = vkCmdDrawIndirectCountKHR;
        vkCmdDrawIndexedIndirectCountKHR = PFN_vkCmdDrawIndexedIndirectCountKHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirectCountKHR" ) );
        if ( !vkCmdDrawIndexedIndirectCount )
            vkCmdDrawIndexedIndirectCount = vkCmdDrawIndexedIndirectCountKHR;

        //=== VK_EXT_external_memory_host ===
        vkGetMemoryHostPointerPropertiesEXT = PFN_vkGetMemoryHostPointerPropertiesEXT( vkGetDeviceProcAddr( device, "vkGetMemoryHostPointerPropertiesEXT" ) );

        //=== VK_AMD_buffer_marker ===
        vkCmdWriteBufferMarkerAMD = PFN_vkCmdWriteBufferMarkerAMD( vkGetDeviceProcAddr( device, "vkCmdWriteBufferMarkerAMD" ) );

        //=== VK_EXT_calibrated_timestamps ===
        vkGetCalibratedTimestampsEXT = PFN_vkGetCalibratedTimestampsEXT( vkGetDeviceProcAddr( device, "vkGetCalibratedTimestampsEXT" ) );

        //=== VK_NV_mesh_shader ===
        vkCmdDrawMeshTasksNV              = PFN_vkCmdDrawMeshTasksNV( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksNV" ) );
        vkCmdDrawMeshTasksIndirectNV      = PFN_vkCmdDrawMeshTasksIndirectNV( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectNV" ) );
        vkCmdDrawMeshTasksIndirectCountNV = PFN_vkCmdDrawMeshTasksIndirectCountNV( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectCountNV" ) );

        //=== VK_NV_scissor_exclusive ===
        vkCmdSetExclusiveScissorEnableNV = PFN_vkCmdSetExclusiveScissorEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetExclusiveScissorEnableNV" ) );
        vkCmdSetExclusiveScissorNV       = PFN_vkCmdSetExclusiveScissorNV( vkGetDeviceProcAddr( device, "vkCmdSetExclusiveScissorNV" ) );

        //=== VK_NV_device_diagnostic_checkpoints ===
        vkCmdSetCheckpointNV       = PFN_vkCmdSetCheckpointNV( vkGetDeviceProcAddr( device, "vkCmdSetCheckpointNV" ) );
        vkGetQueueCheckpointDataNV = PFN_vkGetQueueCheckpointDataNV( vkGetDeviceProcAddr( device, "vkGetQueueCheckpointDataNV" ) );

        //=== VK_KHR_timeline_semaphore ===
        vkGetSemaphoreCounterValueKHR = PFN_vkGetSemaphoreCounterValueKHR( vkGetDeviceProcAddr( device, "vkGetSemaphoreCounterValueKHR" ) );
        if ( !vkGetSemaphoreCounterValue )
            vkGetSemaphoreCounterValue = vkGetSemaphoreCounterValueKHR;
        vkWaitSemaphoresKHR = PFN_vkWaitSemaphoresKHR( vkGetDeviceProcAddr( device, "vkWaitSemaphoresKHR" ) );
        if ( !vkWaitSemaphores )
            vkWaitSemaphores = vkWaitSemaphoresKHR;
        vkSignalSemaphoreKHR = PFN_vkSignalSemaphoreKHR( vkGetDeviceProcAddr( device, "vkSignalSemaphoreKHR" ) );
        if ( !vkSignalSemaphore )
            vkSignalSemaphore = vkSignalSemaphoreKHR;

        //=== VK_INTEL_performance_query ===
        vkInitializePerformanceApiINTEL   = PFN_vkInitializePerformanceApiINTEL( vkGetDeviceProcAddr( device, "vkInitializePerformanceApiINTEL" ) );
        vkUninitializePerformanceApiINTEL = PFN_vkUninitializePerformanceApiINTEL( vkGetDeviceProcAddr( device, "vkUninitializePerformanceApiINTEL" ) );
        vkCmdSetPerformanceMarkerINTEL    = PFN_vkCmdSetPerformanceMarkerINTEL( vkGetDeviceProcAddr( device, "vkCmdSetPerformanceMarkerINTEL" ) );
        vkCmdSetPerformanceStreamMarkerINTEL =
            PFN_vkCmdSetPerformanceStreamMarkerINTEL( vkGetDeviceProcAddr( device, "vkCmdSetPerformanceStreamMarkerINTEL" ) );
        vkCmdSetPerformanceOverrideINTEL = PFN_vkCmdSetPerformanceOverrideINTEL( vkGetDeviceProcAddr( device, "vkCmdSetPerformanceOverrideINTEL" ) );
        vkAcquirePerformanceConfigurationINTEL =
            PFN_vkAcquirePerformanceConfigurationINTEL( vkGetDeviceProcAddr( device, "vkAcquirePerformanceConfigurationINTEL" ) );
        vkReleasePerformanceConfigurationINTEL =
            PFN_vkReleasePerformanceConfigurationINTEL( vkGetDeviceProcAddr( device, "vkReleasePerformanceConfigurationINTEL" ) );
        vkQueueSetPerformanceConfigurationINTEL =
            PFN_vkQueueSetPerformanceConfigurationINTEL( vkGetDeviceProcAddr( device, "vkQueueSetPerformanceConfigurationINTEL" ) );
        vkGetPerformanceParameterINTEL = PFN_vkGetPerformanceParameterINTEL( vkGetDeviceProcAddr( device, "vkGetPerformanceParameterINTEL" ) );

        //=== VK_AMD_display_native_hdr ===
        vkSetLocalDimmingAMD = PFN_vkSetLocalDimmingAMD( vkGetDeviceProcAddr( device, "vkSetLocalDimmingAMD" ) );

        //=== VK_KHR_fragment_shading_rate ===
        vkCmdSetFragmentShadingRateKHR = PFN_vkCmdSetFragmentShadingRateKHR( vkGetDeviceProcAddr( device, "vkCmdSetFragmentShadingRateKHR" ) );

        //=== VK_EXT_buffer_device_address ===
        vkGetBufferDeviceAddressEXT = PFN_vkGetBufferDeviceAddressEXT( vkGetDeviceProcAddr( device, "vkGetBufferDeviceAddressEXT" ) );
        if ( !vkGetBufferDeviceAddress )
            vkGetBufferDeviceAddress = vkGetBufferDeviceAddressEXT;

        //=== VK_KHR_present_wait ===
        vkWaitForPresentKHR = PFN_vkWaitForPresentKHR( vkGetDeviceProcAddr( device, "vkWaitForPresentKHR" ) );

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_EXT_full_screen_exclusive ===
        vkAcquireFullScreenExclusiveModeEXT = PFN_vkAcquireFullScreenExclusiveModeEXT( vkGetDeviceProcAddr( device, "vkAcquireFullScreenExclusiveModeEXT" ) );
        vkReleaseFullScreenExclusiveModeEXT = PFN_vkReleaseFullScreenExclusiveModeEXT( vkGetDeviceProcAddr( device, "vkReleaseFullScreenExclusiveModeEXT" ) );
        vkGetDeviceGroupSurfacePresentModes2EXT =
          PFN_vkGetDeviceGroupSurfacePresentModes2EXT( vkGetDeviceProcAddr( device, "vkGetDeviceGroupSurfacePresentModes2EXT" ) );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_buffer_device_address ===
        vkGetBufferDeviceAddressKHR = PFN_vkGetBufferDeviceAddressKHR( vkGetDeviceProcAddr( device, "vkGetBufferDeviceAddressKHR" ) );
        if ( !vkGetBufferDeviceAddress )
            vkGetBufferDeviceAddress = vkGetBufferDeviceAddressKHR;
        vkGetBufferOpaqueCaptureAddressKHR = PFN_vkGetBufferOpaqueCaptureAddressKHR( vkGetDeviceProcAddr( device, "vkGetBufferOpaqueCaptureAddressKHR" ) );
        if ( !vkGetBufferOpaqueCaptureAddress )
            vkGetBufferOpaqueCaptureAddress = vkGetBufferOpaqueCaptureAddressKHR;
        vkGetDeviceMemoryOpaqueCaptureAddressKHR =
            PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR( vkGetDeviceProcAddr( device, "vkGetDeviceMemoryOpaqueCaptureAddressKHR" ) );
        if ( !vkGetDeviceMemoryOpaqueCaptureAddress )
            vkGetDeviceMemoryOpaqueCaptureAddress = vkGetDeviceMemoryOpaqueCaptureAddressKHR;

        //=== VK_EXT_line_rasterization ===
        vkCmdSetLineStippleEXT = PFN_vkCmdSetLineStippleEXT( vkGetDeviceProcAddr( device, "vkCmdSetLineStippleEXT" ) );

        //=== VK_EXT_host_query_reset ===
        vkResetQueryPoolEXT = PFN_vkResetQueryPoolEXT( vkGetDeviceProcAddr( device, "vkResetQueryPoolEXT" ) );
        if ( !vkResetQueryPool )
            vkResetQueryPool = vkResetQueryPoolEXT;

        //=== VK_EXT_extended_dynamic_state ===
        vkCmdSetCullModeEXT = PFN_vkCmdSetCullModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetCullModeEXT" ) );
        if ( !vkCmdSetCullMode )
            vkCmdSetCullMode = vkCmdSetCullModeEXT;
        vkCmdSetFrontFaceEXT = PFN_vkCmdSetFrontFaceEXT( vkGetDeviceProcAddr( device, "vkCmdSetFrontFaceEXT" ) );
        if ( !vkCmdSetFrontFace )
            vkCmdSetFrontFace = vkCmdSetFrontFaceEXT;
        vkCmdSetPrimitiveTopologyEXT = PFN_vkCmdSetPrimitiveTopologyEXT( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveTopologyEXT" ) );
        if ( !vkCmdSetPrimitiveTopology )
            vkCmdSetPrimitiveTopology = vkCmdSetPrimitiveTopologyEXT;
        vkCmdSetViewportWithCountEXT = PFN_vkCmdSetViewportWithCountEXT( vkGetDeviceProcAddr( device, "vkCmdSetViewportWithCountEXT" ) );
        if ( !vkCmdSetViewportWithCount )
            vkCmdSetViewportWithCount = vkCmdSetViewportWithCountEXT;
        vkCmdSetScissorWithCountEXT = PFN_vkCmdSetScissorWithCountEXT( vkGetDeviceProcAddr( device, "vkCmdSetScissorWithCountEXT" ) );
        if ( !vkCmdSetScissorWithCount )
            vkCmdSetScissorWithCount = vkCmdSetScissorWithCountEXT;
        vkCmdBindVertexBuffers2EXT = PFN_vkCmdBindVertexBuffers2EXT( vkGetDeviceProcAddr( device, "vkCmdBindVertexBuffers2EXT" ) );
        if ( !vkCmdBindVertexBuffers2 )
            vkCmdBindVertexBuffers2 = vkCmdBindVertexBuffers2EXT;
        vkCmdSetDepthTestEnableEXT = PFN_vkCmdSetDepthTestEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthTestEnableEXT" ) );
        if ( !vkCmdSetDepthTestEnable )
            vkCmdSetDepthTestEnable = vkCmdSetDepthTestEnableEXT;
        vkCmdSetDepthWriteEnableEXT = PFN_vkCmdSetDepthWriteEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthWriteEnableEXT" ) );
        if ( !vkCmdSetDepthWriteEnable )
            vkCmdSetDepthWriteEnable = vkCmdSetDepthWriteEnableEXT;
        vkCmdSetDepthCompareOpEXT = PFN_vkCmdSetDepthCompareOpEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthCompareOpEXT" ) );
        if ( !vkCmdSetDepthCompareOp )
            vkCmdSetDepthCompareOp = vkCmdSetDepthCompareOpEXT;
        vkCmdSetDepthBoundsTestEnableEXT = PFN_vkCmdSetDepthBoundsTestEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthBoundsTestEnableEXT" ) );
        if ( !vkCmdSetDepthBoundsTestEnable )
            vkCmdSetDepthBoundsTestEnable = vkCmdSetDepthBoundsTestEnableEXT;
        vkCmdSetStencilTestEnableEXT = PFN_vkCmdSetStencilTestEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetStencilTestEnableEXT" ) );
        if ( !vkCmdSetStencilTestEnable )
            vkCmdSetStencilTestEnable = vkCmdSetStencilTestEnableEXT;
        vkCmdSetStencilOpEXT = PFN_vkCmdSetStencilOpEXT( vkGetDeviceProcAddr( device, "vkCmdSetStencilOpEXT" ) );
        if ( !vkCmdSetStencilOp )
            vkCmdSetStencilOp = vkCmdSetStencilOpEXT;

        //=== VK_KHR_deferred_host_operations ===
        vkCreateDeferredOperationKHR  = PFN_vkCreateDeferredOperationKHR( vkGetDeviceProcAddr( device, "vkCreateDeferredOperationKHR" ) );
        vkDestroyDeferredOperationKHR = PFN_vkDestroyDeferredOperationKHR( vkGetDeviceProcAddr( device, "vkDestroyDeferredOperationKHR" ) );
        vkGetDeferredOperationMaxConcurrencyKHR =
            PFN_vkGetDeferredOperationMaxConcurrencyKHR( vkGetDeviceProcAddr( device, "vkGetDeferredOperationMaxConcurrencyKHR" ) );
        vkGetDeferredOperationResultKHR = PFN_vkGetDeferredOperationResultKHR( vkGetDeviceProcAddr( device, "vkGetDeferredOperationResultKHR" ) );
        vkDeferredOperationJoinKHR      = PFN_vkDeferredOperationJoinKHR( vkGetDeviceProcAddr( device, "vkDeferredOperationJoinKHR" ) );

        //=== VK_KHR_pipeline_executable_properties ===
        vkGetPipelineExecutablePropertiesKHR =
            PFN_vkGetPipelineExecutablePropertiesKHR( vkGetDeviceProcAddr( device, "vkGetPipelineExecutablePropertiesKHR" ) );
        vkGetPipelineExecutableStatisticsKHR =
            PFN_vkGetPipelineExecutableStatisticsKHR( vkGetDeviceProcAddr( device, "vkGetPipelineExecutableStatisticsKHR" ) );
        vkGetPipelineExecutableInternalRepresentationsKHR =
            PFN_vkGetPipelineExecutableInternalRepresentationsKHR( vkGetDeviceProcAddr( device, "vkGetPipelineExecutableInternalRepresentationsKHR" ) );

        //=== VK_EXT_host_image_copy ===
        vkCopyMemoryToImageEXT          = PFN_vkCopyMemoryToImageEXT( vkGetDeviceProcAddr( device, "vkCopyMemoryToImageEXT" ) );
        vkCopyImageToMemoryEXT          = PFN_vkCopyImageToMemoryEXT( vkGetDeviceProcAddr( device, "vkCopyImageToMemoryEXT" ) );
        vkCopyImageToImageEXT           = PFN_vkCopyImageToImageEXT( vkGetDeviceProcAddr( device, "vkCopyImageToImageEXT" ) );
        vkTransitionImageLayoutEXT      = PFN_vkTransitionImageLayoutEXT( vkGetDeviceProcAddr( device, "vkTransitionImageLayoutEXT" ) );
        vkGetImageSubresourceLayout2EXT = PFN_vkGetImageSubresourceLayout2EXT( vkGetDeviceProcAddr( device, "vkGetImageSubresourceLayout2EXT" ) );
        if ( !vkGetImageSubresourceLayout2KHR )
            vkGetImageSubresourceLayout2KHR = vkGetImageSubresourceLayout2EXT;

        //=== VK_KHR_map_memory2 ===
        vkMapMemory2KHR   = PFN_vkMapMemory2KHR( vkGetDeviceProcAddr( device, "vkMapMemory2KHR" ) );
        vkUnmapMemory2KHR = PFN_vkUnmapMemory2KHR( vkGetDeviceProcAddr( device, "vkUnmapMemory2KHR" ) );

        //=== VK_EXT_swapchain_maintenance1 ===
        vkReleaseSwapchainImagesEXT = PFN_vkReleaseSwapchainImagesEXT( vkGetDeviceProcAddr( device, "vkReleaseSwapchainImagesEXT" ) );

        //=== VK_NV_device_generated_commands ===
        vkGetGeneratedCommandsMemoryRequirementsNV =
            PFN_vkGetGeneratedCommandsMemoryRequirementsNV( vkGetDeviceProcAddr( device, "vkGetGeneratedCommandsMemoryRequirementsNV" ) );
        vkCmdPreprocessGeneratedCommandsNV = PFN_vkCmdPreprocessGeneratedCommandsNV( vkGetDeviceProcAddr( device, "vkCmdPreprocessGeneratedCommandsNV" ) );
        vkCmdExecuteGeneratedCommandsNV    = PFN_vkCmdExecuteGeneratedCommandsNV( vkGetDeviceProcAddr( device, "vkCmdExecuteGeneratedCommandsNV" ) );
        vkCmdBindPipelineShaderGroupNV     = PFN_vkCmdBindPipelineShaderGroupNV( vkGetDeviceProcAddr( device, "vkCmdBindPipelineShaderGroupNV" ) );
        vkCreateIndirectCommandsLayoutNV   = PFN_vkCreateIndirectCommandsLayoutNV( vkGetDeviceProcAddr( device, "vkCreateIndirectCommandsLayoutNV" ) );
        vkDestroyIndirectCommandsLayoutNV  = PFN_vkDestroyIndirectCommandsLayoutNV( vkGetDeviceProcAddr( device, "vkDestroyIndirectCommandsLayoutNV" ) );

        //=== VK_EXT_depth_bias_control ===
        vkCmdSetDepthBias2EXT = PFN_vkCmdSetDepthBias2EXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthBias2EXT" ) );

        //=== VK_EXT_private_data ===
        vkCreatePrivateDataSlotEXT = PFN_vkCreatePrivateDataSlotEXT( vkGetDeviceProcAddr( device, "vkCreatePrivateDataSlotEXT" ) );
        if ( !vkCreatePrivateDataSlot )
            vkCreatePrivateDataSlot = vkCreatePrivateDataSlotEXT;
        vkDestroyPrivateDataSlotEXT = PFN_vkDestroyPrivateDataSlotEXT( vkGetDeviceProcAddr( device, "vkDestroyPrivateDataSlotEXT" ) );
        if ( !vkDestroyPrivateDataSlot )
            vkDestroyPrivateDataSlot = vkDestroyPrivateDataSlotEXT;
        vkSetPrivateDataEXT = PFN_vkSetPrivateDataEXT( vkGetDeviceProcAddr( device, "vkSetPrivateDataEXT" ) );
        if ( !vkSetPrivateData )
            vkSetPrivateData = vkSetPrivateDataEXT;
        vkGetPrivateDataEXT = PFN_vkGetPrivateDataEXT( vkGetDeviceProcAddr( device, "vkGetPrivateDataEXT" ) );
        if ( !vkGetPrivateData )
            vkGetPrivateData = vkGetPrivateDataEXT;

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
        //=== VK_KHR_video_encode_queue ===
        vkGetEncodedVideoSessionParametersKHR =
            PFN_vkGetEncodedVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkGetEncodedVideoSessionParametersKHR" ) );
        vkCmdEncodeVideoKHR = PFN_vkCmdEncodeVideoKHR( vkGetDeviceProcAddr( device, "vkCmdEncodeVideoKHR" ) );
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

#  if defined( VK_USE_PLATFORM_METAL_EXT )
        //=== VK_EXT_metal_objects ===
        vkExportMetalObjectsEXT = PFN_vkExportMetalObjectsEXT( vkGetDeviceProcAddr( device, "vkExportMetalObjectsEXT" ) );
#  endif /*VK_USE_PLATFORM_METAL_EXT*/

        //=== VK_KHR_synchronization2 ===
        vkCmdSetEvent2KHR = PFN_vkCmdSetEvent2KHR( vkGetDeviceProcAddr( device, "vkCmdSetEvent2KHR" ) );
        if ( !vkCmdSetEvent2 )
            vkCmdSetEvent2 = vkCmdSetEvent2KHR;
        vkCmdResetEvent2KHR = PFN_vkCmdResetEvent2KHR( vkGetDeviceProcAddr( device, "vkCmdResetEvent2KHR" ) );
        if ( !vkCmdResetEvent2 )
            vkCmdResetEvent2 = vkCmdResetEvent2KHR;
        vkCmdWaitEvents2KHR = PFN_vkCmdWaitEvents2KHR( vkGetDeviceProcAddr( device, "vkCmdWaitEvents2KHR" ) );
        if ( !vkCmdWaitEvents2 )
            vkCmdWaitEvents2 = vkCmdWaitEvents2KHR;
        vkCmdPipelineBarrier2KHR = PFN_vkCmdPipelineBarrier2KHR( vkGetDeviceProcAddr( device, "vkCmdPipelineBarrier2KHR" ) );
        if ( !vkCmdPipelineBarrier2 )
            vkCmdPipelineBarrier2 = vkCmdPipelineBarrier2KHR;
        vkCmdWriteTimestamp2KHR = PFN_vkCmdWriteTimestamp2KHR( vkGetDeviceProcAddr( device, "vkCmdWriteTimestamp2KHR" ) );
        if ( !vkCmdWriteTimestamp2 )
            vkCmdWriteTimestamp2 = vkCmdWriteTimestamp2KHR;
        vkQueueSubmit2KHR = PFN_vkQueueSubmit2KHR( vkGetDeviceProcAddr( device, "vkQueueSubmit2KHR" ) );
        if ( !vkQueueSubmit2 )
            vkQueueSubmit2 = vkQueueSubmit2KHR;
        vkCmdWriteBufferMarker2AMD  = PFN_vkCmdWriteBufferMarker2AMD( vkGetDeviceProcAddr( device, "vkCmdWriteBufferMarker2AMD" ) );
        vkGetQueueCheckpointData2NV = PFN_vkGetQueueCheckpointData2NV( vkGetDeviceProcAddr( device, "vkGetQueueCheckpointData2NV" ) );

        //=== VK_EXT_descriptor_buffer ===
        vkGetDescriptorSetLayoutSizeEXT = PFN_vkGetDescriptorSetLayoutSizeEXT( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutSizeEXT" ) );
        vkGetDescriptorSetLayoutBindingOffsetEXT =
            PFN_vkGetDescriptorSetLayoutBindingOffsetEXT( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutBindingOffsetEXT" ) );
        vkGetDescriptorEXT                 = PFN_vkGetDescriptorEXT( vkGetDeviceProcAddr( device, "vkGetDescriptorEXT" ) );
        vkCmdBindDescriptorBuffersEXT      = PFN_vkCmdBindDescriptorBuffersEXT( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorBuffersEXT" ) );
        vkCmdSetDescriptorBufferOffsetsEXT = PFN_vkCmdSetDescriptorBufferOffsetsEXT( vkGetDeviceProcAddr( device, "vkCmdSetDescriptorBufferOffsetsEXT" ) );
        vkCmdBindDescriptorBufferEmbeddedSamplersEXT =
            PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT" ) );
        vkGetBufferOpaqueCaptureDescriptorDataEXT =
            PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetBufferOpaqueCaptureDescriptorDataEXT" ) );
        vkGetImageOpaqueCaptureDescriptorDataEXT =
            PFN_vkGetImageOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetImageOpaqueCaptureDescriptorDataEXT" ) );
        vkGetImageViewOpaqueCaptureDescriptorDataEXT =
            PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetImageViewOpaqueCaptureDescriptorDataEXT" ) );
        vkGetSamplerOpaqueCaptureDescriptorDataEXT =
            PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetSamplerOpaqueCaptureDescriptorDataEXT" ) );
        vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(
            vkGetDeviceProcAddr( device, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT" ) );

        //=== VK_NV_fragment_shading_rate_enums ===
        vkCmdSetFragmentShadingRateEnumNV = PFN_vkCmdSetFragmentShadingRateEnumNV( vkGetDeviceProcAddr( device, "vkCmdSetFragmentShadingRateEnumNV" ) );

        //=== VK_EXT_mesh_shader ===
        vkCmdDrawMeshTasksEXT              = PFN_vkCmdDrawMeshTasksEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksEXT" ) );
        vkCmdDrawMeshTasksIndirectEXT      = PFN_vkCmdDrawMeshTasksIndirectEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectEXT" ) );
        vkCmdDrawMeshTasksIndirectCountEXT = PFN_vkCmdDrawMeshTasksIndirectCountEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectCountEXT" ) );

        //=== VK_KHR_copy_commands2 ===
        vkCmdCopyBuffer2KHR = PFN_vkCmdCopyBuffer2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyBuffer2KHR" ) );
        if ( !vkCmdCopyBuffer2 )
            vkCmdCopyBuffer2 = vkCmdCopyBuffer2KHR;
        vkCmdCopyImage2KHR = PFN_vkCmdCopyImage2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyImage2KHR" ) );
        if ( !vkCmdCopyImage2 )
            vkCmdCopyImage2 = vkCmdCopyImage2KHR;
        vkCmdCopyBufferToImage2KHR = PFN_vkCmdCopyBufferToImage2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyBufferToImage2KHR" ) );
        if ( !vkCmdCopyBufferToImage2 )
            vkCmdCopyBufferToImage2 = vkCmdCopyBufferToImage2KHR;
        vkCmdCopyImageToBuffer2KHR = PFN_vkCmdCopyImageToBuffer2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyImageToBuffer2KHR" ) );
        if ( !vkCmdCopyImageToBuffer2 )
            vkCmdCopyImageToBuffer2 = vkCmdCopyImageToBuffer2KHR;
        vkCmdBlitImage2KHR = PFN_vkCmdBlitImage2KHR( vkGetDeviceProcAddr( device, "vkCmdBlitImage2KHR" ) );
        if ( !vkCmdBlitImage2 )
            vkCmdBlitImage2 = vkCmdBlitImage2KHR;
        vkCmdResolveImage2KHR = PFN_vkCmdResolveImage2KHR( vkGetDeviceProcAddr( device, "vkCmdResolveImage2KHR" ) );
        if ( !vkCmdResolveImage2 )
            vkCmdResolveImage2 = vkCmdResolveImage2KHR;

        //=== VK_EXT_device_fault ===
        vkGetDeviceFaultInfoEXT = PFN_vkGetDeviceFaultInfoEXT( vkGetDeviceProcAddr( device, "vkGetDeviceFaultInfoEXT" ) );

        //=== VK_EXT_vertex_input_dynamic_state ===
        vkCmdSetVertexInputEXT = PFN_vkCmdSetVertexInputEXT( vkGetDeviceProcAddr( device, "vkCmdSetVertexInputEXT" ) );

#  if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_external_memory ===
        vkGetMemoryZirconHandleFUCHSIA = PFN_vkGetMemoryZirconHandleFUCHSIA( vkGetDeviceProcAddr( device, "vkGetMemoryZirconHandleFUCHSIA" ) );
        vkGetMemoryZirconHandlePropertiesFUCHSIA =
          PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA( vkGetDeviceProcAddr( device, "vkGetMemoryZirconHandlePropertiesFUCHSIA" ) );
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

#  if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_external_semaphore ===
        vkImportSemaphoreZirconHandleFUCHSIA =
          PFN_vkImportSemaphoreZirconHandleFUCHSIA( vkGetDeviceProcAddr( device, "vkImportSemaphoreZirconHandleFUCHSIA" ) );
        vkGetSemaphoreZirconHandleFUCHSIA = PFN_vkGetSemaphoreZirconHandleFUCHSIA( vkGetDeviceProcAddr( device, "vkGetSemaphoreZirconHandleFUCHSIA" ) );
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

#  if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_buffer_collection ===
        vkCreateBufferCollectionFUCHSIA = PFN_vkCreateBufferCollectionFUCHSIA( vkGetDeviceProcAddr( device, "vkCreateBufferCollectionFUCHSIA" ) );
        vkSetBufferCollectionImageConstraintsFUCHSIA =
          PFN_vkSetBufferCollectionImageConstraintsFUCHSIA( vkGetDeviceProcAddr( device, "vkSetBufferCollectionImageConstraintsFUCHSIA" ) );
        vkSetBufferCollectionBufferConstraintsFUCHSIA =
          PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA( vkGetDeviceProcAddr( device, "vkSetBufferCollectionBufferConstraintsFUCHSIA" ) );
        vkDestroyBufferCollectionFUCHSIA = PFN_vkDestroyBufferCollectionFUCHSIA( vkGetDeviceProcAddr( device, "vkDestroyBufferCollectionFUCHSIA" ) );
        vkGetBufferCollectionPropertiesFUCHSIA =
          PFN_vkGetBufferCollectionPropertiesFUCHSIA( vkGetDeviceProcAddr( device, "vkGetBufferCollectionPropertiesFUCHSIA" ) );
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

        //=== VK_HUAWEI_subpass_shading ===
        vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI =
            PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI( vkGetDeviceProcAddr( device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI" ) );
        vkCmdSubpassShadingHUAWEI = PFN_vkCmdSubpassShadingHUAWEI( vkGetDeviceProcAddr( device, "vkCmdSubpassShadingHUAWEI" ) );

        //=== VK_HUAWEI_invocation_mask ===
        vkCmdBindInvocationMaskHUAWEI = PFN_vkCmdBindInvocationMaskHUAWEI( vkGetDeviceProcAddr( device, "vkCmdBindInvocationMaskHUAWEI" ) );

        //=== VK_NV_external_memory_rdma ===
        vkGetMemoryRemoteAddressNV = PFN_vkGetMemoryRemoteAddressNV( vkGetDeviceProcAddr( device, "vkGetMemoryRemoteAddressNV" ) );

        //=== VK_EXT_pipeline_properties ===
        vkGetPipelinePropertiesEXT = PFN_vkGetPipelinePropertiesEXT( vkGetDeviceProcAddr( device, "vkGetPipelinePropertiesEXT" ) );

        //=== VK_EXT_extended_dynamic_state2 ===
        vkCmdSetPatchControlPointsEXT      = PFN_vkCmdSetPatchControlPointsEXT( vkGetDeviceProcAddr( device, "vkCmdSetPatchControlPointsEXT" ) );
        vkCmdSetRasterizerDiscardEnableEXT = PFN_vkCmdSetRasterizerDiscardEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetRasterizerDiscardEnableEXT" ) );
        if ( !vkCmdSetRasterizerDiscardEnable )
            vkCmdSetRasterizerDiscardEnable = vkCmdSetRasterizerDiscardEnableEXT;
        vkCmdSetDepthBiasEnableEXT = PFN_vkCmdSetDepthBiasEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthBiasEnableEXT" ) );
        if ( !vkCmdSetDepthBiasEnable )
            vkCmdSetDepthBiasEnable = vkCmdSetDepthBiasEnableEXT;
        vkCmdSetLogicOpEXT                = PFN_vkCmdSetLogicOpEXT( vkGetDeviceProcAddr( device, "vkCmdSetLogicOpEXT" ) );
        vkCmdSetPrimitiveRestartEnableEXT = PFN_vkCmdSetPrimitiveRestartEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveRestartEnableEXT" ) );
        if ( !vkCmdSetPrimitiveRestartEnable )
            vkCmdSetPrimitiveRestartEnable = vkCmdSetPrimitiveRestartEnableEXT;

        //=== VK_EXT_color_write_enable ===
        vkCmdSetColorWriteEnableEXT = PFN_vkCmdSetColorWriteEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorWriteEnableEXT" ) );

        //=== VK_KHR_ray_tracing_maintenance1 ===
        vkCmdTraceRaysIndirect2KHR = PFN_vkCmdTraceRaysIndirect2KHR( vkGetDeviceProcAddr( device, "vkCmdTraceRaysIndirect2KHR" ) );

        //=== VK_EXT_multi_draw ===
        vkCmdDrawMultiEXT        = PFN_vkCmdDrawMultiEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMultiEXT" ) );
        vkCmdDrawMultiIndexedEXT = PFN_vkCmdDrawMultiIndexedEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMultiIndexedEXT" ) );

        //=== VK_EXT_opacity_micromap ===
        vkCreateMicromapEXT                 = PFN_vkCreateMicromapEXT( vkGetDeviceProcAddr( device, "vkCreateMicromapEXT" ) );
        vkDestroyMicromapEXT                = PFN_vkDestroyMicromapEXT( vkGetDeviceProcAddr( device, "vkDestroyMicromapEXT" ) );
        vkCmdBuildMicromapsEXT              = PFN_vkCmdBuildMicromapsEXT( vkGetDeviceProcAddr( device, "vkCmdBuildMicromapsEXT" ) );
        vkBuildMicromapsEXT                 = PFN_vkBuildMicromapsEXT( vkGetDeviceProcAddr( device, "vkBuildMicromapsEXT" ) );
        vkCopyMicromapEXT                   = PFN_vkCopyMicromapEXT( vkGetDeviceProcAddr( device, "vkCopyMicromapEXT" ) );
        vkCopyMicromapToMemoryEXT           = PFN_vkCopyMicromapToMemoryEXT( vkGetDeviceProcAddr( device, "vkCopyMicromapToMemoryEXT" ) );
        vkCopyMemoryToMicromapEXT           = PFN_vkCopyMemoryToMicromapEXT( vkGetDeviceProcAddr( device, "vkCopyMemoryToMicromapEXT" ) );
        vkWriteMicromapsPropertiesEXT       = PFN_vkWriteMicromapsPropertiesEXT( vkGetDeviceProcAddr( device, "vkWriteMicromapsPropertiesEXT" ) );
        vkCmdCopyMicromapEXT                = PFN_vkCmdCopyMicromapEXT( vkGetDeviceProcAddr( device, "vkCmdCopyMicromapEXT" ) );
        vkCmdCopyMicromapToMemoryEXT        = PFN_vkCmdCopyMicromapToMemoryEXT( vkGetDeviceProcAddr( device, "vkCmdCopyMicromapToMemoryEXT" ) );
        vkCmdCopyMemoryToMicromapEXT        = PFN_vkCmdCopyMemoryToMicromapEXT( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToMicromapEXT" ) );
        vkCmdWriteMicromapsPropertiesEXT    = PFN_vkCmdWriteMicromapsPropertiesEXT( vkGetDeviceProcAddr( device, "vkCmdWriteMicromapsPropertiesEXT" ) );
        vkGetDeviceMicromapCompatibilityEXT = PFN_vkGetDeviceMicromapCompatibilityEXT( vkGetDeviceProcAddr( device, "vkGetDeviceMicromapCompatibilityEXT" ) );
        vkGetMicromapBuildSizesEXT          = PFN_vkGetMicromapBuildSizesEXT( vkGetDeviceProcAddr( device, "vkGetMicromapBuildSizesEXT" ) );

        //=== VK_HUAWEI_cluster_culling_shader ===
        vkCmdDrawClusterHUAWEI         = PFN_vkCmdDrawClusterHUAWEI( vkGetDeviceProcAddr( device, "vkCmdDrawClusterHUAWEI" ) );
        vkCmdDrawClusterIndirectHUAWEI = PFN_vkCmdDrawClusterIndirectHUAWEI( vkGetDeviceProcAddr( device, "vkCmdDrawClusterIndirectHUAWEI" ) );

        //=== VK_EXT_pageable_device_local_memory ===
        vkSetDeviceMemoryPriorityEXT = PFN_vkSetDeviceMemoryPriorityEXT( vkGetDeviceProcAddr( device, "vkSetDeviceMemoryPriorityEXT" ) );

        //=== VK_KHR_maintenance4 ===
        vkGetDeviceBufferMemoryRequirementsKHR =
            PFN_vkGetDeviceBufferMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetDeviceBufferMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceBufferMemoryRequirements )
            vkGetDeviceBufferMemoryRequirements = vkGetDeviceBufferMemoryRequirementsKHR;
        vkGetDeviceImageMemoryRequirementsKHR =
            PFN_vkGetDeviceImageMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetDeviceImageMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceImageMemoryRequirements )
            vkGetDeviceImageMemoryRequirements = vkGetDeviceImageMemoryRequirementsKHR;
        vkGetDeviceImageSparseMemoryRequirementsKHR =
            PFN_vkGetDeviceImageSparseMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetDeviceImageSparseMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceImageSparseMemoryRequirements )
            vkGetDeviceImageSparseMemoryRequirements = vkGetDeviceImageSparseMemoryRequirementsKHR;

        //=== VK_VALVE_descriptor_set_host_mapping ===
        vkGetDescriptorSetLayoutHostMappingInfoVALVE =
            PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutHostMappingInfoVALVE" ) );
        vkGetDescriptorSetHostMappingVALVE = PFN_vkGetDescriptorSetHostMappingVALVE( vkGetDeviceProcAddr( device, "vkGetDescriptorSetHostMappingVALVE" ) );

        //=== VK_NV_copy_memory_indirect ===
        vkCmdCopyMemoryIndirectNV        = PFN_vkCmdCopyMemoryIndirectNV( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryIndirectNV" ) );
        vkCmdCopyMemoryToImageIndirectNV = PFN_vkCmdCopyMemoryToImageIndirectNV( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToImageIndirectNV" ) );

        //=== VK_NV_memory_decompression ===
        vkCmdDecompressMemoryNV = PFN_vkCmdDecompressMemoryNV( vkGetDeviceProcAddr( device, "vkCmdDecompressMemoryNV" ) );
        vkCmdDecompressMemoryIndirectCountNV =
            PFN_vkCmdDecompressMemoryIndirectCountNV( vkGetDeviceProcAddr( device, "vkCmdDecompressMemoryIndirectCountNV" ) );

        //=== VK_NV_device_generated_commands_compute ===
        vkGetPipelineIndirectMemoryRequirementsNV =
            PFN_vkGetPipelineIndirectMemoryRequirementsNV( vkGetDeviceProcAddr( device, "vkGetPipelineIndirectMemoryRequirementsNV" ) );
        vkCmdUpdatePipelineIndirectBufferNV = PFN_vkCmdUpdatePipelineIndirectBufferNV( vkGetDeviceProcAddr( device, "vkCmdUpdatePipelineIndirectBufferNV" ) );
        vkGetPipelineIndirectDeviceAddressNV =
            PFN_vkGetPipelineIndirectDeviceAddressNV( vkGetDeviceProcAddr( device, "vkGetPipelineIndirectDeviceAddressNV" ) );

        //=== VK_EXT_extended_dynamic_state3 ===
        vkCmdSetTessellationDomainOriginEXT = PFN_vkCmdSetTessellationDomainOriginEXT( vkGetDeviceProcAddr( device, "vkCmdSetTessellationDomainOriginEXT" ) );
        vkCmdSetDepthClampEnableEXT         = PFN_vkCmdSetDepthClampEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthClampEnableEXT" ) );
        vkCmdSetPolygonModeEXT              = PFN_vkCmdSetPolygonModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetPolygonModeEXT" ) );
        vkCmdSetRasterizationSamplesEXT     = PFN_vkCmdSetRasterizationSamplesEXT( vkGetDeviceProcAddr( device, "vkCmdSetRasterizationSamplesEXT" ) );
        vkCmdSetSampleMaskEXT               = PFN_vkCmdSetSampleMaskEXT( vkGetDeviceProcAddr( device, "vkCmdSetSampleMaskEXT" ) );
        vkCmdSetAlphaToCoverageEnableEXT    = PFN_vkCmdSetAlphaToCoverageEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetAlphaToCoverageEnableEXT" ) );
        vkCmdSetAlphaToOneEnableEXT         = PFN_vkCmdSetAlphaToOneEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetAlphaToOneEnableEXT" ) );
        vkCmdSetLogicOpEnableEXT            = PFN_vkCmdSetLogicOpEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetLogicOpEnableEXT" ) );
        vkCmdSetColorBlendEnableEXT         = PFN_vkCmdSetColorBlendEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorBlendEnableEXT" ) );
        vkCmdSetColorBlendEquationEXT       = PFN_vkCmdSetColorBlendEquationEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorBlendEquationEXT" ) );
        vkCmdSetColorWriteMaskEXT           = PFN_vkCmdSetColorWriteMaskEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorWriteMaskEXT" ) );
        vkCmdSetRasterizationStreamEXT      = PFN_vkCmdSetRasterizationStreamEXT( vkGetDeviceProcAddr( device, "vkCmdSetRasterizationStreamEXT" ) );
        vkCmdSetConservativeRasterizationModeEXT =
            PFN_vkCmdSetConservativeRasterizationModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetConservativeRasterizationModeEXT" ) );
        vkCmdSetExtraPrimitiveOverestimationSizeEXT =
            PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT( vkGetDeviceProcAddr( device, "vkCmdSetExtraPrimitiveOverestimationSizeEXT" ) );
        vkCmdSetDepthClipEnableEXT       = PFN_vkCmdSetDepthClipEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthClipEnableEXT" ) );
        vkCmdSetSampleLocationsEnableEXT = PFN_vkCmdSetSampleLocationsEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetSampleLocationsEnableEXT" ) );
        vkCmdSetColorBlendAdvancedEXT    = PFN_vkCmdSetColorBlendAdvancedEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorBlendAdvancedEXT" ) );
        vkCmdSetProvokingVertexModeEXT   = PFN_vkCmdSetProvokingVertexModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetProvokingVertexModeEXT" ) );
        vkCmdSetLineRasterizationModeEXT = PFN_vkCmdSetLineRasterizationModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetLineRasterizationModeEXT" ) );
        vkCmdSetLineStippleEnableEXT     = PFN_vkCmdSetLineStippleEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetLineStippleEnableEXT" ) );
        vkCmdSetDepthClipNegativeOneToOneEXT =
            PFN_vkCmdSetDepthClipNegativeOneToOneEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthClipNegativeOneToOneEXT" ) );
        vkCmdSetViewportWScalingEnableNV  = PFN_vkCmdSetViewportWScalingEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportWScalingEnableNV" ) );
        vkCmdSetViewportSwizzleNV         = PFN_vkCmdSetViewportSwizzleNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportSwizzleNV" ) );
        vkCmdSetCoverageToColorEnableNV   = PFN_vkCmdSetCoverageToColorEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageToColorEnableNV" ) );
        vkCmdSetCoverageToColorLocationNV = PFN_vkCmdSetCoverageToColorLocationNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageToColorLocationNV" ) );
        vkCmdSetCoverageModulationModeNV  = PFN_vkCmdSetCoverageModulationModeNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageModulationModeNV" ) );
        vkCmdSetCoverageModulationTableEnableNV =
            PFN_vkCmdSetCoverageModulationTableEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageModulationTableEnableNV" ) );
        vkCmdSetCoverageModulationTableNV = PFN_vkCmdSetCoverageModulationTableNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageModulationTableNV" ) );
        vkCmdSetShadingRateImageEnableNV  = PFN_vkCmdSetShadingRateImageEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetShadingRateImageEnableNV" ) );
        vkCmdSetRepresentativeFragmentTestEnableNV =
            PFN_vkCmdSetRepresentativeFragmentTestEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetRepresentativeFragmentTestEnableNV" ) );
        vkCmdSetCoverageReductionModeNV = PFN_vkCmdSetCoverageReductionModeNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageReductionModeNV" ) );

        //=== VK_EXT_shader_module_identifier ===
        vkGetShaderModuleIdentifierEXT = PFN_vkGetShaderModuleIdentifierEXT( vkGetDeviceProcAddr( device, "vkGetShaderModuleIdentifierEXT" ) );
        vkGetShaderModuleCreateInfoIdentifierEXT =
            PFN_vkGetShaderModuleCreateInfoIdentifierEXT( vkGetDeviceProcAddr( device, "vkGetShaderModuleCreateInfoIdentifierEXT" ) );

        //=== VK_NV_optical_flow ===
        vkCreateOpticalFlowSessionNV    = PFN_vkCreateOpticalFlowSessionNV( vkGetDeviceProcAddr( device, "vkCreateOpticalFlowSessionNV" ) );
        vkDestroyOpticalFlowSessionNV   = PFN_vkDestroyOpticalFlowSessionNV( vkGetDeviceProcAddr( device, "vkDestroyOpticalFlowSessionNV" ) );
        vkBindOpticalFlowSessionImageNV = PFN_vkBindOpticalFlowSessionImageNV( vkGetDeviceProcAddr( device, "vkBindOpticalFlowSessionImageNV" ) );
        vkCmdOpticalFlowExecuteNV       = PFN_vkCmdOpticalFlowExecuteNV( vkGetDeviceProcAddr( device, "vkCmdOpticalFlowExecuteNV" ) );

        //=== VK_KHR_maintenance5 ===
        vkCmdBindIndexBuffer2KHR         = PFN_vkCmdBindIndexBuffer2KHR( vkGetDeviceProcAddr( device, "vkCmdBindIndexBuffer2KHR" ) );
        vkGetRenderingAreaGranularityKHR = PFN_vkGetRenderingAreaGranularityKHR( vkGetDeviceProcAddr( device, "vkGetRenderingAreaGranularityKHR" ) );
        vkGetDeviceImageSubresourceLayoutKHR =
            PFN_vkGetDeviceImageSubresourceLayoutKHR( vkGetDeviceProcAddr( device, "vkGetDeviceImageSubresourceLayoutKHR" ) );
        vkGetImageSubresourceLayout2KHR = PFN_vkGetImageSubresourceLayout2KHR( vkGetDeviceProcAddr( device, "vkGetImageSubresourceLayout2KHR" ) );

        //=== VK_EXT_shader_object ===
        vkCreateShadersEXT       = PFN_vkCreateShadersEXT( vkGetDeviceProcAddr( device, "vkCreateShadersEXT" ) );
        vkDestroyShaderEXT       = PFN_vkDestroyShaderEXT( vkGetDeviceProcAddr( device, "vkDestroyShaderEXT" ) );
        vkGetShaderBinaryDataEXT = PFN_vkGetShaderBinaryDataEXT( vkGetDeviceProcAddr( device, "vkGetShaderBinaryDataEXT" ) );
        vkCmdBindShadersEXT      = PFN_vkCmdBindShadersEXT( vkGetDeviceProcAddr( device, "vkCmdBindShadersEXT" ) );

        //=== VK_QCOM_tile_properties ===
        vkGetFramebufferTilePropertiesQCOM = PFN_vkGetFramebufferTilePropertiesQCOM( vkGetDeviceProcAddr( device, "vkGetFramebufferTilePropertiesQCOM" ) );
        vkGetDynamicRenderingTilePropertiesQCOM =
            PFN_vkGetDynamicRenderingTilePropertiesQCOM( vkGetDeviceProcAddr( device, "vkGetDynamicRenderingTilePropertiesQCOM" ) );

        //=== VK_EXT_attachment_feedback_loop_dynamic_state ===
        vkCmdSetAttachmentFeedbackLoopEnableEXT =
            PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetAttachmentFeedbackLoopEnableEXT" ) );

#  if defined( VK_USE_PLATFORM_SCREEN_QNX )
        //=== VK_QNX_external_memory_screen_buffer ===
        vkGetScreenBufferPropertiesQNX = PFN_vkGetScreenBufferPropertiesQNX( vkGetDeviceProcAddr( device, "vkGetScreenBufferPropertiesQNX" ) );
#  endif /*VK_USE_PLATFORM_SCREEN_QNX*/
    }

public:
    //=== VK_VERSION_1_0 ===
    PFN_vkGetDeviceProcAddr                vkGetDeviceProcAddr                = nullptr;
    PFN_vkDestroyDevice                    vkDestroyDevice                    = nullptr;
    PFN_vkGetDeviceQueue                   vkGetDeviceQueue                   = nullptr;
    PFN_vkQueueSubmit                      vkQueueSubmit                      = nullptr;
    PFN_vkQueueWaitIdle                    vkQueueWaitIdle                    = nullptr;
    PFN_vkDeviceWaitIdle                   vkDeviceWaitIdle                   = nullptr;
    PFN_vkAllocateMemory                   vkAllocateMemory                   = nullptr;
    PFN_vkFreeMemory                       vkFreeMemory                       = nullptr;
    PFN_vkMapMemory                        vkMapMemory                        = nullptr;
    PFN_vkUnmapMemory                      vkUnmapMemory                      = nullptr;
    PFN_vkFlushMappedMemoryRanges          vkFlushMappedMemoryRanges          = nullptr;
    PFN_vkInvalidateMappedMemoryRanges     vkInvalidateMappedMemoryRanges     = nullptr;
    PFN_vkGetDeviceMemoryCommitment        vkGetDeviceMemoryCommitment        = nullptr;
    PFN_vkBindBufferMemory                 vkBindBufferMemory                 = nullptr;
    PFN_vkBindImageMemory                  vkBindImageMemory                  = nullptr;
    PFN_vkGetBufferMemoryRequirements      vkGetBufferMemoryRequirements      = nullptr;
    PFN_vkGetImageMemoryRequirements       vkGetImageMemoryRequirements       = nullptr;
    PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements = nullptr;
    PFN_vkQueueBindSparse                  vkQueueBindSparse                  = nullptr;
    PFN_vkCreateFence                      vkCreateFence                      = nullptr;
    PFN_vkDestroyFence                     vkDestroyFence                     = nullptr;
    PFN_vkResetFences                      vkResetFences                      = nullptr;
    PFN_vkGetFenceStatus                   vkGetFenceStatus                   = nullptr;
    PFN_vkWaitForFences                    vkWaitForFences                    = nullptr;
    PFN_vkCreateSemaphore                  vkCreateSemaphore                  = nullptr;
    PFN_vkDestroySemaphore                 vkDestroySemaphore                 = nullptr;
    PFN_vkCreateEvent                      vkCreateEvent                      = nullptr;
    PFN_vkDestroyEvent                     vkDestroyEvent                     = nullptr;
    PFN_vkGetEventStatus                   vkGetEventStatus                   = nullptr;
    PFN_vkSetEvent                         vkSetEvent                         = nullptr;
    PFN_vkResetEvent                       vkResetEvent                       = nullptr;
    PFN_vkCreateQueryPool                  vkCreateQueryPool                  = nullptr;
    PFN_vkDestroyQueryPool                 vkDestroyQueryPool                 = nullptr;
    PFN_vkGetQueryPoolResults              vkGetQueryPoolResults              = nullptr;
    PFN_vkCreateBuffer                     vkCreateBuffer                     = nullptr;
    PFN_vkDestroyBuffer                    vkDestroyBuffer                    = nullptr;
    PFN_vkCreateBufferView                 vkCreateBufferView                 = nullptr;
    PFN_vkDestroyBufferView                vkDestroyBufferView                = nullptr;
    PFN_vkCreateImage                      vkCreateImage                      = nullptr;
    PFN_vkDestroyImage                     vkDestroyImage                     = nullptr;
    PFN_vkGetImageSubresourceLayout        vkGetImageSubresourceLayout        = nullptr;
    PFN_vkCreateImageView                  vkCreateImageView                  = nullptr;
    PFN_vkDestroyImageView                 vkDestroyImageView                 = nullptr;
    PFN_vkCreateShaderModule               vkCreateShaderModule               = nullptr;
    PFN_vkDestroyShaderModule              vkDestroyShaderModule              = nullptr;
    PFN_vkCreatePipelineCache              vkCreatePipelineCache              = nullptr;
    PFN_vkDestroyPipelineCache             vkDestroyPipelineCache             = nullptr;
    PFN_vkGetPipelineCacheData             vkGetPipelineCacheData             = nullptr;
    PFN_vkMergePipelineCaches              vkMergePipelineCaches              = nullptr;
    PFN_vkCreateGraphicsPipelines          vkCreateGraphicsPipelines          = nullptr;
    PFN_vkCreateComputePipelines           vkCreateComputePipelines           = nullptr;
    PFN_vkDestroyPipeline                  vkDestroyPipeline                  = nullptr;
    PFN_vkCreatePipelineLayout             vkCreatePipelineLayout             = nullptr;
    PFN_vkDestroyPipelineLayout            vkDestroyPipelineLayout            = nullptr;
    PFN_vkCreateSampler                    vkCreateSampler                    = nullptr;
    PFN_vkDestroySampler                   vkDestroySampler                   = nullptr;
    PFN_vkCreateDescriptorSetLayout        vkCreateDescriptorSetLayout        = nullptr;
    PFN_vkDestroyDescriptorSetLayout       vkDestroyDescriptorSetLayout       = nullptr;
    PFN_vkCreateDescriptorPool             vkCreateDescriptorPool             = nullptr;
    PFN_vkDestroyDescriptorPool            vkDestroyDescriptorPool            = nullptr;
    PFN_vkResetDescriptorPool              vkResetDescriptorPool              = nullptr;
    PFN_vkAllocateDescriptorSets           vkAllocateDescriptorSets           = nullptr;
    PFN_vkFreeDescriptorSets               vkFreeDescriptorSets               = nullptr;
    PFN_vkUpdateDescriptorSets             vkUpdateDescriptorSets             = nullptr;
    PFN_vkCreateFramebuffer                vkCreateFramebuffer                = nullptr;
    PFN_vkDestroyFramebuffer               vkDestroyFramebuffer               = nullptr;
    PFN_vkCreateRenderPass                 vkCreateRenderPass                 = nullptr;
    PFN_vkDestroyRenderPass                vkDestroyRenderPass                = nullptr;
    PFN_vkGetRenderAreaGranularity         vkGetRenderAreaGranularity         = nullptr;
    PFN_vkCreateCommandPool                vkCreateCommandPool                = nullptr;
    PFN_vkDestroyCommandPool               vkDestroyCommandPool               = nullptr;
    PFN_vkResetCommandPool                 vkResetCommandPool                 = nullptr;
    PFN_vkAllocateCommandBuffers           vkAllocateCommandBuffers           = nullptr;
    PFN_vkFreeCommandBuffers               vkFreeCommandBuffers               = nullptr;
    PFN_vkBeginCommandBuffer               vkBeginCommandBuffer               = nullptr;
    PFN_vkEndCommandBuffer                 vkEndCommandBuffer                 = nullptr;
    PFN_vkResetCommandBuffer               vkResetCommandBuffer               = nullptr;
    PFN_vkCmdBindPipeline                  vkCmdBindPipeline                  = nullptr;
    PFN_vkCmdSetViewport                   vkCmdSetViewport                   = nullptr;
    PFN_vkCmdSetScissor                    vkCmdSetScissor                    = nullptr;
    PFN_vkCmdSetLineWidth                  vkCmdSetLineWidth                  = nullptr;
    PFN_vkCmdSetDepthBias                  vkCmdSetDepthBias                  = nullptr;
    PFN_vkCmdSetBlendConstants             vkCmdSetBlendConstants             = nullptr;
    PFN_vkCmdSetDepthBounds                vkCmdSetDepthBounds                = nullptr;
    PFN_vkCmdSetStencilCompareMask         vkCmdSetStencilCompareMask         = nullptr;
    PFN_vkCmdSetStencilWriteMask           vkCmdSetStencilWriteMask           = nullptr;
    PFN_vkCmdSetStencilReference           vkCmdSetStencilReference           = nullptr;
    PFN_vkCmdBindDescriptorSets            vkCmdBindDescriptorSets            = nullptr;
    PFN_vkCmdBindIndexBuffer               vkCmdBindIndexBuffer               = nullptr;
    PFN_vkCmdBindVertexBuffers             vkCmdBindVertexBuffers             = nullptr;
    PFN_vkCmdDraw                          vkCmdDraw                          = nullptr;
    PFN_vkCmdDrawIndexed                   vkCmdDrawIndexed                   = nullptr;
    PFN_vkCmdDrawIndirect                  vkCmdDrawIndirect                  = nullptr;
    PFN_vkCmdDrawIndexedIndirect           vkCmdDrawIndexedIndirect           = nullptr;
    PFN_vkCmdDispatch                      vkCmdDispatch                      = nullptr;
    PFN_vkCmdDispatchIndirect              vkCmdDispatchIndirect              = nullptr;
    PFN_vkCmdCopyBuffer                    vkCmdCopyBuffer                    = nullptr;
    PFN_vkCmdCopyImage                     vkCmdCopyImage                     = nullptr;
    PFN_vkCmdBlitImage                     vkCmdBlitImage                     = nullptr;
    PFN_vkCmdCopyBufferToImage             vkCmdCopyBufferToImage             = nullptr;
    PFN_vkCmdCopyImageToBuffer             vkCmdCopyImageToBuffer             = nullptr;
    PFN_vkCmdUpdateBuffer                  vkCmdUpdateBuffer                  = nullptr;
    PFN_vkCmdFillBuffer                    vkCmdFillBuffer                    = nullptr;
    PFN_vkCmdClearColorImage               vkCmdClearColorImage               = nullptr;
    PFN_vkCmdClearDepthStencilImage        vkCmdClearDepthStencilImage        = nullptr;
    PFN_vkCmdClearAttachments              vkCmdClearAttachments              = nullptr;
    PFN_vkCmdResolveImage                  vkCmdResolveImage                  = nullptr;
    PFN_vkCmdSetEvent                      vkCmdSetEvent                      = nullptr;
    PFN_vkCmdResetEvent                    vkCmdResetEvent                    = nullptr;
    PFN_vkCmdWaitEvents                    vkCmdWaitEvents                    = nullptr;
    PFN_vkCmdPipelineBarrier               vkCmdPipelineBarrier               = nullptr;
    PFN_vkCmdBeginQuery                    vkCmdBeginQuery                    = nullptr;
    PFN_vkCmdEndQuery                      vkCmdEndQuery                      = nullptr;
    PFN_vkCmdResetQueryPool                vkCmdResetQueryPool                = nullptr;
    PFN_vkCmdWriteTimestamp                vkCmdWriteTimestamp                = nullptr;
    PFN_vkCmdCopyQueryPoolResults          vkCmdCopyQueryPoolResults          = nullptr;
    PFN_vkCmdPushConstants                 vkCmdPushConstants                 = nullptr;
    PFN_vkCmdBeginRenderPass               vkCmdBeginRenderPass               = nullptr;
    PFN_vkCmdNextSubpass                   vkCmdNextSubpass                   = nullptr;
    PFN_vkCmdEndRenderPass                 vkCmdEndRenderPass                 = nullptr;
    PFN_vkCmdExecuteCommands               vkCmdExecuteCommands               = nullptr;

    //=== VK_VERSION_1_1 ===
    PFN_vkBindBufferMemory2                 vkBindBufferMemory2                 = nullptr;
    PFN_vkBindImageMemory2                  vkBindImageMemory2                  = nullptr;
    PFN_vkGetDeviceGroupPeerMemoryFeatures  vkGetDeviceGroupPeerMemoryFeatures  = nullptr;
    PFN_vkCmdSetDeviceMask                  vkCmdSetDeviceMask                  = nullptr;
    PFN_vkCmdDispatchBase                   vkCmdDispatchBase                   = nullptr;
    PFN_vkGetImageMemoryRequirements2       vkGetImageMemoryRequirements2       = nullptr;
    PFN_vkGetBufferMemoryRequirements2      vkGetBufferMemoryRequirements2      = nullptr;
    PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2 = nullptr;
    PFN_vkTrimCommandPool                   vkTrimCommandPool                   = nullptr;
    PFN_vkGetDeviceQueue2                   vkGetDeviceQueue2                   = nullptr;
    PFN_vkCreateSamplerYcbcrConversion      vkCreateSamplerYcbcrConversion      = nullptr;
    PFN_vkDestroySamplerYcbcrConversion     vkDestroySamplerYcbcrConversion     = nullptr;
    PFN_vkCreateDescriptorUpdateTemplate    vkCreateDescriptorUpdateTemplate    = nullptr;
    PFN_vkDestroyDescriptorUpdateTemplate   vkDestroyDescriptorUpdateTemplate   = nullptr;
    PFN_vkUpdateDescriptorSetWithTemplate   vkUpdateDescriptorSetWithTemplate   = nullptr;
    PFN_vkGetDescriptorSetLayoutSupport     vkGetDescriptorSetLayoutSupport     = nullptr;

    //=== VK_VERSION_1_2 ===
    PFN_vkCmdDrawIndirectCount                vkCmdDrawIndirectCount                = nullptr;
    PFN_vkCmdDrawIndexedIndirectCount         vkCmdDrawIndexedIndirectCount         = nullptr;
    PFN_vkCreateRenderPass2                   vkCreateRenderPass2                   = nullptr;
    PFN_vkCmdBeginRenderPass2                 vkCmdBeginRenderPass2                 = nullptr;
    PFN_vkCmdNextSubpass2                     vkCmdNextSubpass2                     = nullptr;
    PFN_vkCmdEndRenderPass2                   vkCmdEndRenderPass2                   = nullptr;
    PFN_vkResetQueryPool                      vkResetQueryPool                      = nullptr;
    PFN_vkGetSemaphoreCounterValue            vkGetSemaphoreCounterValue            = nullptr;
    PFN_vkWaitSemaphores                      vkWaitSemaphores                      = nullptr;
    PFN_vkSignalSemaphore                     vkSignalSemaphore                     = nullptr;
    PFN_vkGetBufferDeviceAddress              vkGetBufferDeviceAddress              = nullptr;
    PFN_vkGetBufferOpaqueCaptureAddress       vkGetBufferOpaqueCaptureAddress       = nullptr;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress = nullptr;

    //=== VK_VERSION_1_3 ===
    PFN_vkCreatePrivateDataSlot                  vkCreatePrivateDataSlot                  = nullptr;
    PFN_vkDestroyPrivateDataSlot                 vkDestroyPrivateDataSlot                 = nullptr;
    PFN_vkSetPrivateData                         vkSetPrivateData                         = nullptr;
    PFN_vkGetPrivateData                         vkGetPrivateData                         = nullptr;
    PFN_vkCmdSetEvent2                           vkCmdSetEvent2                           = nullptr;
    PFN_vkCmdResetEvent2                         vkCmdResetEvent2                         = nullptr;
    PFN_vkCmdWaitEvents2                         vkCmdWaitEvents2                         = nullptr;
    PFN_vkCmdPipelineBarrier2                    vkCmdPipelineBarrier2                    = nullptr;
    PFN_vkCmdWriteTimestamp2                     vkCmdWriteTimestamp2                     = nullptr;
    PFN_vkQueueSubmit2                           vkQueueSubmit2                           = nullptr;
    PFN_vkCmdCopyBuffer2                         vkCmdCopyBuffer2                         = nullptr;
    PFN_vkCmdCopyImage2                          vkCmdCopyImage2                          = nullptr;
    PFN_vkCmdCopyBufferToImage2                  vkCmdCopyBufferToImage2                  = nullptr;
    PFN_vkCmdCopyImageToBuffer2                  vkCmdCopyImageToBuffer2                  = nullptr;
    PFN_vkCmdBlitImage2                          vkCmdBlitImage2                          = nullptr;
    PFN_vkCmdResolveImage2                       vkCmdResolveImage2                       = nullptr;
    PFN_vkCmdBeginRendering                      vkCmdBeginRendering                      = nullptr;
    PFN_vkCmdEndRendering                        vkCmdEndRendering                        = nullptr;
    PFN_vkCmdSetCullMode                         vkCmdSetCullMode                         = nullptr;
    PFN_vkCmdSetFrontFace                        vkCmdSetFrontFace                        = nullptr;
    PFN_vkCmdSetPrimitiveTopology                vkCmdSetPrimitiveTopology                = nullptr;
    PFN_vkCmdSetViewportWithCount                vkCmdSetViewportWithCount                = nullptr;
    PFN_vkCmdSetScissorWithCount                 vkCmdSetScissorWithCount                 = nullptr;
    PFN_vkCmdBindVertexBuffers2                  vkCmdBindVertexBuffers2                  = nullptr;
    PFN_vkCmdSetDepthTestEnable                  vkCmdSetDepthTestEnable                  = nullptr;
    PFN_vkCmdSetDepthWriteEnable                 vkCmdSetDepthWriteEnable                 = nullptr;
    PFN_vkCmdSetDepthCompareOp                   vkCmdSetDepthCompareOp                   = nullptr;
    PFN_vkCmdSetDepthBoundsTestEnable            vkCmdSetDepthBoundsTestEnable            = nullptr;
    PFN_vkCmdSetStencilTestEnable                vkCmdSetStencilTestEnable                = nullptr;
    PFN_vkCmdSetStencilOp                        vkCmdSetStencilOp                        = nullptr;
    PFN_vkCmdSetRasterizerDiscardEnable          vkCmdSetRasterizerDiscardEnable          = nullptr;
    PFN_vkCmdSetDepthBiasEnable                  vkCmdSetDepthBiasEnable                  = nullptr;
    PFN_vkCmdSetPrimitiveRestartEnable           vkCmdSetPrimitiveRestartEnable           = nullptr;
    PFN_vkGetDeviceBufferMemoryRequirements      vkGetDeviceBufferMemoryRequirements      = nullptr;
    PFN_vkGetDeviceImageMemoryRequirements       vkGetDeviceImageMemoryRequirements       = nullptr;
    PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements = nullptr;

    //=== VK_KHR_swapchain ===
    PFN_vkCreateSwapchainKHR                   vkCreateSwapchainKHR                   = nullptr;
    PFN_vkDestroySwapchainKHR                  vkDestroySwapchainKHR                  = nullptr;
    PFN_vkGetSwapchainImagesKHR                vkGetSwapchainImagesKHR                = nullptr;
    PFN_vkAcquireNextImageKHR                  vkAcquireNextImageKHR                  = nullptr;
    PFN_vkQueuePresentKHR                      vkQueuePresentKHR                      = nullptr;
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR = nullptr;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR = nullptr;
    PFN_vkAcquireNextImage2KHR                 vkAcquireNextImage2KHR                 = nullptr;

    //=== VK_KHR_display_swapchain ===
    PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR = nullptr;

    //=== VK_EXT_debug_marker ===
    PFN_vkDebugMarkerSetObjectTagEXT  vkDebugMarkerSetObjectTagEXT  = nullptr;
    PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT = nullptr;
    PFN_vkCmdDebugMarkerBeginEXT      vkCmdDebugMarkerBeginEXT      = nullptr;
    PFN_vkCmdDebugMarkerEndEXT        vkCmdDebugMarkerEndEXT        = nullptr;
    PFN_vkCmdDebugMarkerInsertEXT     vkCmdDebugMarkerInsertEXT     = nullptr;

    //=== VK_KHR_video_queue ===
    PFN_vkCreateVideoSessionKHR                vkCreateVideoSessionKHR                = nullptr;
    PFN_vkDestroyVideoSessionKHR               vkDestroyVideoSessionKHR               = nullptr;
    PFN_vkGetVideoSessionMemoryRequirementsKHR vkGetVideoSessionMemoryRequirementsKHR = nullptr;
    PFN_vkBindVideoSessionMemoryKHR            vkBindVideoSessionMemoryKHR            = nullptr;
    PFN_vkCreateVideoSessionParametersKHR      vkCreateVideoSessionParametersKHR      = nullptr;
    PFN_vkUpdateVideoSessionParametersKHR      vkUpdateVideoSessionParametersKHR      = nullptr;
    PFN_vkDestroyVideoSessionParametersKHR     vkDestroyVideoSessionParametersKHR     = nullptr;
    PFN_vkCmdBeginVideoCodingKHR               vkCmdBeginVideoCodingKHR               = nullptr;
    PFN_vkCmdEndVideoCodingKHR                 vkCmdEndVideoCodingKHR                 = nullptr;
    PFN_vkCmdControlVideoCodingKHR             vkCmdControlVideoCodingKHR             = nullptr;

    //=== VK_KHR_video_decode_queue ===
    PFN_vkCmdDecodeVideoKHR vkCmdDecodeVideoKHR = nullptr;

    //=== VK_EXT_transform_feedback ===
    PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT = nullptr;
    PFN_vkCmdBeginTransformFeedbackEXT       vkCmdBeginTransformFeedbackEXT       = nullptr;
    PFN_vkCmdEndTransformFeedbackEXT         vkCmdEndTransformFeedbackEXT         = nullptr;
    PFN_vkCmdBeginQueryIndexedEXT            vkCmdBeginQueryIndexedEXT            = nullptr;
    PFN_vkCmdEndQueryIndexedEXT              vkCmdEndQueryIndexedEXT              = nullptr;
    PFN_vkCmdDrawIndirectByteCountEXT        vkCmdDrawIndirectByteCountEXT        = nullptr;

    //=== VK_NVX_binary_import ===
    PFN_vkCreateCuModuleNVX    vkCreateCuModuleNVX    = nullptr;
    PFN_vkCreateCuFunctionNVX  vkCreateCuFunctionNVX  = nullptr;
    PFN_vkDestroyCuModuleNVX   vkDestroyCuModuleNVX   = nullptr;
    PFN_vkDestroyCuFunctionNVX vkDestroyCuFunctionNVX = nullptr;
    PFN_vkCmdCuLaunchKernelNVX vkCmdCuLaunchKernelNVX = nullptr;

    //=== VK_NVX_image_view_handle ===
    PFN_vkGetImageViewHandleNVX  vkGetImageViewHandleNVX  = nullptr;
    PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX = nullptr;

    //=== VK_AMD_draw_indirect_count ===
    PFN_vkCmdDrawIndirectCountAMD        vkCmdDrawIndirectCountAMD        = nullptr;
    PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD = nullptr;

    //=== VK_AMD_shader_info ===
    PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD = nullptr;

    //=== VK_KHR_dynamic_rendering ===
    PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR = nullptr;
    PFN_vkCmdEndRenderingKHR   vkCmdEndRenderingKHR   = nullptr;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_NV_external_memory_win32 ===
      PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV = nullptr;
#  else
    PFN_dummy vkGetMemoryWin32HandleNV_placeholder                                = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

    //=== VK_KHR_device_group ===
    PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR = nullptr;
    PFN_vkCmdSetDeviceMaskKHR                 vkCmdSetDeviceMaskKHR                 = nullptr;
    PFN_vkCmdDispatchBaseKHR                  vkCmdDispatchBaseKHR                  = nullptr;

    //=== VK_KHR_maintenance1 ===
    PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR = nullptr;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_KHR_external_memory_win32 ===
      PFN_vkGetMemoryWin32HandleKHR           vkGetMemoryWin32HandleKHR           = nullptr;
      PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR = nullptr;
#  else
    PFN_dummy vkGetMemoryWin32HandleKHR_placeholder                               = nullptr;
    PFN_dummy vkGetMemoryWin32HandlePropertiesKHR_placeholder                     = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

    //=== VK_KHR_external_memory_fd ===
    PFN_vkGetMemoryFdKHR           vkGetMemoryFdKHR           = nullptr;
    PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR = nullptr;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_KHR_external_semaphore_win32 ===
      PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR = nullptr;
      PFN_vkGetSemaphoreWin32HandleKHR    vkGetSemaphoreWin32HandleKHR    = nullptr;
#  else
    PFN_dummy vkImportSemaphoreWin32HandleKHR_placeholder                         = nullptr;
    PFN_dummy vkGetSemaphoreWin32HandleKHR_placeholder                            = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

    //=== VK_KHR_external_semaphore_fd ===
    PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR = nullptr;
    PFN_vkGetSemaphoreFdKHR    vkGetSemaphoreFdKHR    = nullptr;

    //=== VK_KHR_push_descriptor ===
    PFN_vkCmdPushDescriptorSetKHR             vkCmdPushDescriptorSetKHR             = nullptr;
    PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR = nullptr;

    //=== VK_EXT_conditional_rendering ===
    PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT = nullptr;
    PFN_vkCmdEndConditionalRenderingEXT   vkCmdEndConditionalRenderingEXT   = nullptr;

    //=== VK_KHR_descriptor_update_template ===
    PFN_vkCreateDescriptorUpdateTemplateKHR  vkCreateDescriptorUpdateTemplateKHR  = nullptr;
    PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR = nullptr;
    PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR = nullptr;

    //=== VK_NV_clip_space_w_scaling ===
    PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV = nullptr;

    //=== VK_EXT_display_control ===
    PFN_vkDisplayPowerControlEXT  vkDisplayPowerControlEXT  = nullptr;
    PFN_vkRegisterDeviceEventEXT  vkRegisterDeviceEventEXT  = nullptr;
    PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT = nullptr;
    PFN_vkGetSwapchainCounterEXT  vkGetSwapchainCounterEXT  = nullptr;

    //=== VK_GOOGLE_display_timing ===
    PFN_vkGetRefreshCycleDurationGOOGLE   vkGetRefreshCycleDurationGOOGLE   = nullptr;
    PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE = nullptr;

    //=== VK_EXT_discard_rectangles ===
    PFN_vkCmdSetDiscardRectangleEXT       vkCmdSetDiscardRectangleEXT       = nullptr;
    PFN_vkCmdSetDiscardRectangleEnableEXT vkCmdSetDiscardRectangleEnableEXT = nullptr;
    PFN_vkCmdSetDiscardRectangleModeEXT   vkCmdSetDiscardRectangleModeEXT   = nullptr;

    //=== VK_EXT_hdr_metadata ===
    PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT = nullptr;

    //=== VK_KHR_create_renderpass2 ===
    PFN_vkCreateRenderPass2KHR   vkCreateRenderPass2KHR   = nullptr;
    PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR = nullptr;
    PFN_vkCmdNextSubpass2KHR     vkCmdNextSubpass2KHR     = nullptr;
    PFN_vkCmdEndRenderPass2KHR   vkCmdEndRenderPass2KHR   = nullptr;

    //=== VK_KHR_shared_presentable_image ===
    PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR = nullptr;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_KHR_external_fence_win32 ===
      PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR = nullptr;
      PFN_vkGetFenceWin32HandleKHR    vkGetFenceWin32HandleKHR    = nullptr;
#  else
    PFN_dummy vkImportFenceWin32HandleKHR_placeholder                             = nullptr;
    PFN_dummy vkGetFenceWin32HandleKHR_placeholder                                = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

    //=== VK_KHR_external_fence_fd ===
    PFN_vkImportFenceFdKHR vkImportFenceFdKHR = nullptr;
    PFN_vkGetFenceFdKHR    vkGetFenceFdKHR    = nullptr;

    //=== VK_KHR_performance_query ===
    PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR = nullptr;
    PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR = nullptr;

    //=== VK_EXT_debug_utils ===
    PFN_vkSetDebugUtilsObjectNameEXT    vkSetDebugUtilsObjectNameEXT    = nullptr;
    PFN_vkSetDebugUtilsObjectTagEXT     vkSetDebugUtilsObjectTagEXT     = nullptr;
    PFN_vkQueueBeginDebugUtilsLabelEXT  vkQueueBeginDebugUtilsLabelEXT  = nullptr;
    PFN_vkQueueEndDebugUtilsLabelEXT    vkQueueEndDebugUtilsLabelEXT    = nullptr;
    PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdBeginDebugUtilsLabelEXT    vkCmdBeginDebugUtilsLabelEXT    = nullptr;
    PFN_vkCmdEndDebugUtilsLabelEXT      vkCmdEndDebugUtilsLabelEXT      = nullptr;
    PFN_vkCmdInsertDebugUtilsLabelEXT   vkCmdInsertDebugUtilsLabelEXT   = nullptr;

#  if defined( VK_USE_PLATFORM_ANDROID_KHR )
    //=== VK_ANDROID_external_memory_android_hardware_buffer ===
      PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID = nullptr;
      PFN_vkGetMemoryAndroidHardwareBufferANDROID     vkGetMemoryAndroidHardwareBufferANDROID     = nullptr;
#  else
    PFN_dummy vkGetAndroidHardwareBufferPropertiesANDROID_placeholder             = nullptr;
    PFN_dummy vkGetMemoryAndroidHardwareBufferANDROID_placeholder                 = nullptr;
#  endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
    //=== VK_AMDX_shader_enqueue ===
    PFN_vkCreateExecutionGraphPipelinesAMDX        vkCreateExecutionGraphPipelinesAMDX        = nullptr;
    PFN_vkGetExecutionGraphPipelineScratchSizeAMDX vkGetExecutionGraphPipelineScratchSizeAMDX = nullptr;
    PFN_vkGetExecutionGraphPipelineNodeIndexAMDX   vkGetExecutionGraphPipelineNodeIndexAMDX   = nullptr;
    PFN_vkCmdInitializeGraphScratchMemoryAMDX      vkCmdInitializeGraphScratchMemoryAMDX      = nullptr;
    PFN_vkCmdDispatchGraphAMDX                     vkCmdDispatchGraphAMDX                     = nullptr;
    PFN_vkCmdDispatchGraphIndirectAMDX             vkCmdDispatchGraphIndirectAMDX             = nullptr;
    PFN_vkCmdDispatchGraphIndirectCountAMDX        vkCmdDispatchGraphIndirectCountAMDX        = nullptr;
#  else
    PFN_dummy vkCreateExecutionGraphPipelinesAMDX_placeholder                     = nullptr;
      PFN_dummy vkGetExecutionGraphPipelineScratchSizeAMDX_placeholder              = nullptr;
      PFN_dummy vkGetExecutionGraphPipelineNodeIndexAMDX_placeholder                = nullptr;
      PFN_dummy vkCmdInitializeGraphScratchMemoryAMDX_placeholder                   = nullptr;
      PFN_dummy vkCmdDispatchGraphAMDX_placeholder                                  = nullptr;
      PFN_dummy vkCmdDispatchGraphIndirectAMDX_placeholder                          = nullptr;
      PFN_dummy vkCmdDispatchGraphIndirectCountAMDX_placeholder                     = nullptr;
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

    //=== VK_EXT_sample_locations ===
    PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT = nullptr;

    //=== VK_KHR_get_memory_requirements2 ===
    PFN_vkGetImageMemoryRequirements2KHR       vkGetImageMemoryRequirements2KHR       = nullptr;
    PFN_vkGetBufferMemoryRequirements2KHR      vkGetBufferMemoryRequirements2KHR      = nullptr;
    PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR = nullptr;

    //=== VK_KHR_acceleration_structure ===
    PFN_vkCreateAccelerationStructureKHR                 vkCreateAccelerationStructureKHR                 = nullptr;
    PFN_vkDestroyAccelerationStructureKHR                vkDestroyAccelerationStructureKHR                = nullptr;
    PFN_vkCmdBuildAccelerationStructuresKHR              vkCmdBuildAccelerationStructuresKHR              = nullptr;
    PFN_vkCmdBuildAccelerationStructuresIndirectKHR      vkCmdBuildAccelerationStructuresIndirectKHR      = nullptr;
    PFN_vkBuildAccelerationStructuresKHR                 vkBuildAccelerationStructuresKHR                 = nullptr;
    PFN_vkCopyAccelerationStructureKHR                   vkCopyAccelerationStructureKHR                   = nullptr;
    PFN_vkCopyAccelerationStructureToMemoryKHR           vkCopyAccelerationStructureToMemoryKHR           = nullptr;
    PFN_vkCopyMemoryToAccelerationStructureKHR           vkCopyMemoryToAccelerationStructureKHR           = nullptr;
    PFN_vkWriteAccelerationStructuresPropertiesKHR       vkWriteAccelerationStructuresPropertiesKHR       = nullptr;
    PFN_vkCmdCopyAccelerationStructureKHR                vkCmdCopyAccelerationStructureKHR                = nullptr;
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR        vkCmdCopyAccelerationStructureToMemoryKHR        = nullptr;
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR        vkCmdCopyMemoryToAccelerationStructureKHR        = nullptr;
    PFN_vkGetAccelerationStructureDeviceAddressKHR       vkGetAccelerationStructureDeviceAddressKHR       = nullptr;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR    vkCmdWriteAccelerationStructuresPropertiesKHR    = nullptr;
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR = nullptr;
    PFN_vkGetAccelerationStructureBuildSizesKHR          vkGetAccelerationStructureBuildSizesKHR          = nullptr;

    //=== VK_KHR_ray_tracing_pipeline ===
    PFN_vkCmdTraceRaysKHR                                 vkCmdTraceRaysKHR                                 = nullptr;
    PFN_vkCreateRayTracingPipelinesKHR                    vkCreateRayTracingPipelinesKHR                    = nullptr;
    PFN_vkGetRayTracingShaderGroupHandlesKHR              vkGetRayTracingShaderGroupHandlesKHR              = nullptr;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = nullptr;
    PFN_vkCmdTraceRaysIndirectKHR                         vkCmdTraceRaysIndirectKHR                         = nullptr;
    PFN_vkGetRayTracingShaderGroupStackSizeKHR            vkGetRayTracingShaderGroupStackSizeKHR            = nullptr;
    PFN_vkCmdSetRayTracingPipelineStackSizeKHR            vkCmdSetRayTracingPipelineStackSizeKHR            = nullptr;

    //=== VK_KHR_sampler_ycbcr_conversion ===
    PFN_vkCreateSamplerYcbcrConversionKHR  vkCreateSamplerYcbcrConversionKHR  = nullptr;
    PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR = nullptr;

    //=== VK_KHR_bind_memory2 ===
    PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR = nullptr;
    PFN_vkBindImageMemory2KHR  vkBindImageMemory2KHR  = nullptr;

    //=== VK_EXT_image_drm_format_modifier ===
    PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT = nullptr;

    //=== VK_EXT_validation_cache ===
    PFN_vkCreateValidationCacheEXT  vkCreateValidationCacheEXT  = nullptr;
    PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT = nullptr;
    PFN_vkMergeValidationCachesEXT  vkMergeValidationCachesEXT  = nullptr;
    PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT = nullptr;

    //=== VK_NV_shading_rate_image ===
    PFN_vkCmdBindShadingRateImageNV          vkCmdBindShadingRateImageNV          = nullptr;
    PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV = nullptr;
    PFN_vkCmdSetCoarseSampleOrderNV          vkCmdSetCoarseSampleOrderNV          = nullptr;

    //=== VK_NV_ray_tracing ===
    PFN_vkCreateAccelerationStructureNV                vkCreateAccelerationStructureNV                = nullptr;
    PFN_vkDestroyAccelerationStructureNV               vkDestroyAccelerationStructureNV               = nullptr;
    PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV = nullptr;
    PFN_vkBindAccelerationStructureMemoryNV            vkBindAccelerationStructureMemoryNV            = nullptr;
    PFN_vkCmdBuildAccelerationStructureNV              vkCmdBuildAccelerationStructureNV              = nullptr;
    PFN_vkCmdCopyAccelerationStructureNV               vkCmdCopyAccelerationStructureNV               = nullptr;
    PFN_vkCmdTraceRaysNV                               vkCmdTraceRaysNV                               = nullptr;
    PFN_vkCreateRayTracingPipelinesNV                  vkCreateRayTracingPipelinesNV                  = nullptr;
    PFN_vkGetRayTracingShaderGroupHandlesNV            vkGetRayTracingShaderGroupHandlesNV            = nullptr;
    PFN_vkGetAccelerationStructureHandleNV             vkGetAccelerationStructureHandleNV             = nullptr;
    PFN_vkCmdWriteAccelerationStructuresPropertiesNV   vkCmdWriteAccelerationStructuresPropertiesNV   = nullptr;
    PFN_vkCompileDeferredNV                            vkCompileDeferredNV                            = nullptr;

    //=== VK_KHR_maintenance3 ===
    PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR = nullptr;

    //=== VK_KHR_draw_indirect_count ===
    PFN_vkCmdDrawIndirectCountKHR        vkCmdDrawIndirectCountKHR        = nullptr;
    PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR = nullptr;

    //=== VK_EXT_external_memory_host ===
    PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT = nullptr;

    //=== VK_AMD_buffer_marker ===
    PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD = nullptr;

    //=== VK_EXT_calibrated_timestamps ===
    PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT = nullptr;

    //=== VK_NV_mesh_shader ===
    PFN_vkCmdDrawMeshTasksNV              vkCmdDrawMeshTasksNV              = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectNV      vkCmdDrawMeshTasksIndirectNV      = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV = nullptr;

    //=== VK_NV_scissor_exclusive ===
    PFN_vkCmdSetExclusiveScissorEnableNV vkCmdSetExclusiveScissorEnableNV = nullptr;
    PFN_vkCmdSetExclusiveScissorNV       vkCmdSetExclusiveScissorNV       = nullptr;

    //=== VK_NV_device_diagnostic_checkpoints ===
    PFN_vkCmdSetCheckpointNV       vkCmdSetCheckpointNV       = nullptr;
    PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV = nullptr;

    //=== VK_KHR_timeline_semaphore ===
    PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR = nullptr;
    PFN_vkWaitSemaphoresKHR           vkWaitSemaphoresKHR           = nullptr;
    PFN_vkSignalSemaphoreKHR          vkSignalSemaphoreKHR          = nullptr;

    //=== VK_INTEL_performance_query ===
    PFN_vkInitializePerformanceApiINTEL         vkInitializePerformanceApiINTEL         = nullptr;
    PFN_vkUninitializePerformanceApiINTEL       vkUninitializePerformanceApiINTEL       = nullptr;
    PFN_vkCmdSetPerformanceMarkerINTEL          vkCmdSetPerformanceMarkerINTEL          = nullptr;
    PFN_vkCmdSetPerformanceStreamMarkerINTEL    vkCmdSetPerformanceStreamMarkerINTEL    = nullptr;
    PFN_vkCmdSetPerformanceOverrideINTEL        vkCmdSetPerformanceOverrideINTEL        = nullptr;
    PFN_vkAcquirePerformanceConfigurationINTEL  vkAcquirePerformanceConfigurationINTEL  = nullptr;
    PFN_vkReleasePerformanceConfigurationINTEL  vkReleasePerformanceConfigurationINTEL  = nullptr;
    PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL = nullptr;
    PFN_vkGetPerformanceParameterINTEL          vkGetPerformanceParameterINTEL          = nullptr;

    //=== VK_AMD_display_native_hdr ===
    PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD = nullptr;

    //=== VK_KHR_fragment_shading_rate ===
    PFN_vkCmdSetFragmentShadingRateKHR vkCmdSetFragmentShadingRateKHR = nullptr;

    //=== VK_EXT_buffer_device_address ===
    PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT = nullptr;

    //=== VK_KHR_present_wait ===
    PFN_vkWaitForPresentKHR vkWaitForPresentKHR = nullptr;

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
    //=== VK_EXT_full_screen_exclusive ===
      PFN_vkAcquireFullScreenExclusiveModeEXT     vkAcquireFullScreenExclusiveModeEXT     = nullptr;
      PFN_vkReleaseFullScreenExclusiveModeEXT     vkReleaseFullScreenExclusiveModeEXT     = nullptr;
      PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT = nullptr;
#  else
    PFN_dummy vkAcquireFullScreenExclusiveModeEXT_placeholder                     = nullptr;
    PFN_dummy vkReleaseFullScreenExclusiveModeEXT_placeholder                     = nullptr;
    PFN_dummy vkGetDeviceGroupSurfacePresentModes2EXT_placeholder                 = nullptr;
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

    //=== VK_KHR_buffer_device_address ===
    PFN_vkGetBufferDeviceAddressKHR              vkGetBufferDeviceAddressKHR              = nullptr;
    PFN_vkGetBufferOpaqueCaptureAddressKHR       vkGetBufferOpaqueCaptureAddressKHR       = nullptr;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR = nullptr;

    //=== VK_EXT_line_rasterization ===
    PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT = nullptr;

    //=== VK_EXT_host_query_reset ===
    PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT = nullptr;

    //=== VK_EXT_extended_dynamic_state ===
    PFN_vkCmdSetCullModeEXT              vkCmdSetCullModeEXT              = nullptr;
    PFN_vkCmdSetFrontFaceEXT             vkCmdSetFrontFaceEXT             = nullptr;
    PFN_vkCmdSetPrimitiveTopologyEXT     vkCmdSetPrimitiveTopologyEXT     = nullptr;
    PFN_vkCmdSetViewportWithCountEXT     vkCmdSetViewportWithCountEXT     = nullptr;
    PFN_vkCmdSetScissorWithCountEXT      vkCmdSetScissorWithCountEXT      = nullptr;
    PFN_vkCmdBindVertexBuffers2EXT       vkCmdBindVertexBuffers2EXT       = nullptr;
    PFN_vkCmdSetDepthTestEnableEXT       vkCmdSetDepthTestEnableEXT       = nullptr;
    PFN_vkCmdSetDepthWriteEnableEXT      vkCmdSetDepthWriteEnableEXT      = nullptr;
    PFN_vkCmdSetDepthCompareOpEXT        vkCmdSetDepthCompareOpEXT        = nullptr;
    PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT = nullptr;
    PFN_vkCmdSetStencilTestEnableEXT     vkCmdSetStencilTestEnableEXT     = nullptr;
    PFN_vkCmdSetStencilOpEXT             vkCmdSetStencilOpEXT             = nullptr;

    //=== VK_KHR_deferred_host_operations ===
    PFN_vkCreateDeferredOperationKHR            vkCreateDeferredOperationKHR            = nullptr;
    PFN_vkDestroyDeferredOperationKHR           vkDestroyDeferredOperationKHR           = nullptr;
    PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR = nullptr;
    PFN_vkGetDeferredOperationResultKHR         vkGetDeferredOperationResultKHR         = nullptr;
    PFN_vkDeferredOperationJoinKHR              vkDeferredOperationJoinKHR              = nullptr;

    //=== VK_KHR_pipeline_executable_properties ===
    PFN_vkGetPipelineExecutablePropertiesKHR              vkGetPipelineExecutablePropertiesKHR              = nullptr;
    PFN_vkGetPipelineExecutableStatisticsKHR              vkGetPipelineExecutableStatisticsKHR              = nullptr;
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR = nullptr;

    //=== VK_EXT_host_image_copy ===
    PFN_vkCopyMemoryToImageEXT          vkCopyMemoryToImageEXT          = nullptr;
    PFN_vkCopyImageToMemoryEXT          vkCopyImageToMemoryEXT          = nullptr;
    PFN_vkCopyImageToImageEXT           vkCopyImageToImageEXT           = nullptr;
    PFN_vkTransitionImageLayoutEXT      vkTransitionImageLayoutEXT      = nullptr;
    PFN_vkGetImageSubresourceLayout2EXT vkGetImageSubresourceLayout2EXT = nullptr;

    //=== VK_KHR_map_memory2 ===
    PFN_vkMapMemory2KHR   vkMapMemory2KHR   = nullptr;
    PFN_vkUnmapMemory2KHR vkUnmapMemory2KHR = nullptr;

    //=== VK_EXT_swapchain_maintenance1 ===
    PFN_vkReleaseSwapchainImagesEXT vkReleaseSwapchainImagesEXT = nullptr;

    //=== VK_NV_device_generated_commands ===
    PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV = nullptr;
    PFN_vkCmdPreprocessGeneratedCommandsNV         vkCmdPreprocessGeneratedCommandsNV         = nullptr;
    PFN_vkCmdExecuteGeneratedCommandsNV            vkCmdExecuteGeneratedCommandsNV            = nullptr;
    PFN_vkCmdBindPipelineShaderGroupNV             vkCmdBindPipelineShaderGroupNV             = nullptr;
    PFN_vkCreateIndirectCommandsLayoutNV           vkCreateIndirectCommandsLayoutNV           = nullptr;
    PFN_vkDestroyIndirectCommandsLayoutNV          vkDestroyIndirectCommandsLayoutNV          = nullptr;

    //=== VK_EXT_depth_bias_control ===
    PFN_vkCmdSetDepthBias2EXT vkCmdSetDepthBias2EXT = nullptr;

    //=== VK_EXT_private_data ===
    PFN_vkCreatePrivateDataSlotEXT  vkCreatePrivateDataSlotEXT  = nullptr;
    PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT = nullptr;
    PFN_vkSetPrivateDataEXT         vkSetPrivateDataEXT         = nullptr;
    PFN_vkGetPrivateDataEXT         vkGetPrivateDataEXT         = nullptr;

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
    //=== VK_KHR_video_encode_queue ===
    PFN_vkGetEncodedVideoSessionParametersKHR vkGetEncodedVideoSessionParametersKHR = nullptr;
    PFN_vkCmdEncodeVideoKHR                   vkCmdEncodeVideoKHR                   = nullptr;
#  else
    PFN_dummy vkGetEncodedVideoSessionParametersKHR_placeholder                   = nullptr;
      PFN_dummy vkCmdEncodeVideoKHR_placeholder                                     = nullptr;
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

#  if defined( VK_USE_PLATFORM_METAL_EXT )
    //=== VK_EXT_metal_objects ===
      PFN_vkExportMetalObjectsEXT vkExportMetalObjectsEXT = nullptr;
#  else
    PFN_dummy vkExportMetalObjectsEXT_placeholder                                 = nullptr;
#  endif /*VK_USE_PLATFORM_METAL_EXT*/

    //=== VK_KHR_synchronization2 ===
    PFN_vkCmdSetEvent2KHR           vkCmdSetEvent2KHR           = nullptr;
    PFN_vkCmdResetEvent2KHR         vkCmdResetEvent2KHR         = nullptr;
    PFN_vkCmdWaitEvents2KHR         vkCmdWaitEvents2KHR         = nullptr;
    PFN_vkCmdPipelineBarrier2KHR    vkCmdPipelineBarrier2KHR    = nullptr;
    PFN_vkCmdWriteTimestamp2KHR     vkCmdWriteTimestamp2KHR     = nullptr;
    PFN_vkQueueSubmit2KHR           vkQueueSubmit2KHR           = nullptr;
    PFN_vkCmdWriteBufferMarker2AMD  vkCmdWriteBufferMarker2AMD  = nullptr;
    PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV = nullptr;

    //=== VK_EXT_descriptor_buffer ===
    PFN_vkGetDescriptorSetLayoutSizeEXT                          vkGetDescriptorSetLayoutSizeEXT                          = nullptr;
    PFN_vkGetDescriptorSetLayoutBindingOffsetEXT                 vkGetDescriptorSetLayoutBindingOffsetEXT                 = nullptr;
    PFN_vkGetDescriptorEXT                                       vkGetDescriptorEXT                                       = nullptr;
    PFN_vkCmdBindDescriptorBuffersEXT                            vkCmdBindDescriptorBuffersEXT                            = nullptr;
    PFN_vkCmdSetDescriptorBufferOffsetsEXT                       vkCmdSetDescriptorBufferOffsetsEXT                       = nullptr;
    PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT             vkCmdBindDescriptorBufferEmbeddedSamplersEXT             = nullptr;
    PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT                vkGetBufferOpaqueCaptureDescriptorDataEXT                = nullptr;
    PFN_vkGetImageOpaqueCaptureDescriptorDataEXT                 vkGetImageOpaqueCaptureDescriptorDataEXT                 = nullptr;
    PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT             vkGetImageViewOpaqueCaptureDescriptorDataEXT             = nullptr;
    PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT               vkGetSamplerOpaqueCaptureDescriptorDataEXT               = nullptr;
    PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = nullptr;

    //=== VK_NV_fragment_shading_rate_enums ===
    PFN_vkCmdSetFragmentShadingRateEnumNV vkCmdSetFragmentShadingRateEnumNV = nullptr;

    //=== VK_EXT_mesh_shader ===
    PFN_vkCmdDrawMeshTasksEXT              vkCmdDrawMeshTasksEXT              = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectEXT      vkCmdDrawMeshTasksIndirectEXT      = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT = nullptr;

    //=== VK_KHR_copy_commands2 ===
    PFN_vkCmdCopyBuffer2KHR        vkCmdCopyBuffer2KHR        = nullptr;
    PFN_vkCmdCopyImage2KHR         vkCmdCopyImage2KHR         = nullptr;
    PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR = nullptr;
    PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR = nullptr;
    PFN_vkCmdBlitImage2KHR         vkCmdBlitImage2KHR         = nullptr;
    PFN_vkCmdResolveImage2KHR      vkCmdResolveImage2KHR      = nullptr;

    //=== VK_EXT_device_fault ===
    PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT = nullptr;

    //=== VK_EXT_vertex_input_dynamic_state ===
    PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT = nullptr;

#  if defined( VK_USE_PLATFORM_FUCHSIA )
    //=== VK_FUCHSIA_external_memory ===
      PFN_vkGetMemoryZirconHandleFUCHSIA           vkGetMemoryZirconHandleFUCHSIA           = nullptr;
      PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA vkGetMemoryZirconHandlePropertiesFUCHSIA = nullptr;
#  else
    PFN_dummy vkGetMemoryZirconHandleFUCHSIA_placeholder                          = nullptr;
    PFN_dummy vkGetMemoryZirconHandlePropertiesFUCHSIA_placeholder                = nullptr;
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

#  if defined( VK_USE_PLATFORM_FUCHSIA )
    //=== VK_FUCHSIA_external_semaphore ===
      PFN_vkImportSemaphoreZirconHandleFUCHSIA vkImportSemaphoreZirconHandleFUCHSIA = nullptr;
      PFN_vkGetSemaphoreZirconHandleFUCHSIA    vkGetSemaphoreZirconHandleFUCHSIA    = nullptr;
#  else
    PFN_dummy vkImportSemaphoreZirconHandleFUCHSIA_placeholder                    = nullptr;
    PFN_dummy vkGetSemaphoreZirconHandleFUCHSIA_placeholder                       = nullptr;
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

#  if defined( VK_USE_PLATFORM_FUCHSIA )
    //=== VK_FUCHSIA_buffer_collection ===
      PFN_vkCreateBufferCollectionFUCHSIA               vkCreateBufferCollectionFUCHSIA               = nullptr;
      PFN_vkSetBufferCollectionImageConstraintsFUCHSIA  vkSetBufferCollectionImageConstraintsFUCHSIA  = nullptr;
      PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA vkSetBufferCollectionBufferConstraintsFUCHSIA = nullptr;
      PFN_vkDestroyBufferCollectionFUCHSIA              vkDestroyBufferCollectionFUCHSIA              = nullptr;
      PFN_vkGetBufferCollectionPropertiesFUCHSIA        vkGetBufferCollectionPropertiesFUCHSIA        = nullptr;
#  else
    PFN_dummy vkCreateBufferCollectionFUCHSIA_placeholder                         = nullptr;
    PFN_dummy vkSetBufferCollectionImageConstraintsFUCHSIA_placeholder            = nullptr;
    PFN_dummy vkSetBufferCollectionBufferConstraintsFUCHSIA_placeholder           = nullptr;
    PFN_dummy vkDestroyBufferCollectionFUCHSIA_placeholder                        = nullptr;
    PFN_dummy vkGetBufferCollectionPropertiesFUCHSIA_placeholder                  = nullptr;
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

    //=== VK_HUAWEI_subpass_shading ===
    PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = nullptr;
    PFN_vkCmdSubpassShadingHUAWEI                       vkCmdSubpassShadingHUAWEI                       = nullptr;

    //=== VK_HUAWEI_invocation_mask ===
    PFN_vkCmdBindInvocationMaskHUAWEI vkCmdBindInvocationMaskHUAWEI = nullptr;

    //=== VK_NV_external_memory_rdma ===
    PFN_vkGetMemoryRemoteAddressNV vkGetMemoryRemoteAddressNV = nullptr;

    //=== VK_EXT_pipeline_properties ===
    PFN_vkGetPipelinePropertiesEXT vkGetPipelinePropertiesEXT = nullptr;

    //=== VK_EXT_extended_dynamic_state2 ===
    PFN_vkCmdSetPatchControlPointsEXT      vkCmdSetPatchControlPointsEXT      = nullptr;
    PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT = nullptr;
    PFN_vkCmdSetDepthBiasEnableEXT         vkCmdSetDepthBiasEnableEXT         = nullptr;
    PFN_vkCmdSetLogicOpEXT                 vkCmdSetLogicOpEXT                 = nullptr;
    PFN_vkCmdSetPrimitiveRestartEnableEXT  vkCmdSetPrimitiveRestartEnableEXT  = nullptr;

    //=== VK_EXT_color_write_enable ===
    PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT = nullptr;

    //=== VK_KHR_ray_tracing_maintenance1 ===
    PFN_vkCmdTraceRaysIndirect2KHR vkCmdTraceRaysIndirect2KHR = nullptr;

    //=== VK_EXT_multi_draw ===
    PFN_vkCmdDrawMultiEXT        vkCmdDrawMultiEXT        = nullptr;
    PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT = nullptr;

    //=== VK_EXT_opacity_micromap ===
    PFN_vkCreateMicromapEXT                 vkCreateMicromapEXT                 = nullptr;
    PFN_vkDestroyMicromapEXT                vkDestroyMicromapEXT                = nullptr;
    PFN_vkCmdBuildMicromapsEXT              vkCmdBuildMicromapsEXT              = nullptr;
    PFN_vkBuildMicromapsEXT                 vkBuildMicromapsEXT                 = nullptr;
    PFN_vkCopyMicromapEXT                   vkCopyMicromapEXT                   = nullptr;
    PFN_vkCopyMicromapToMemoryEXT           vkCopyMicromapToMemoryEXT           = nullptr;
    PFN_vkCopyMemoryToMicromapEXT           vkCopyMemoryToMicromapEXT           = nullptr;
    PFN_vkWriteMicromapsPropertiesEXT       vkWriteMicromapsPropertiesEXT       = nullptr;
    PFN_vkCmdCopyMicromapEXT                vkCmdCopyMicromapEXT                = nullptr;
    PFN_vkCmdCopyMicromapToMemoryEXT        vkCmdCopyMicromapToMemoryEXT        = nullptr;
    PFN_vkCmdCopyMemoryToMicromapEXT        vkCmdCopyMemoryToMicromapEXT        = nullptr;
    PFN_vkCmdWriteMicromapsPropertiesEXT    vkCmdWriteMicromapsPropertiesEXT    = nullptr;
    PFN_vkGetDeviceMicromapCompatibilityEXT vkGetDeviceMicromapCompatibilityEXT = nullptr;
    PFN_vkGetMicromapBuildSizesEXT          vkGetMicromapBuildSizesEXT          = nullptr;

    //=== VK_HUAWEI_cluster_culling_shader ===
    PFN_vkCmdDrawClusterHUAWEI         vkCmdDrawClusterHUAWEI         = nullptr;
    PFN_vkCmdDrawClusterIndirectHUAWEI vkCmdDrawClusterIndirectHUAWEI = nullptr;

    //=== VK_EXT_pageable_device_local_memory ===
    PFN_vkSetDeviceMemoryPriorityEXT vkSetDeviceMemoryPriorityEXT = nullptr;

    //=== VK_KHR_maintenance4 ===
    PFN_vkGetDeviceBufferMemoryRequirementsKHR      vkGetDeviceBufferMemoryRequirementsKHR      = nullptr;
    PFN_vkGetDeviceImageMemoryRequirementsKHR       vkGetDeviceImageMemoryRequirementsKHR       = nullptr;
    PFN_vkGetDeviceImageSparseMemoryRequirementsKHR vkGetDeviceImageSparseMemoryRequirementsKHR = nullptr;

    //=== VK_VALVE_descriptor_set_host_mapping ===
    PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE vkGetDescriptorSetLayoutHostMappingInfoVALVE = nullptr;
    PFN_vkGetDescriptorSetHostMappingVALVE           vkGetDescriptorSetHostMappingVALVE           = nullptr;

    //=== VK_NV_copy_memory_indirect ===
    PFN_vkCmdCopyMemoryIndirectNV        vkCmdCopyMemoryIndirectNV        = nullptr;
    PFN_vkCmdCopyMemoryToImageIndirectNV vkCmdCopyMemoryToImageIndirectNV = nullptr;

    //=== VK_NV_memory_decompression ===
    PFN_vkCmdDecompressMemoryNV              vkCmdDecompressMemoryNV              = nullptr;
    PFN_vkCmdDecompressMemoryIndirectCountNV vkCmdDecompressMemoryIndirectCountNV = nullptr;

    //=== VK_NV_device_generated_commands_compute ===
    PFN_vkGetPipelineIndirectMemoryRequirementsNV vkGetPipelineIndirectMemoryRequirementsNV = nullptr;
    PFN_vkCmdUpdatePipelineIndirectBufferNV       vkCmdUpdatePipelineIndirectBufferNV       = nullptr;
    PFN_vkGetPipelineIndirectDeviceAddressNV      vkGetPipelineIndirectDeviceAddressNV      = nullptr;

    //=== VK_EXT_extended_dynamic_state3 ===
    PFN_vkCmdSetTessellationDomainOriginEXT         vkCmdSetTessellationDomainOriginEXT         = nullptr;
    PFN_vkCmdSetDepthClampEnableEXT                 vkCmdSetDepthClampEnableEXT                 = nullptr;
    PFN_vkCmdSetPolygonModeEXT                      vkCmdSetPolygonModeEXT                      = nullptr;
    PFN_vkCmdSetRasterizationSamplesEXT             vkCmdSetRasterizationSamplesEXT             = nullptr;
    PFN_vkCmdSetSampleMaskEXT                       vkCmdSetSampleMaskEXT                       = nullptr;
    PFN_vkCmdSetAlphaToCoverageEnableEXT            vkCmdSetAlphaToCoverageEnableEXT            = nullptr;
    PFN_vkCmdSetAlphaToOneEnableEXT                 vkCmdSetAlphaToOneEnableEXT                 = nullptr;
    PFN_vkCmdSetLogicOpEnableEXT                    vkCmdSetLogicOpEnableEXT                    = nullptr;
    PFN_vkCmdSetColorBlendEnableEXT                 vkCmdSetColorBlendEnableEXT                 = nullptr;
    PFN_vkCmdSetColorBlendEquationEXT               vkCmdSetColorBlendEquationEXT               = nullptr;
    PFN_vkCmdSetColorWriteMaskEXT                   vkCmdSetColorWriteMaskEXT                   = nullptr;
    PFN_vkCmdSetRasterizationStreamEXT              vkCmdSetRasterizationStreamEXT              = nullptr;
    PFN_vkCmdSetConservativeRasterizationModeEXT    vkCmdSetConservativeRasterizationModeEXT    = nullptr;
    PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT vkCmdSetExtraPrimitiveOverestimationSizeEXT = nullptr;
    PFN_vkCmdSetDepthClipEnableEXT                  vkCmdSetDepthClipEnableEXT                  = nullptr;
    PFN_vkCmdSetSampleLocationsEnableEXT            vkCmdSetSampleLocationsEnableEXT            = nullptr;
    PFN_vkCmdSetColorBlendAdvancedEXT               vkCmdSetColorBlendAdvancedEXT               = nullptr;
    PFN_vkCmdSetProvokingVertexModeEXT              vkCmdSetProvokingVertexModeEXT              = nullptr;
    PFN_vkCmdSetLineRasterizationModeEXT            vkCmdSetLineRasterizationModeEXT            = nullptr;
    PFN_vkCmdSetLineStippleEnableEXT                vkCmdSetLineStippleEnableEXT                = nullptr;
    PFN_vkCmdSetDepthClipNegativeOneToOneEXT        vkCmdSetDepthClipNegativeOneToOneEXT        = nullptr;
    PFN_vkCmdSetViewportWScalingEnableNV            vkCmdSetViewportWScalingEnableNV            = nullptr;
    PFN_vkCmdSetViewportSwizzleNV                   vkCmdSetViewportSwizzleNV                   = nullptr;
    PFN_vkCmdSetCoverageToColorEnableNV             vkCmdSetCoverageToColorEnableNV             = nullptr;
    PFN_vkCmdSetCoverageToColorLocationNV           vkCmdSetCoverageToColorLocationNV           = nullptr;
    PFN_vkCmdSetCoverageModulationModeNV            vkCmdSetCoverageModulationModeNV            = nullptr;
    PFN_vkCmdSetCoverageModulationTableEnableNV     vkCmdSetCoverageModulationTableEnableNV     = nullptr;
    PFN_vkCmdSetCoverageModulationTableNV           vkCmdSetCoverageModulationTableNV           = nullptr;
    PFN_vkCmdSetShadingRateImageEnableNV            vkCmdSetShadingRateImageEnableNV            = nullptr;
    PFN_vkCmdSetRepresentativeFragmentTestEnableNV  vkCmdSetRepresentativeFragmentTestEnableNV  = nullptr;
    PFN_vkCmdSetCoverageReductionModeNV             vkCmdSetCoverageReductionModeNV             = nullptr;

    //=== VK_EXT_shader_module_identifier ===
    PFN_vkGetShaderModuleIdentifierEXT           vkGetShaderModuleIdentifierEXT           = nullptr;
    PFN_vkGetShaderModuleCreateInfoIdentifierEXT vkGetShaderModuleCreateInfoIdentifierEXT = nullptr;

    //=== VK_NV_optical_flow ===
    PFN_vkCreateOpticalFlowSessionNV    vkCreateOpticalFlowSessionNV    = nullptr;
    PFN_vkDestroyOpticalFlowSessionNV   vkDestroyOpticalFlowSessionNV   = nullptr;
    PFN_vkBindOpticalFlowSessionImageNV vkBindOpticalFlowSessionImageNV = nullptr;
    PFN_vkCmdOpticalFlowExecuteNV       vkCmdOpticalFlowExecuteNV       = nullptr;

    //=== VK_KHR_maintenance5 ===
    PFN_vkCmdBindIndexBuffer2KHR             vkCmdBindIndexBuffer2KHR             = nullptr;
    PFN_vkGetRenderingAreaGranularityKHR     vkGetRenderingAreaGranularityKHR     = nullptr;
    PFN_vkGetDeviceImageSubresourceLayoutKHR vkGetDeviceImageSubresourceLayoutKHR = nullptr;
    PFN_vkGetImageSubresourceLayout2KHR      vkGetImageSubresourceLayout2KHR      = nullptr;

    //=== VK_EXT_shader_object ===
    PFN_vkCreateShadersEXT       vkCreateShadersEXT       = nullptr;
    PFN_vkDestroyShaderEXT       vkDestroyShaderEXT       = nullptr;
    PFN_vkGetShaderBinaryDataEXT vkGetShaderBinaryDataEXT = nullptr;
    PFN_vkCmdBindShadersEXT      vkCmdBindShadersEXT      = nullptr;

    //=== VK_QCOM_tile_properties ===
    PFN_vkGetFramebufferTilePropertiesQCOM      vkGetFramebufferTilePropertiesQCOM      = nullptr;
    PFN_vkGetDynamicRenderingTilePropertiesQCOM vkGetDynamicRenderingTilePropertiesQCOM = nullptr;

    //=== VK_EXT_attachment_feedback_loop_dynamic_state ===
    PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT vkCmdSetAttachmentFeedbackLoopEnableEXT = nullptr;

#  if defined( VK_USE_PLATFORM_SCREEN_QNX )
    //=== VK_QNX_external_memory_screen_buffer ===
      PFN_vkGetScreenBufferPropertiesQNX vkGetScreenBufferPropertiesQNX = nullptr;
#  else
    PFN_dummy vkGetScreenBufferPropertiesQNX_placeholder                          = nullptr;
#  endif /*VK_USE_PLATFORM_SCREEN_QNX*/
};