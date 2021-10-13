#include <stdlib.h>
#include <stdio.h>
#define MAX_PATH 100

typedef struct dimension{
    int width;
    int height;
} Dimension;

/**
 * Allocates memory for a matrix with
 * bcertain width and height
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
int **read_file(char *path, char *type, int *limit, Dimension *D){
    FILE *imgP = fopen(path, "r");
    if(imgP == NULL){
        printf("Unable to open file.\n");
        printf("Please, check if your path has less than 99 characters or if it was properly typed");
        exit(0);
    }

    fscanf(imgP, "%s", type);
    fscanf(imgP, "%d %d", &(D->width), &(D->height));
    fscanf(imgP, "%d", limit);

    int **matrix = allocate_matrix(D->width, D->height);
    for(int i=0; i<D->height; i++){
        for(int j=0;j<3*(D->width); j++){
            fscanf(imgP, "%d", &matrix[i][j]);
        }
    }
    fclose(imgP);
    return matrix;
}

/**
 * Prints a matrix to stdout
 * */
void print_matrix(FILE *newFileP, int **matrix, int width, int height){
    for(int i=0; i<height; i++){
        for(int j=0; j<3*width; j++){
            fprintf(newFileP, "%d ", matrix[i][j]);
        }
        fprintf(newFileP, "\n");
    }
}

/**
 * Applies convolution using kernel
 * */
int **apply_convolution(int **matrix, Dimension D, float **kernel, int kernel_size){
    int **conv_matrix = allocate_matrix(D.width, D.height);
    int num_pixels_skip = (kernel_size-1)/2;
    for(int i=num_pixels_skip; i<D.height-num_pixels_skip; i++){
        for(int j=3*num_pixels_skip; j<3*(D.width-num_pixels_skip); j++){
            float value = 0;
            for(int k=0; k<kernel_size; k++){
                for(int l=0; l<kernel_size; l++){
                    value += kernel[k][l] * matrix[i-num_pixels_skip+k][j-3*num_pixels_skip+3*k];
                }
            }
            if(value > 255){
                value = 255;
            }else if(value < 0){
                value = 0;
            }
            conv_matrix[i][j] = (int) value;
        }
    }
    return conv_matrix;
}

/**
 * Create new file
 * */
void write_file(int **conv_matrix, char *type, int limit, Dimension *D){
    FILE *newFileP = fopen("file_processed.ppm", "w+");
    fprintf(newFileP, "%s\n", type);
    fprintf(newFileP, "%d %d\n", D->width, D->height);
    fprintf(newFileP, "%d\n", limit);
    print_matrix(newFileP, conv_matrix, D->width, D->height);
    fclose(newFileP);
}

/**
 * Reads square matrix/kernel from stdin
 * */
float **read_kernel(int *kernel_size){
    printf("Enter size of kernel: ");
    scanf("%d", kernel_size);
    if(*kernel_size % 2 == 0){
        printf("Only kernels with odd size are allowed.\n");
        exit(0);
    }
    float **kernel = malloc(*kernel_size * sizeof(float *));
    printf("Please, enter kernel: \n");
    for(int i=0; i<*kernel_size; i++){
        kernel[i] = calloc(*kernel_size, sizeof(float));
        for(int j=0; j<*kernel_size; j++){
            scanf("%f", &kernel[i][j]);
        }
    }
    return kernel;
}

int main(){
    char *type = malloc(3 * sizeof(char));
    int limit;
    Dimension *D = malloc(sizeof(Dimension));
    char *path = malloc(MAX_PATH * sizeof(char));

    printf("Type the path of your file: ");
    scanf("%s", path);

    int **matrix = read_file(path, type, &limit, D);
    int kernel_size;
    float **kernel = read_kernel(&kernel_size);

    int **conv_matrix = apply_convolution(matrix, *D, kernel, kernel_size);

    write_file(conv_matrix, type, limit, D);
    return 0;
}
