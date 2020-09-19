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

int main(int argc, char *argv[]){
if (argc == 5){
	clock_t tic_t = clock(); //Total calculation timing
    //Variable declaration
    FILE *pf;
	char *imgpath = argv[1];
	char *filterpath = argv[2];
	char *imgrespath = argv[3];
	char *filtsize = argv[4];
	int filt_cont, tmpcont, w, h, bpp, cc = 3, colc=1, wc, hc, crop_img_size;
	double *tmp, *at, *a = malloc(atoi(filtsize)*atoi(filtsize)*sizeof(double *));
    unsigned char sum, *image, *p, *pg, *gray_img, *new_img_gray;
    size_t img_size, gray_img_size, i;
    int gray_channels = 1;
    //Reading the filter from a file
    pf = fopen (filterpath, "r");
    if (pf == NULL){
        printf("Error loading filter\n");
        return 0;
    }   
    for(i = 0, tmp = a; i < atoi(filtsize)*atoi(filtsize); ++i){
            fscanf(pf, "%lf", tmp++);
    }
    fclose (pf); 
    //Image loading
	image = stbi_load(imgpath, &w, &h, &bpp, cc);
	img_size = w * h * cc;
	gray_img_size = w * h * gray_channels;
    wc = w - (atoi(filtsize)-1);
    hc = h - (atoi(filtsize)-1);     
    crop_img_size = wc* hc;
    //New image memory allocation
	gray_img = malloc(gray_img_size);
	new_img_gray = malloc(crop_img_size);
    //Grayscale conversion
	for(p = image, pg = gray_img; p != image + img_size; p += cc, pg += gray_channels) {
		*pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
	}
	//Convolution
	clock_t tic_c = clock(); //Timing convolution
	for (p = gray_img, pg = new_img_gray; pg != new_img_gray + crop_img_size; p++, pg++){
        sum = 0;
        tmpcont = 0;
        for (at = (a + (atoi(filtsize)*atoi(filtsize))-1),  filt_cont = (atoi(filtsize)*atoi(filtsize))-1; at >= a; at--, filt_cont--){
            sum += *at * *(p + tmpcont + (w*(atoi(filtsize)-((int)(filt_cont/atoi(filtsize))+1))));
            if (tmpcont == (atoi(filtsize)-1)){
                tmpcont = 0;
            } else {
                tmpcont++;
            }
        }
        if (colc == wc){
            colc = 1;
            p = p + atoi(filtsize)-1;
        } else {
            colc++;             
        }
        *pg = (uint8_t)sum; 
	}	
	clock_t toc_c = clock();
    //Write convolution result in file
	stbi_write_jpg(imgrespath, wc, hc, gray_channels, new_img_gray, wc * gray_channels);
    //Free memory
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
