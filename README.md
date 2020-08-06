State Rviz plugins
==============================================

## <img align="center" height="20" src="https://i.imgur.com/vAYeCzC.png"/> Introduction

This repository includes Rviz plugins to display the whole-body state and trajectory of a robot. These plugins use dedicated ROS messages defined in [state_msgs](https://github.com/cmastalli/state_msgs) package. To process efficiently the messages, e.g. robot display without TF broadcasting, the plugins use [Pinocchio](https://github.com/stack-of-tasks/pinocchio) library.

![output](https://user-images.githubusercontent.com/3601935/89519116-c6b45600-d7d3-11ea-89a0-fc8df97df2f0.gif)

The whole-body state plugin displays
  1. the position and velocity of Center of Mass,
  2. the contact forces,
  3. the Center of Pressure,
  4. the Instantaneous Capture Point,
  5. the friction cone, and
  6. the support polygon.

Instead, the whole-body trajectory plugin displays
 1. the Center of Mass trajectory and body orientation,
 2. the swing trajectory and its orientation, and
 3. the target posture and contact forces.

In the whole-body state plugin is possible to configure the diplay of the center of mass information in such a way that is projected in the support polygon. In both plugins, the contact forces are normalized according to the robot's weights. Furthermore, it is possible 

All visuals are configurable through Rviz GUI. For example, it is possible to configure the color and the dimension of points, arrows and cones. Additionally, the users can select different lines style display.

## :penguin: Building

1. Installation pinocchio from any source (ros / robotpkg binaries or source)

2. Building the state_msgs and these packages in your catkin workspace:
    ```bash
	cd your_ros_ws/
	catkin build #catkin_make
    ```

## :copyright: Credits

### :writing_hand: Written by

- [Carlos Mastalli](https://cmastalli.github.io/), The University of Edinburgh :uk:
