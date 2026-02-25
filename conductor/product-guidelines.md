# Product Guidelines: 3DSC2

## Design Philosophy
3DSC2 aims to be a high-performance, modern tool that makes 3DS capture accessible to everyone. We prioritize **stability and low latency** above all else, ensuring that the gaming experience is as close to hardware-native as possible.

## Tone & Communication
- **Friendly & Accessible:** Documentation and UI labels should be welcoming and easy to understand for non-technical users.
- **Supportive Language:** Use "We" and "Let's" to guide the user through setup and troubleshooting.
- **Clarity Over Jargon:** Explain technical terms (like ROI, TAS, or Latency) simply when they appear in the interface.

## User Experience (UX)
- **Performance First:** Every UI interaction or background process must be optimized to prevent frame drops in the video stream.
- **Low-Latency Feedback:** Input redirection should feel instantaneous. Visual feedback for button presses on the PC should match the console's reaction.
- **Stable Scaffolding:** Prevent crashes by validating inputs (IP addresses, camera indices) before attempting to start heavy processes like video capture.

## Visual Aesthetic
- **Modern Tech Tool:** Use a clean, professional interface with a focus on usability. Avoid cluttered "gaming" overlays in favor of a sleek, high-tech dashboard.
- **Visual Consistency:** Maintain consistent spacing, typography (sans-serif), and a neutral color palette with primary action colors (e.g., green for "Start", red for "Stop").
- **Focused Viewports:** The 3DS screen windows should be distraction-free, with controls hidden in menus or the main dashboard.

## Error Handling & Reliability
- **Proactive Guidance:** When an error occurs (e.g., "3DS not found"), provide a clear explanation of *why* and a specific step the user can take to fix it.
- **Graceful Failure:** If a camera disconnects or the network drops, the app should return to a safe state rather than hanging or crashing.
- **User-Centric Alerts:** Avoid raw stack traces in the main UI. Use friendly dialog boxes for critical issues and status bar updates for minor warnings.
