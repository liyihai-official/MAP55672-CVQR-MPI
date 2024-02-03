echo "Setup Environment Vairables from file $0"

export LIBRARY_PATH=/opt/homebrew/Cellar/open-mpi/5.0.1/lib:$LIBRARY_PATH
export C_INCLUDE_PATH=/opt/homebrew/Cellar/open-mpi/5.0.1/include:$C_INCLUDE_PATH


export LIBRARY_PATH=/opt/homebrew/opt/lapack/lib:$LIBRARY_PATH
export C_INCLUDE_PATH=/opt/homebrew/opt/lapack/include:$C_INCLUDE_PATH


export LIBRARY_PATH=/opt/homebrew/opt/openblas/lib:$LIBRARY_PATH
export C_INCLUDE_PATH=/opt/homebrew/opt/openblas/include:$C_INCLUDE_PATH

echo "Compiling"
make
