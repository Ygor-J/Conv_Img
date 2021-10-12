#include <stdlib.h>
#include <stdio.h>

typdef struct dimension{
    int width;
    int height;
} Dimension;

int **allocate_matrix(int width, int height){
    int **matrix = malloc(height * sizeof(int *));
    for(int i=0; i<height; i++){
        matrix[i] = malloc(width * sizeof(int));
    }
    return matrix;
}


int **read_file(char *type, struct dimension *D){
    scanf("%s", type);
    scanf("%d %d", &(D->width), &(D->height));
    int **matrix = allocate_matrix(D->width, D->height);
    for(int i=0; i<D->height; i++){
        for(int j=0;j<D->width; j++){
            scanf("%d", matrix[i][j]);
        }
    }
    return matrix;
}

int main(){
    int **matrix = read_file();
    // applies convolution
    // returns file with applied convolution
    return 0;
}
