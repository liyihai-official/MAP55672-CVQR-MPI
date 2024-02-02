# CC = g++-13

# LDFLAGS = -L/opt/homebrew/opt/lapack/lib
# CPPFLAGS = -I/opt/homebrew/opt/lapack/include

# LDFLAGS_="-L/opt/homebrew/opt/openblas/lib"
# CPPFLAGS_="-I/opt/homebrew/opt/openblas/include"

# MPIFLAGC = "-I/opt/homebrew/Cellar/open-mpi/5.0.1/include" 
# MPIFLAGL = "-L/opt/homebrew/Cellar/open-mpi/5.0.1/lib"






#-------------------------------------------------------------------------#
# export LIBRARY_PATH=/opt/homebrew/Cellar/open-mpi/5.0.1/lib:$LIBRARY_PATH
# export C_INCLUDE_PATH=/opt/homebrew/Cellar/open-mpi/5.0.1/include:$C_INCLUDE_PATH


# export LIBRARY_PATH=/opt/homebrew/opt/lapack/lib:$LIBRARY_PATH
# export C_INCLUDE_PATH=/opt/homebrew/opt/lapack/include:$C_INCLUDE_PATH


# export LIBRARY_PATH=/opt/homebrew/opt/openblas/lib:$LIBRARY_PATH
# export C_INCLUDE_PATH=/opt/homebrew/opt/openblas/include:$C_INCLUDE_PATH



# lapack: lapack.cc
# 	$(CC) -o $@ $< $(CPPFLAGS) $(CPPFLAGS_) $(LDFLAGS) $(LDFLAGS_) -llapack -lopenblas 
	
# # -lblas

# qr: qr.c
# 	gcc-13 -o $@ $< $(CPPFLAGS) $(CPPFLAGS_) $(LDFLAGS) $(LDFLAGS_) -llapack -lopenblas -lblas



CC = gcc-13
CFLAGS = -Wall -Werror
LDFLAGS = -llapack -lopenblas -lblas -lmpi

all: test

load.o: load.c load.h
	$(CC) $(CFLAGS) -c $< -o $@

test: test.c load.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
# $(MPIFLAGC) $(MPIFLAGL) $(CPPFLAGS) $(CPPFLAGS_) $(LDFLAGS) $(LDFLAGS_) 

clean:
	rm -f *.o test
