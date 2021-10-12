#include <stdlib.h>
#include <stdio.h>

typedef struct dimension{
    int width;
    int height;
} Dimension;

/**
 * Allocates memory for a matrix with
 * certain width and height
 * */
int **allocate_matrix(int width, int height){
    int **matrix = malloc(height * sizeof(int *));
    for(int i=0; i<height; i++){
        matrix[i] = calloc(3*width, sizeof(int));
    }
    return matrix;
}

/**
 * Reads Netpbm file. It returns the matrix
 * corresponding to the image and modifies the values
 * stored in the char *type pointer and Dimension *D pointer.
 * */
int **read_file(char *type, int *limit, Dimension *D){
    scanf("%s", type);
    scanf("%d %d", &(D->width), &(D->height));
    scanf("%d", limit);
    int **matrix = allocate_matrix(D->width, D->height);
    for(int i=0; i<D->height; i++){
        for(int j=0;j<3*(D->width); j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    return matrix;
}

/**
 * Prints a matrix to stdout
 * */
void print_matrix(int **matrix, int width, int height){
    for(int i=0; i<height; i++){
        for(int j=0; j<3*width; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * Applies convolution using kernel
 * */
int **apply_convolution(int **matrix, Dimension D, int kernel[][3]){
    int **conv_matrix = allocate_matrix(D.width, D.height);
    for(int i=1; i<D.height-1; i++){
        for(int j=3; j<3*(D.width-3); j++){
            int value = 0;
            for(int k=0; k<3; k++){
                for(int l=0; l<3; l++){
                    value += kernel[k][l] * matrix[i-1+k][j-3+3*k];
                }
            }
            if(value > 255){
                value = 255;
            }else if(value < 0){
                value = 0;
            }
            conv_matrix[i][j] = value;
        }
    }
    return conv_matrix;
}

int main(){
    char *type = malloc(3 * sizeof(char));
    int limit;
    Dimension *D = malloc(sizeof(Dimension));

    int **matrix = read_file(type, &limit, D);
    int kernel[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };

    int **conv_matrix = apply_convolution(matrix, *D, kernel);


    printf("%s\n", type);
    printf("%d %d\n", D->width, D->height);
    printf("%d\n", limit);
    print_matrix(conv_matrix, D->width, D->height);
    return 0;
}
