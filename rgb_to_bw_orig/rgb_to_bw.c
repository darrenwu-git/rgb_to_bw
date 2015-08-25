#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define RGBA_FILE "../image.rgba"
#define RGBA_FILE_SIZE 1600512

#define BW_FILE "../image_bw.rgba"

void rgba_to_bw(uint32_t *bitmap, int width, int height, long stride) {
    int row, col;
    uint32_t pixel, r, g, b, a, bw;
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            pixel = bitmap[col + row * stride / 4];
            a = (pixel >> 24) & 0xff;
            r = (pixel >> 16) & 0xff;
            g = (pixel >> 8) & 0xff;
            b = pixel & 0xff;
            bw = (uint32_t) (r * 0.299 + g * 0.587 + b * 0.114);
            bitmap[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
        }
    }
}

int main()
{
	FILE *fp=NULL;
	uint32_t *bitmap;
	size_t sz;

	//read rgba
	fp = fopen(RGBA_FILE, "r");
	if(fp == NULL)
	{
		perror("Open RGBA fail");
		return -1;	
	}

	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);

	bitmap = malloc(sz);
	if(bitmap == NULL)
	{
		perror("No memory");
		return -1;
	}

	fread(bitmap, sz, 1, fp);

	fclose(fp);

	//convert to BW
	rgba_to_bw(bitmap, 800, 500,0);

	//write back
	fp = fopen(BW_FILE, "w+");
        if(fp == NULL)
        {
                perror("Open BW fail");
                return -1;
        }

	fwrite(bitmap, sz, 1, fp);

	fclose(fp);

	return 0;
}
