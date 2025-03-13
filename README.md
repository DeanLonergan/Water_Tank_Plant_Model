# Water Tank Plant Model

<img width="600" alt="dynamic_model_1" src="https://github.com/user-attachments/assets/74757c8d-c840-42ca-9703-a1b49c5d86c3" />

## Overview

I created this project during my fifth semester of Applied Computing, as part of the Model-Based Development module. We were required to design a model of a water tank that could be filled, leveled, and drained according to user inputs.

This involved modeling the water tank filling process and developing a control system to manage the liquid level in the tank. I built the model using **MATLAB Simulink**, utilizing a **PID controller** to regulate the water height based on user inputs. The user controls rely on a state chart developed in **MATLAB Stateflow**.

## Features
- Simulates a dynamic water tank system with controlled inflow and outflow.
- Implements a **PID Controller** for level regulation.
- Provides **user controls** for setting water height.
- Includes **real-time graphical visualization**.
- Uses **Statecharts** for intuitive control logic.

## System Model
The water tank follows this dynamic equation:

<img width="400" alt="dynamic_model_2" src="https://github.com/user-attachments/assets/b53c7792-4b5d-4260-8c1a-25aa751a5532" />

Where:
- **h** = Liquid height
- **R** = Resistance to outflow
- **A** = Tank cross-sectional area
- **Qin** = Inflow rate

### Simulation Requirements
- **PID Control** with a response time of ≈ 20s and overshoot < 10%.
- **User buttons** to control height levels (Low: 2m, Medium: 8m, High: 16m).
- **Boost Button**: Temporarily increases height by 10% for 10 seconds.
- **Empty Button**: Empties tank when held for 5 seconds.

## Controller Implementation
The PID controller is implemented and tuned using the **Ziegler-Nichols method**:

| Controller Type | \(K_p\) | \(K_i\) | \(K_d\) |
|---|---|---|---|
| P | 0.5 * \(K_{max}\) | 0 | 0 |
| PI | 0.45 * \(K_{max}\) | 1.2 * \(f_0\) | 0 |
| PID | 0.6 * \(K_{max}\) | 2.0 * \(f_0\) | 0.125 / \(f_0\) |

After preliminary tuning and manual adjustments, the system achieved near **optimal performance** with minimal overshoot.

<img width="400" alt="tuned_model" src="https://github.com/user-attachments/assets/ba11f942-9c8d-4b7b-9b9c-59e3d46db3b3" />

## User Interface & Control Logic
### User Controls:
- **Low (2m)**, **Medium (8m)**, **High (16m)** height settings.
- **Boost Button**: Increases height by 10% for 10s.
- **Empty Button**: Drains tank when pressed for 5s.

### Statechart Implementation
The control logic is designed using **Statecharts**, featuring:
- **Parallel States**: Allows simultaneous height adjustment and boost.
- **Time-Based Transitions**: Implements logical delays for **emptying** and **boosting**.

## Final Model & Verification
<img width="600" alt="water_tank_plant_model" src="https://github.com/user-attachments/assets/84c04f08-13a1-4794-b772-40c83d205144" />

- Successfully simulates a water tank filling/emptying system.
- Accurately follows user inputs and maintains desired water levels.
- Meets **design criteria** with fast response time and minimal overshoot.

## How to Run the Model
1. Open the **MATLAB Simulink** project.
2. Run the **Water_Tank_Plant_Model.slx** file.
3. Adjust water level using the **control panel**.
4. Observe real-time **graphical output**.

---
📌 *For detailed documentation, refer to the [project report](Project%20Document.pdf).*

