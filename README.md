# HPC Consumer-Producer Model using C++
---
### Preface

This project showcases a producer-consumer model using mutual exclusions (Mutex) using C++ in order to draw the well known [`Barnsley fern`](<https://en.wikipedia.org/wiki/Barnsley_fern>) (see resulting image below). Therein, the computational workload can distributed among several workers in order to speed up the entire process. The number of workers is selectable and can be adjusted according to the computational hardware at hand. 

<h2 align="center">
  <img src="assets/fern_image.png" alt="resulting barnsley fern" width="300px" />
</h2>

---

### Repository Structure
- [`assets`](/assets) includes image of the final Barnsely fern
- [`src`](/src) contains source files of the project

---

### Prerequisits for Linux Enviroment (Tested on Ubuntu 20.04)

- [CMake](https://cmake.org/) - Platform for build automation, testing and packaging using a compiler-independent method
<br/> `sudo apt-get update`
<br/> `sudo apt-get install cmake gcc clang gdb built-essential`


- [imagemagick library](https://imagemagick.org/index.php) and dependencies in order to be able to work with PNG images
<br/> `sudo apt-get install imagemagick libpng-dev zlib1g-dev`

---

### Execution

In order to make use of the code, please invoke `make compile` in the root directory of this repository. Subsequently:
1. `cd src/`
2. `cd build/`
3. `./BarnselyFern`

