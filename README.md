# C++ Multithreading - Barnsely Fern
---
### Preface

This project uses C++ multithreading (producer-consumer model) in order to draw the well known [Barnsley fern](<https://en.wikipedia.org/wiki/Barnsley_fern>) (see resulting image below). 

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
<br/> `sudo apt-get install cmake`
<br/> `sudo apt-get install build-essential`
<br/> `sudo apt-get install imagemagick libpng-dev zlib1g-dev`

---

### Execution

In order to make use of the code, please invoke `make compile` in the root directory of this repository, everything else is done automatically afterwards.

