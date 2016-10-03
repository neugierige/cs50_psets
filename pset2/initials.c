#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name;
    do
    {
        name = GetString();
    } while (name == NULL);
    
    printf("%c", toupper(name[0]));
    for (int i = 0, j = strlen(name); i < j; i++)
    {
        if (isblank(name[i]))
        {
            printf("%c", toupper(name[i+1]));
        }   
    }
    printf("\n");
}