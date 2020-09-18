#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <regex.h>
#include "stb_image.h"
#include "stb_image_write.h"

int readmatrix(size_t rows, size_t cols, double (*a)[cols], const char* filename)
{

    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL)
        return 0;

    for(size_t i = 0; i < rows; ++i)
    {
        for(size_t j = 0; j < cols; ++j)
            fscanf(pf, "%lf", a[i] + j);
    }


    fclose (pf); 
    return 1; 
}

int main(int argc, char *argv[]){
if (argc == 5){
	clock_t tic_t = clock();
	char *imgpath = argv[1];
	char *filterpath = argv[2];
	char *imgrespath = argv[3];
	char *filtsize = argv[4];
	int w, h, bpp, i, j, cc = 3;
	unsigned char sum;
	double a[atoi(filtsize)][atoi(filtsize)];
	readmatrix(atoi(filtsize), atoi(filtsize), a, filterpath);
	uint8_t* image = stbi_load(imgpath, &w, &h, &bpp, cc);
	size_t img_size = w * h * cc;
	int gray_channels = 1;
	size_t gray_img_size = w * h * gray_channels;
	unsigned char *gray_img = malloc(gray_img_size);
	unsigned char *new_img_gray = malloc(gray_img_size);

	for(unsigned char *p = image, *pg = gray_img; p != image + img_size; p += cc, pg += gray_channels) {
		*pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
	}

	//convolution
	clock_t tic_c = clock();
	int temp = atoi(filtsize)-1;
	for (unsigned char *p = gray_img, *pg = new_img_gray; p != gray_img + gray_img_size; p++, pg++){
		sum = 0;
		for (i = temp; i >= 0; i--){
			for (j = temp; j >= 0; j--){
				sum += a[i][j] * *(p + 1 + (atoi(filtsize)-(j+1)) + (w*(atoi(filtsize)-(i+1))));
			}
		}
		//save convolution result into new image
		*pg = (uint8_t)sum;
	}	
	clock_t toc_c = clock();
	stbi_write_jpg(imgrespath, w, h, gray_channels, new_img_gray, 100);
	stbi_image_free(image);
	free(gray_img);
	free(new_img_gray);
	clock_t toc_t = clock();
	printf("Total convolution time: %f seconds\n", (double)(toc_c - tic_c) / CLOCKS_PER_SEC);
	printf("Total time elapsed: %f seconds\n", (double)(toc_t - tic_t) / CLOCKS_PER_SEC);
} else {
	printf("Incorrect number of arguments\n");
}
	return 0;
}
