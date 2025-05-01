#ifndef REAITYSCENES_EY_SHARED_H
#define REAITYSCENES_EY_SHARED_H

struct SwapchainInfo {
    XrSwapchain swapchain = XR_NULL_HANDLE;
    int64_t swapchainFormat = 0;
    std::vector<void *> imageViews;
};


#endif //REAITYSCENES_EY_SHARED_H

