/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 1 || n > 100) {
        printf("Please use a number between 1 and 100.\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    

    // calculate new padding
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int resizedPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) * n) % 4) % 4;

    // declare new variables
    BITMAPFILEHEADER resizedBf = bf;
    BITMAPINFOHEADER resizedBi = bi;
    
    // update the width & height
    resizedBi.biWidth = bi.biWidth * n;
	resizedBi.biHeight = bi.biHeight * n;

    // calculate new image sizes
    resizedBi.biSizeImage = ((resizedBi.biWidth * sizeof(RGBTRIPLE)) + resizedPadding) * abs(resizedBi.biHeight);
    resizedBf.bfSize = resizedBf.bfSize + (resizedBi.biSizeImage - bi.biSizeImage);


    // write outfile's BITMAPFILEHEADER
    fwrite(&resizedBf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&resizedBi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // number of reads
        for (int x = 0; x < n; x++) 
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile n times
                for (int y = 0; y < n; y++) {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                }
            }
            
            // add resized padding to file
            for (int k = 0; k < resizedPadding; k++)
            {
                fputc(0x00, outptr);
            }
            
            if (x < n-1) {
                long offset = (bi.biWidth * sizeof(RGBTRIPLE));
                fseek(inptr, -offset, SEEK_CUR);
            }
            
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
