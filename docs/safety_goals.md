# HARA: Hazard Analysis and Risk Assessment

## 1. Hazard Identification
| ID | Hazard Description | Situation | Malfunction |
| :--- | :--- | :--- | :--- |
| HZ_01 | Rear-end collision with lead vehicle | Highway driving | No braking despite obstacle |

## 2. Risk Assessment (ISO 26262)
| Severity (S) | Exposure (E) | Controllability (C) | ASIL Rating |
| :--- | :--- | :--- | :--- |
| S3 (Fatal) | E4 (Common) | C3 (Uncontrollable) | **ASIL D** |

## 3. Functional Safety Requirements (FSR)
These requirements must be met by the software nodes.

- **FSR_01 (Latent Faults):** The sensor fusion node shall detect sensor timeout within 50ms.
- **FSR_02 (Performance):** The AEB logic shall trigger a brake command if TTC < 1.5s.
- **FSR_03 (Accuracy):** The EKF shall maintain a position error of < 0.5m for obstacles within 30m.
