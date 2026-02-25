# Tech Stack: 3DSC2

## Core Language & Runtime
- **Python (>= 3.10):** The primary programming language for the app.
- **uv:** Fast and reliable Python dependency management.

## GUI & Display
- **PyQt6:** The main framework for building the application's desktop interface and handling video windows.

## Video Processing
- **OpenCV (opencv-python):** Used for camera capture, real-time ROI extraction, and image processing.
- **NumPy:** Essential for high-performance matrix and image data manipulation.

## Input Handling
- **Pygame:** Detects and processes physical gamepad and controller inputs.

## AI & Computer Vision
- **PyTorch (torch):** Powers advanced AI features such as Super-Resolution and image stabilization.
- **Torchvision:** Utility library for image transformations and model management.

## Networking
- **UDP (Luma3DS Protocol):** Direct network communication on port 4950 for input redirection.
