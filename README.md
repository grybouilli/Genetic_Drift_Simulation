# Genetic Drift Simulation : Where are the tusks ?
## About the project

This is an old-ish project I did when I was in highschool and was learning C++ on my own for game dev purpose. Below is what I wrote about it back at the time:

### Simulation of genetic drift on elephants and their tusks

This is a little personnal project inspired from a homework we had in biology. The subject was about genetic drift amongst 
elephants. It was observed that a population of elephants which were put in a protected park ended up with no 
tusks through generations, even tho they were not being hunted. 

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