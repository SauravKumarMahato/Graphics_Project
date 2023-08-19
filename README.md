# OPENGL_CAR

The project basically contains a moveable environment or view where there is a car which has some basic functionality like real car has and user can change the color of car and switch between day and night environment. 


## FUNCTIONALITIES:

|      **Buttons**      |                **Uses**               |   
|:---------------------:|:-------------------------------------:|
|           w           |               move front              |
|           s           |               move back               |   
|           a           |               turn left               |   
|           d           |               turn right              |  
|        w and a        | move front along with turning left    |   
|        w and d        |  move front along with turning right  |  
|           1           |          move up in y - axis          |
|           2           |         move down in y - axis         |   
|           f1          |                 night                 |   
|           f2          |                  day                  |   


| **Buttons for color** |          **Color of the Car**         |  
|:---------------------:|:-------------------------------------:|
|           r           |                  Red                  |  
|           g           |                 green                 |   
|           b           |                  blue                 |  
|           y           |                 yellow                |   
|           p           |                  pink                 |   



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


![Screenshot from 2023-08-19 16-42-06](https://github.com/SauravKumarMahato/Graphics_Project/assets/83631265/72c107f6-8afd-45e6-ae22-e1745e9536a8)
![Screenshot from 2023-08-19 16-41-23](https://github.com/SauravKumarMahato/Graphics_Project/assets/83631265/204071e7-40bf-42d7-bce6-dafd82d95763)
![Screenshot from 2023-08-19 16-40-58](https://github.com/SauravKumarMahato/Graphics_Project/assets/83631265/fb53932a-393d-44a5-8c52-c0f426baf5a5)
![Screenshot from 2023-08-19 16-42-34](https://github.com/SauravKumarMahato/Graphics_Project/assets/83631265/3b4d3c73-92c9-47bb-b27b-f336aa23ac1c)
![Screenshot from 2023-08-19 16-42-20](https://github.com/SauravKumarMahato/Graphics_Project/assets/83631265/6fa02836-a1bc-46d1-b1a9-0f51c78fbad0)

## REFERENCES:

- https://en.wikipedia.org/wiki/Wavefront_.obj_file
- https://www.loc.gov/preservation/digital/formats/fdd/fdd000507.shtml
- http://paulbourke.net/dataformats/mtl/
- https://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html
