# Specification: Auto-Calibration System

## Goal
The goal of this track is to provide a robust, automated way to detect the 3DS top and bottom screens in a camera feed. This replaces the manual "click 4 corners" process and ensures a consistent view even in suboptimal lighting or camera angles.

## Requirements
1. **Automated Detection:** Detect the 3DS screens automatically when the user shows a "Green Screen" (or high-contrast calibration image) on the 3DS.
2. **Robustness:** Handle poor webcam quality, noise, and varied lighting conditions.
3. **Temporal Stability:** Ensure that the detected ROIs are stable over multiple frames before locking them in.
4. **Visual Feedback:** Provide real-time visual overlays to show the user what the computer is "seeing" during calibration.
5. **Testability:** The core detection logic must be modular and covered by unit tests.

## Technical Approach
- **Color Masking:** Use HSV color space to mask "calibration green".
- **Structural Detection:** Use Canny Edge detection as a fallback for washed-out colors.
- **Geometric Validation:** Filter candidates based on contour area, convexity, and aspect ratio (approx 5:3 or 4:3).
- **Stability Engine:** A counter-based system that requires the same region to be detected for at least 5-10 consecutive frames.

## Constraints
- Must run in real-time on the main UI thread or a dedicated worker without dropping frames.
- Must work with both local USB cameras and IP-based camera streams.
