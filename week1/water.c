#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("minutes: ");
    int minutes = GetInt();
    int b = minutes*192/16;
    printf("bottles: %d\n", b);
}