CC = g++-13

LDFLAGS = -L/opt/homebrew/opt/lapack/lib
CPPFLAGS = -I/opt/homebrew/opt/lapack/include

LDFLAGS_="-L/opt/homebrew/opt/openblas/lib"
CPPFLAGS_="-I/opt/homebrew/opt/openblas/include"



lapack: lapack.cc
	$(CC) -o $@ $< $(CPPFLAGS) $(CPPFLAGS_) $(LDFLAGS) $(LDFLAGS_) -llapack -lopenblas -lblas

# vec_add: vec_add.c
# 	$(CC) -o $@ $< -fopenmp


