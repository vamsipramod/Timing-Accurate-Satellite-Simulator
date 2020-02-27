
CXXFLAGS= -std=c++17 -DNDEBUG -O3 -g -lelf
CXX=g++

NANOLOG_RUNTIME_DIR= ./NanoLog/runtime

all:  satsim decompressor

OBJS = satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o elf_reader.o

$(OBJS) : %o : %cpp
		$(CXX) -I $(NANOLOG_RUNTIME_DIR) -c -o $@ $< $(CXXFLAGS)

satsim : satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o elf_reader.o
		g++ -o satsim satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o elf_reader.o libNanoLog.a -lelf -L. -lNanoLog -pthread -lrt




# satsim.o : satsim.cpp satsim.h NanoLogCpp17.h
# 		  g++ -c satsim.cpp	

# core.o : core.cpp core.h NanoLogCpp17.h
# 		g++ -c core.cpp

# fetch.o : fetch.cpp fetch.h NanoLogCpp17.h
# 		 g++ -c fetch.cpp

# decode.o : decode.cpp decode.h NanoLogCpp17.h
# 		  g++ -c decode.cpp

# execute.o : execute.cpp execute.h NanoLogCpp17.h
# 		   g++ -c execute.cpp

# reg_access.o : reg_access.cpp reg_access.h NanoLogCpp17.h
# 			  g++ -c reg_access.cpp

# mem_access.o : mem_access.cpp mem_access.h NanoLogCpp17.h
# 			  g++ -c mem_access.cpp	

# exception.o : exception.cpp exception.h NanoLogCpp17.h
# 			 g++ -c exception.cpp

# write_back.o :  write_back.cpp write_back.h NanoLogCpp17.h
# 			  g++ -c write_back.cpp

# reg.o : reg.cpp reg.h NanoLogCpp17.h
# 		g++ -c reg.cpp

# instruction.o : instruction.cpp instruction.h NanoLogCpp17.h
# 				g++ -c instruction.cpp

clean :	
		rm satsim satsim.o core.o fetch.o decode.o execute.o reg_access.o mem_access.o exception.o write_back.o reg.o instruction.o

# libNanoLog.a:
# 	$(MAKE) libNanoLog.a -C $(NANOLOG_RUNTIME_DIR)
# 	cp $(NANOLOG_RUNTIME_DIR)/libNanoLog.a .

# decompressor:
# 	$(MAKE) decompressor -C $(NANOLOG_RUNTIME_DIR)
# 	cp $(NANOLOG_RUNTIME_DIR)/decompressor .

# Cleans up the NanoLog files as well
clean-all: clean
	@rm -f libNanoLog.a decompressor
	$(MAKE) clean-all -C $(NANOLOG_RUNTIME_DIR)