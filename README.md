# Timing-Accurate Satellite Simulator




## Getting Started

### Installation

1. Clone the repo
```sh
git clone https://github.com/vamsipramod/Timing-Accurate-Satellite-Simulator.git
```
2. Go to the root directory of the project, and do:

```sh
./autogen.sh
```

3. This should create all "configure" script along with all the Makefile's. Now, you can type
```sh
./configure
make
```

This compiles the project and creates binary `simulator`.
Binary should be available at `src/`.


### Usage

To test the simulator with an executable. Go to `src/main`, Do :
```sh
./simulator  </path/to/SPARCv8/executable>
```

`Note` : The Target Architecture of Simulator is SPARC V8 Architecture, So target ISA of executable that is passed to simulator must be SPARC V8
