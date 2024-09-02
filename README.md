# CameraApp

CameraApp is a C++ application that uses OpenCV and FFmpeg to capture video from a camera, display it in a window, and process it using **hardware acceleration**. The application also lists detailed information about available cameras using DirectShow.

## Features

- List available cameras with detailed information (name, device path, etc.)
- Capture video from a selected camera
- Display video in a window
- Set camera resolution to 4K
- Use hardware acceleration for video processing

## Prerequisites

- Windows operating system
- CMake
- Visual Studio or MinGW
- OpenCV
- FFmpeg

## Installation

### 1. Install CMake

Download and install CMake from the [CMake website](https://cmake.org/download/).

### 2. Install Visual Studio or MinGW

#### Visual Studio

Download and install Visual Studio from the [Visual Studio website](https://visualstudio.microsoft.com/). Make sure to install the "Desktop development with C++" workload.

#### MinGW

Download and install MinGW from the [MinGW website](http://www.mingw.org/). Make sure to add MinGW to your system's PATH.

### 3. Install OpenCV

1. Download the latest OpenCV release from the [OpenCV website](https://opencv.org/releases/).
2. Extract the downloaded archive to a directory, e.g., `C:/opencv`.
3. Set the `OpenCV_DIR` environment variable to the path of the OpenCV build directory, e.g., `C:/opencv/build`.

### 4. Install FFmpeg

1. Download the latest FFmpeg release from [Gyan.dev FFmpeg Builds](https://www.gyan.dev/ffmpeg/builds/).
> ⚠ Be carreful to download the full_build-**SHARED** version in the release build section ! 
2. Extract the downloaded archive to a directory, e.g., `C:/ffmpeg`.
3. Set the `FFMPEG_DIR` environment variable to the path of the FFmpeg directory, e.g., `C:/ffmpeg`.

