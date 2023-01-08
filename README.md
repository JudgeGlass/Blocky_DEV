# Blocky



## Description
Me trying to make a voxel in OpenGL 3.3+

## Libraries
- GLFW
- GLM
- GLEW

Install the required dependencies
```bash
sudo apt install cmake make libglew-dev libglfw3-dev libglm-dev
```

Next, get a copy of Nothing's STB_IMAGE and copy it to your user includes
```bash
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
sudo cp stb_image.h /usr/local/include
```

## Build
Install cmake 3.16+ and run
```bash
mkdir build
cd build
cmake ..
make -j16 (replace 16 with amount of cpu cores)
```

To run, simpily run (in build directory)
```bash
./blocky
```

## Image
![Demo image of blocky](https://github.com/JudgeGlass/Blocky_DEV/blob/main/resources/demo.png?raw=true)
