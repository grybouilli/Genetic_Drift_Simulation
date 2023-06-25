# Genetic Drift Simulation : Where are the tusks ?
## About the project

This is an old-ish project I did back in my senior year, when I was teaching myself C++ and SFML. 

### Simulation of genetic drift on elephants and their tusks

During a biology course, we learned about genetic drift and its effect on elephants and their tusks. Elephants living in areas where hunters are active tend to be born tusksless because of natural selection. However, an experience led to observe that a population of elephants which were put in a protected park still ended up with no tusks as generations advanced - even tho they were not being hunted.

This project aims to simulate a population of elephants growing and reproducing through time to see the effects of the genetic 
drift.

## Build it on your own

Pre-requisited packages:

 * CMake and make 
 * The [SFML lib](https://www.sfml-dev.org/download.php) version $\geq$ 2.5; 

Simply clone the repo and run the following lines in a terminal :

```bash
$ mkdir build
$ cd build
$ cmake .. # and eventual options such as -GNinja
$ cmake --build .
```
