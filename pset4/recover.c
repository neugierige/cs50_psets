/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t buffer[512];

int main()
{
    int imageCount = 0;
    FILE* imageFile = NULL;
    
    // OPEN MEMORY CARD FILE
    FILE* memoryCard = fopen("card.raw", "r");
    
    // READ UNTIL THE END OF THE FILE
    while (fread(buffer, sizeof(buffer), 1, memoryCard) == 1) {
        
        // FIND BEGINNING OF JPG FILE
        if (buffer[0] == 0xff &&  buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef) {
            
            if (imageFile != NULL) {
                fclose(imageFile);
            }
            
            // OPEN A NEW JPG
            char name [8];
            sprintf(name, "%03d.jpg", imageCount);
            imageFile = fopen(name, "w");
            imageCount += 1;
            
            // WRITE 512 BYTES
            fwrite(buffer, sizeof(buffer), 1, imageFile);
        
        // else if this is not the 1st iteration
        } else if (imageFile != NULL) {
            fwrite(buffer, sizeof(buffer), 1, imageFile);
        }
        
    }
    
    fclose(memoryCard);
    return 0;
}