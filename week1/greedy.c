#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float x;
    do
    {
        printf("O hai! How much change is owed?\n");
        x = GetFloat();    
    } while (x <= 0);
    
    int y = roundf(x*100);
    int quarters = y/25;
    int dimes = round((y % 25)) / 10;
    int nickels = ((y % 25) % 10) / 5;
    int pennies = ((y % 25) % 10) % 5;
    
    int count = quarters + dimes + nickels + pennies;
    printf("%d\n", count);
}
