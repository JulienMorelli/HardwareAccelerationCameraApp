#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/hwcontext.h>
#include <libswscale/swscale.h>
}

int main() {
    std::cout << "Starting CameraApp..." << std::endl;

    // Initialize FFmpeg (no need for av_register_all or avformat_network_init)
    av_log_set_level(AV_LOG_INFO);

    // Set up hardware acceleration context
    AVBufferRef *hw_device_ctx = nullptr;
    int err = av_hwdevice_ctx_create(&hw_device_ctx, AV_HWDEVICE_TYPE_QSV, nullptr, nullptr, 0);
    if (err < 0) {
        std::cerr << "Failed to create hardware device context using QSV" << std::endl;
        return -1;
    }
    std::cout << "Hardware device context created using QSV." << std::endl;

    // Set up FFmpeg decoder
    const AVCodec *codec = avcodec_find_decoder_by_name("h264_qsv");
    if (!codec) {
        std::cerr << "Hardware accelerated codec not found" << std::endl;
        av_buffer_unref(&hw_device_ctx);
        return -1;
    }
    std::cout << "Hardware accelerated codec found." << std::endl;

    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    if (!codec_ctx) {
        std::cerr << "Failed to allocate codec context" << std::endl;
        av_buffer_unref(&hw_device_ctx);
        return -1;
    }
    std::cout << "Codec context allocated." << std::endl;

    codec_ctx->hw_device_ctx = av_buffer_ref(hw_device_ctx);

    if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
        std::cerr << "Failed to open codec" << std::endl;
        avcodec_free_context(&codec_ctx);
        av_buffer_unref(&hw_device_ctx);
        return -1;
    }
    std::cout << "Codec opened." << std::endl;

    // Camera detection code (same as before)
    std::vector<int> camera_indices;
    for (int i = 0; i < 10; ++i) {
        cv::VideoCapture cap(i);
        if (cap.isOpened()) {
            camera_indices.push_back(i);
            cap.release();
        }
    }

    // Display available cameras
    std::cout << "Available cameras:" << std::endl;
    for (size_t i = 0; i < camera_indices.size(); ++i) {
        std::cout << i << ": Camera " << camera_indices[i] << std::endl;
    }

    // Select a camera
    int selected_camera;
    std::cout << "Select a camera: ";
    std::cin >> selected_camera;

    if (selected_camera < 0 || selected_camera >= camera_indices.size()) {
        std::cerr << "Invalid camera selection." << std::endl;
        return -1;
    }

    // Open the selected camera
    cv::VideoCapture cap(camera_indices[selected_camera]);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera." << std::endl;
        return -1;
    }
    std::cout << "Camera opened." << std::endl;

    // Set camera resolution to 4K
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 3840);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 2160);
    std::cout << "Camera resolution set to 4K." << std::endl;

    // Main loop for capturing and displaying frames
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Process frame with oneVPL
        // ... (oneVPL frame processing code) ...

        cv::imshow("Camera Preview", frame);
        if (cv::waitKey(30) >= 0) break; // Exit on any key press
    }

    // Cleanup
    avcodec_free_context(&codec_ctx);
    av_buffer_unref(&hw_device_ctx);

    std::cout << "Exiting CameraApp..." << std::endl;
    return 0;
}
