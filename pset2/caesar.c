#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) 
{
    if (argc != 2) {
        printf("Please enter a positive integer");
        return 1;
    } 
    
    string input_str = GetString();
    int key = atoi(argv[1]);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
        
    for (int i = 0, j = strlen(input_str); i < j; i++) {
        int offset = 97;
        int checkUpper = 0;
        if (isupper(input_str[i])) {
            offset = 65;
            checkUpper = 1;
        } 
        int mod_index = ((int)input_str[i] - offset + key)%26;
        if (!isalpha(input_str[i])) {
            printf("%c", input_str[i]);
        } else {
            if (checkUpper == 1) {
                printf("%c", toupper(alphabet[mod_index]));
            } else {
                printf("%c", alphabet[mod_index]);
            }
        }
    }
    printf("\n");
    return 0;

}