#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do 
    {
        printf("height: ");
        h = GetInt();     
    } while (h > 23 || h < 0);
    
        for (int i = 1; i<=h; i++)
        {
            int space = h-i;
            // printf("First time: i is %d. space is %d.\n", i, space);
            printf("%.*s", space, "                          ");
            // printf("space is %d", space);
            printf("%.*s", i, "########################");
            printf("#\n");
            // printf("Second time: i is %d. space is %d.\n", i, space);
        }

}