# OPENGL_CAR

The project basically contains a moveable environment or view where there is a car which has some basic functionality like real car has and user can change the color of car and switch between day and night environment. 


## FUNCTIONALITIES:

|      **Buttons**      |                **Uses**               |   |   |   |   |
|:---------------------:|:-------------------------------------:|---|---|---|---|
|           w           |               move front              |   |   |   |   |
|           s           |               move back               |   |   |   |   |
|           a           |               turn left               |   |   |   |   |
|           d           |               turn right              |   |   |   |   |
|        w and a        | move front along with turning left    |   |   |   |   |
|        w and d        |  move front along with turning right  |   |   |   |   |
|           1           |          move up in y - axis          |   |   |   |   |
|           2           |         move down in y - axis         |   |   |   |   |
|           f1          |                 night                 |   |   |   |   |
|           f2          |                  day                  |   |   |   |   |


| **Buttons for color** |          **Color of the Car**         |   |   |   |   |
|:---------------------:|:-------------------------------------:|---|---|---|---|
|           r           |                  Red                  |   |   |   |   |
|           g           |                 green                 |   |   |   |   |
|           b           |                  blue                 |   |   |   |   |
|           y           |                 yellow                |   |   |   |   |
|           p           |                  pink                 |   |   |   |   |



## INSTALL REQUIRED LIBRARY:
- Linux
```
sudo apt-get update
sudo apt-get install mesa-common-dev libglu1-mesa-dev freeglut3-dev
```
- For Arch Linux:
By default mesa should be installed, and libglu1 is included in [mesa package](https://archlinux.org/packages/extra/x86_64/mesa/). So you don't need to manually install it  
```
sudo pacman -Syu && sudo pacman -S mesa freeglut // Without yay installed
yay && yay -S mesa freeglut //With yay installed
```
## HOW TO RUN PROJECT
- Clone repository first: 
`git clone git@github.com:SauravKumarMahato/Graphics_Project.gity`
- Move inside OPENGL_CAR FOLDER: 
`cd OPENGL_CAR`
- Build with make: 
`make`
- Or build in command line: 
`g++ main.cpp -o load_model -lGL -lGLU -lglut`
- And run: 
`./load_model`

## SNAPSHOTS OF PROJECT:

![Image](https://github.com/WHKnightZ/OpenGL-Load-Model/blob/master/test.png)

## REFERENCES:

- https://en.wikipedia.org/wiki/Wavefront_.obj_file
- https://www.loc.gov/preservation/digital/formats/fdd/fdd000507.shtml
- http://paulbourke.net/dataformats/mtl/
- https://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html