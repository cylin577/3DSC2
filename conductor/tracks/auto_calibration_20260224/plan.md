# Implementation Plan: Auto-Calibration System

This plan outlines the steps to refactor and solidify the auto-calibration system using Test-Driven Development.

## Phase 1: Testing Infrastructure
- [ ] Task: Setup Test Suite for Calibration Logic
- [ ] Task: Create Mock Frame Fixtures for Green Screen Detection
- [ ] Task: Conductor - User Manual Verification 'Phase 1: Testing Infrastructure' (Protocol in workflow.md)

## Phase 2: Refactor Detection Core
- [ ] Task: Refactor `find_green_rect` into a testable utility module
- [ ] Task: Write Tests for `find_green_rect` with various noise/lighting scenarios
- [ ] Task: Implement/Fix `find_green_rect` to pass all edge-case tests
- [ ] Task: Conductor - User Manual Verification 'Phase 2: Refactor Detection Core' (Protocol in workflow.md)

## Phase 3: Stability & Validation Logic
- [ ] Task: Refactor `check_stability` into a standalone validator
- [ ] Task: Write Tests for Stability Tracking (Temporal consistency and jitter handling)
- [ ] Task: Implement improved stability logic
- [ ] Task: Conductor - User Manual Verification 'Phase 3: Stability & Validation Logic' (Protocol in workflow.md)

## Phase 4: Integration & Visuals
- [ ] Task: Integrate refactored logic into `AppWindow` and `CalibrationManager`
- [ ] Task: Implement improved real-time visual debugging overlays (Drawing candidate boxes and stability counters)
- [ ] Task: Verify calibration flow with live camera stream/IP camera
- [ ] Task: Conductor - User Manual Verification 'Phase 4: Integration & Visuals' (Protocol in workflow.md)
