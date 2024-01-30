#include <omp.h>
#include <stdio.h>


int main(){

    int n = 120;
    double x[n], y[n];

    int i;

    for (i = 0; i<n; i++){
        x[i] = i*i;
        y[i] = 3.2*i*i*i;
    }


#pragma omp parallel num_threads(3)
{
    int rank = omp_get_thread_num();
}
    return 0;
}