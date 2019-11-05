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

3. This should create the `configure` script, and other `Makefile`s. Now type
```sh
./configure
make
make install
```

This compiles the source files in `src/`, creates the binary `satsim`, and installs it in `.`


### Usage

To run the simulator:
```sh
./satsim  </path/to/SPARCv8/executable>
```

`Note` : The Target Architecture of Simulator is SPARC V8 Architecture, So target ISA of executable that is passed to simulator must be SPARC V8
