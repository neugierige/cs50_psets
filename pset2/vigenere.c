#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) 
{
    if (argc != 2) {
        printf("Please enter a keyword of alphabetical letters.");
        return 1;
    } 
    char* key = argv[1];
    for (int i = 0, j = strlen(key); i < j; i++) {
        if (isalpha(key[i])) {
            key[i] = tolower(key[i]);
        } else {
            printf("can't have non-alphas in the key");
            return 1;
        }
    }
    
    string input_str = GetString();
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0, ii = 0, j = strlen(input_str); i < j; i++) {
        int alpha_offset = 97;
        int checkUpper = 0;
        if (isupper(input_str[i])) {
            alpha_offset = 65;
            checkUpper = 1;
        } 
        
        int index_for_key = ii % (strlen(key));
        int cipher_offset = (int)key[index_for_key] - 97;
        
        if (!isalpha(input_str[i])) {
            printf("%c", input_str[i]);
        } else {
            int mod_index = ((int)input_str[i] - alpha_offset + cipher_offset)%26;
            if (checkUpper == 1) {
                printf("%c", toupper(alphabet[mod_index]));
            } else {
                printf("%c", alphabet[mod_index]);
            }
            ii ++;
        }
    }
    printf("\n");
    return 0;

}