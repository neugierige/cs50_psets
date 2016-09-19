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
        printf("%.*s", space, "                          ");
        printf("%.*s", i, "########################");
        printf("#\n");
    }

}