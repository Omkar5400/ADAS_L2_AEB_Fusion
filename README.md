# ADAS L2: AEB Sensor Fusion (ISO 26262 Inspired)

## Project Overview
This project implements an Autonomous Emergency Braking (AEB) system using an 
Extended Kalman Filter (EKF) to fuse Radar and Camera data.

## Safety Goal (ASIL D)
**SG_01:** The system shall initiate emergency braking within 200ms when 
Time-to-Collision (TTC) is < 1.5s to prevent longitudinal collisions.

## Tech Stack
- **Middleware:** ROS2 Humble
- **Language:** C++17 (Fusion Logic), Python (Simulation)
- **Math Library:** Eigen 3.4
- **Testing:** GTest (Google Test)
- **Environment:** Ubuntu 22.04 (ARM64)
  
## Results
The following graph from rqt_plot shows the Kalman Filter fusing noisy Camera (Red) and Radar (Blue) data into a stable Fused state (Cyan).

![Sensor Fusion Results](docs/image (ADAS1).png)
