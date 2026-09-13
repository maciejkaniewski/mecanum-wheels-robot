# mecanum-wheels-robot

mecanum-wheels-robot is a project I realized with [Dawid Rogaliński](https://github.com/dawidrogalinski) in the sixth semester of my studies within the Mobile Robots course at the Wroclaw University of Technology in the field of Control Engineering and Robotics. The main goal of this project was to create a mobile robot that would be controlled by means of wireless communication, and more specifically the Bluetooth standard. The control was carried out via the mobile application for the Android platform. The robot is equipped with four distance sensors that limit the possibility of running into an obstacle.

<br />
<br />

<p align="center">
  <img src="https://github.com/maciejkaniewski/mecanum-wheels-robot/blob/main/images/mobile_robot_no_bg.png?raw=true" alt="Mobile Robot"/>
</p>

[Final result of the project on YouTube](https://www.youtube.com/watch?v=4yvmt_kOMKs&ab_channel=Kania)

## Features

- Holonomic robot, it can be steered in all directions available to it
- Bluetooth connectivity
- Control via Android application
- Obstacle detection in four driving directions

## Setup
Prerequisites:

- Installed [DFRobot_MotorStepper](https://github.com/DFRobot/DFRobot_MotorStepper) library
- Installed  [NewPing](https://bitbucket.org/teckel12/arduino-new-ping/src/master/) library
