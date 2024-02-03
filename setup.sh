echo "Setup Environment Vairables from file $0"


# ARM MacOS
# export LIBRARY_PATH=/opt/homebrew/Cellar/open-mpi/5.0.1/lib:$LIBRARY_PATH
# export C_INCLUDE_PATH=/opt/homebrew/Cellar/open-mpi/5.0.1/include:$C_INCLUDE_PATH


# export LIBRARY_PATH=/opt/homebrew/opt/lapack/lib:$LIBRARY_PATH
# export C_INCLUDE_PATH=/opt/homebrew/opt/lapack/include:$C_INCLUDE_PATH


# export LIBRARY_PATH=/opt/homebrew/opt/openblas/lib:$LIBRARY_PATH
# export C_INCLUDE_PATH=/opt/homebrew/opt/openblas/include:$C_INCLUDE_PATH



# LINUX 
export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/$LIBRARY_PATH
export C_INCLUDE_PATH=/usr/include/x86_64-linux-gnu/mpi/:$C_INCLUDE_PATH

export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/lapack/$LIBRARY_PATH
export C_INCLUDE_PATH=/home/li/mytf/lib/python3.10/site-packages/external/eigen_archive/Eigen/src/misc/:$C_INCLUDE_PATH



echo "Compiling"
make
