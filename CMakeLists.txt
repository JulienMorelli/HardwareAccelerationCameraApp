cmake_minimum_required(VERSION 3.10)
project(CameraApp)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR "C:/tools/opencv/build")

find_package(OpenCV REQUIRED)

# Set the path to your FFmpeg installation
set(FFMPEG_DIR "C:/tools/ffmpeg")

# Include FFmpeg headers
include_directories(${FFMPEG_DIR}/include)

# Add FFmpeg library directories
link_directories(${FFMPEG_DIR}/lib)

add_executable(CameraApp main.cpp)

# Link against OpenCV and FFmpeg libraries
target_link_libraries(CameraApp 
    ${OpenCV_LIBS}
    avcodec
    avformat
    avutil
    swscale
)

# Copy FFmpeg DLLs to the output directory
add_custom_command(TARGET CameraApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${FFMPEG_DIR}/bin $<TARGET_FILE_DIR:CameraApp>)

    add_custom_command(TARGET CameraApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${OpenCV_DIR}/x64/vc16/bin $<TARGET_FILE_DIR:CameraApp>)