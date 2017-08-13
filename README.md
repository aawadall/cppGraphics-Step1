This Repository is an attempt to recover my Computer Graphics Assignments a couple of years ago.

## Platform
This project was written to run on Ubuntu 14.04

## Dependencies
This project relies heavily onthe following libraries 
* libglut3-dev
* libglew-dev
* eigen3

## Usage 
To view model ```modelviewer <object file>``` 
Then in the program, press:

### General Program Controls 
|Key |Action                          |
|----|--------------------------------|
| q  | Quits Program                  |
| w  | Write Model into a file        |
| ?  | Display Model & Camera Information |

### Camera Controls
|Key |Action                          |
|----|--------------------------------|
| D  | Dolly +ve (x-axis translation) |
| d  | Dolly -ve                      |
| C  | Crane +ve (y-axis translation) |
| c  | Crane -ve                      |
| I  | Zoom  +ve (z-axis translation) |
| i  | Zoom  -ve                      |
| L  | Roll Camera +ve                |
| l  | Roll Camera -ve                |
| T  | Tilt Camera +ve                |
| t  | Tilt Camera -ve                |
| A  | Pan  Camera +ve                |
| a  | Pan  Camera -ve                |
| v  | Orthographic View              |
| V  | Prespective View               |
| f  | Switch Off Fog                 |
| F  | Switch On Fog                  |

### Model Controls 
|Key |Action                          |
|----|--------------------------------|
| N  | Translate Depth +ve            |
| n  | Translate Depth -ve            |
| Y  | (Yaw) Rotate Model Left        |
| y  | (Yaw) Rotate Model Right       |
| P  | (Pitch) Rotate Model Down      |
| p  | (Pitch) Rotate Model Up        |
| R  | (Roll) Rotate Around z-axis +ve|
| r  | (Roll) Rotate Around z-axis -ve|
| x  | Reset Rotation/Translation/Scale Axis            |
| +  | Scale Big                      |
| -  | Scale Small                    |
