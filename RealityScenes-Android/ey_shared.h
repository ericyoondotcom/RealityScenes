#ifndef REAITYSCENES_EY_SHARED_H
#define REAITYSCENES_EY_SHARED_H

struct SwapchainInfo {
    XrSwapchain swapchain = XR_NULL_HANDLE;
    int64_t swapchainFormat = 0;
    std::vector<void *> imageViews;
};

struct CameraConstants {
    XrMatrix4x4f viewProj;
    XrMatrix4x4f modelViewProj;
    XrMatrix4x4f model;
};

#endif //REAITYSCENES_EY_SHARED_H

