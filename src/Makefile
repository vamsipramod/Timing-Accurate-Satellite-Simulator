
CXXFLAGS= -std=c++17 -DNDEBUG -O3 -g -lelf
CXX=g++

NANOLOG_RUNTIME_DIR= ./NanoLog/runtime

all:  satsim decompressor

OBJS = satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o elf_reader.o

$(OBJS) : %o : %cpp
		$(CXX) -I $(NANOLOG_RUNTIME_DIR) -c -o $@ $< $(CXXFLAGS)

satsim : satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o elf_reader.o
		g++ -o satsim satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o elf_reader.o libNanoLog.a -lelf -L. -lNanoLog -pthread -lrt


clean :	
		rm satsim satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o elf_reader.o

clean-all: clean
	@rm -f libNanoLog.a decompressor
	$(MAKE) clean-all -C $(NANOLOG_RUNTIME_DIR)