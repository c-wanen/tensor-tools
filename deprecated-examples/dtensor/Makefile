CC = icpc
CC_FLAGS = -O2 -qopenmp -qoverride-limits -xhost -DNDEBUG -std=c++11 -W

LAPACK_INC = -DMKL_Complex16="std::complex<double>"
LAPACK_LIB = -mkl=parallel

HDF5_INC = -DUSE_EZH5 -I/usr/local/opt/hdf5/include
HDF5_LIB = -L/usr/local/opt/hdf5/lib -lhdf5

TBLIS_INC = -DUSE_TBLIS -I/usr/local/include -I/usr/local/include/tblis
TBLIS_LIB = -L/usr/local/lib -ltblis

HPTT_INC = -DUSE_HPTT -I/Volumes/CoolStuff/MyLibrary/hptt/src
HPTT_LIB = -L/Volumes/CoolStuff/MyLibrary/hptt/lib -lhptt


# CC = g++-7
# CC_FLAGS = -O2 -g -march=native -fopenmp -ffast-math -std=c++11 -W
#
# LAPACK_INC = -framework Accelerate
# LAPACK_LIB = -framework Accelerate
#
# HDF5_INC = -DUSE_EZH5 -I/usr/local/opt/hdf5/include
# HDF5_LIB = -L/usr/local/opt/hdf5/lib -lhdf5
#
# TBLIS_INC = -DUSE_TBLIS -I/usr/local/include -I/usr/local/include/tblis
# TBLIS_LIB = -L/usr/local/lib -ltblis
#
# HPTT_INC = -DUSE_HPTT -I/Volumes/CoolStuff/MyLibrary/hptt/src
# HPTT_LIB = -L/Volumes/CoolStuff/MyLibrary/hptt/lib -lhptt


# CC = g++
# CC_FLAGS = -O2 -DNDEBUG -march=native -fopenmp -ffast-math -std=c++11 -W
#
# LAPACK_INC = -I/usr/include/openblas
# LAPACK_LIB = -lpthread -L/usr/lib/openblas-base -lopenblas
#
# HDF5_INC = -DUSE_EZH5 -I/usr/lib/x86_64-linux-gnu/hdf5/serial/include
# HDF5_LIB = -L/usr/lib/x86_64-linux-gnu/hdf5/serial/lib -lhdf5
#
# TBLIS_INC = -I/usr/local/include -I/usr/local/include/tblis
# TBLIS_LIB = -L/usr/local/lib -ltblis
#
# HPTT_INC = -DUSE_HPTT -I/home/xiongjie/CodeDoc/libraries/hptt/src
# HPTT_LIB = -L/home/xiongjie/CodeDoc/libraries/hptt/lib -Wl,-rpath=/home/xiongjie/CodeDoc/libraries/hptt/lib -lhptt

# File names
EXEC = run
SOURCES = $(wildcard ./main.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CC_FLAGS) $(TBLIS_LIB) $(HPTT_LIB) $(LAPACK_LIB) $(HDF5_LIB) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $(TBLIS_INC) $(HPTT_INC) $(LAPACK_INC) $(HDF5_INC) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
