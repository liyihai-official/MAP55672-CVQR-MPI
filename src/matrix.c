


/**
 * @brief This function transform the Upper-Right corner part of 
 * input MATRIX into a VECTOR
*/
int flatten_UR(const void ** matrix, void * vector, const int row, const int col, int * count){
    
    if (matrix == NULL || vector == NULL) {
        return -1;
    }

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (i <= j){
                vector[*count] = matrix[i][j];
                *count ++;
            }
        }
    }

    return 0;
}