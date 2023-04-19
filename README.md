# Minecart

## Building

To compile Minecart, use one of the following dependending on your build target...

### Probable requirements

You may need to install some packages on your system to build Minecart.
Currently I show how to build on Debian-based, RedHat-based, and MSYS2 (Windows) systems.

#### Debian-based Systems

The following instructions apply to:

* Ubuntu 20.04, 18.04, 16.04
* Debian 10, 9

(Note: these instructions may be outdated)

```
sudo apt-get install -y \
    build-essential \
    cmake \
    xorg-dev \
    libgl1-mesa-dev \
    libfreetype6-dev
```

#### RedHat-based Systems

The following instructions apply to:

* Fedora 22 and higher

(Note: these instructions may be outdated)

```
sudo dnf install -y \
    gcc gcc-c++ make \
    cmake \
    mesa-libGL-devel \
    libXrandr-devel \
    libXinerama-devel \
    libXcursor-devel \
    libXi-devel \
    freetype-devel
```

#### MSYS2 (Windows) and maybe other systems which uses Pacman

* x86_64 based systems
```
pacman -S base-devel mingw-w64-x86_64-{cmake,gcc,freeglut,glew,libpng,mesa,egl-headers}
```
* other systems

Replace `mingw-w64-x86_64` with the architecture for your system (e.g. `mingw-w64-clang-i686`)

### Desktop

Use the following to build for desktop:

``` bash
cmake -B build
cmake --build build
```

### Web

Compiling for the web requires the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html):

``` bash
mkdir build
cd build
emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-s USE_GLFW=3" -DCMAKE_EXECUTABLE_SUFFIX=".html"
emmake make
```