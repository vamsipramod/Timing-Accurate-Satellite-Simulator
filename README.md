# Timing-Accurate Satellite Simulator




## Getting Started

### Installation

1. Clone the repo
```sh
git clone https://github.com/vamsipramod/Timing-Accurate-Satellite-Simulator.git
```
2. Go to the root directory of the project, and do:

```sh
 autoconf
```

3. This should create the `configure` script. Now type
```sh
./configure
```

4. configure checks for pre-requisties required by the project and produces Makefile's. Now do
```sh
make

make install
```
This compiles the source files in `src/` and creates folders `bin` and `lib`.
`bin` contains the executable `satsim`.


### Usage

To run the simulator:
```sh
./bin/satsim  </path/to/SPARCv8/executable>
```

This Creates `CompressedLog` file which contains Log messages in compressed binary format.

To Convert the `CompressedLog` to human readable format. Do:

```sh
./bin/decompress.sh 
```

`Note` : The Target Architecture of Simulator is SPARC V8 Architecture, So target ISA of executable that is passed to simulator must be SPARC V8
