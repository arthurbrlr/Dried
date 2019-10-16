## Personnal Project - DRIED
###### Made during my free time in Aug. 19 - 3 weeks project - Not even complete

**Project description:** I tried to create my own version of Minecraft using OpenGL and C++. This project was mainly a reason to learn a lot on how games works, how to optimize code, etc... Although my version is not as complete as it could possibly be, I'm proud of what I've been able to come up with, knowing that I was working on it 5h/day after being 8-9h at my internship in Stellenbosch.

Implementation in C++ - Using OpenGL as the Graphic API - I used also ImGUI for debugging and LUA for the world gen
I will include some GIF/JPEG later.


### What I learned with this code
 * Basic design patterns in video games,
 * How does a GPU works, how it can be used to display images on the screen,
 * A shit ton about C++: unordered maps, multithreading, mutex, singletons, code optimization, compute shaders and more.


---

### Inspiration
This project was inspired by the video [Coding Minecraft in One Week in C++](https://www.youtube.com/watch?v=Xq3isov6mZ8). 

I learned a lot from:
- [ThinMatrix](https://www.youtube.com/user/ThinMatrix),
- [GLFW.org](https://www.glfw.org/docs/latest/modules.html),
- [Learn OpenGL](https://learnopengl.com/),
- [Hopson repository](https://github.com/Hopson97/MineCraft-One-Week-Challenge).

---

### /headers & /src
The code in those folders is the game engine, divided into multiple subfolders named to be easily understandable. (Ex: the Entities subfolder contains all the code related to the Entities behaviour - movement, position, rotation, scale, etc...)

### /imgui
This is the ImGUI library, it can be used to create easily some usefull and interactive graphic interfaces.

### /lua
This is the code used to interpret LUA code in C++. This is really usefull to change some key parameters in the code (in my case, the biome generation) without compiling every time.

### /res
Ressources folder, containing the textures, shaders, block informations and more.

##### How can I use the code ?
It is pretty straight-forward. The code can be compile by the makefile only.
```
cd path/to/makefile
make
```
Unfortunately, this will only works on MacOs, because of the way OpenGL works on other OS.
```
./run
```

#WIP
