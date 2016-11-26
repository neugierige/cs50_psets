#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 45
#define DICTIONARY "dictionaries/large"

typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;

node* hash_table [676];


int main(int argc, char* argv[])
{
    // char word[20];
    // // int diff;
    // printf("word please: ");
    // scanf("%s", word);
    
    // int str_length = strlen(word);
    // char* lowercase = malloc(sizeof(char) * str_length);
    // for (int i = 0; i < str_length; i++)
    // {
    //     lowercase[i] = tolower(word[i]);
    //     // printf("lowercase[i] is %c\n", lowercase[i]);
    // }
    // lowercase[str_length] = '\0';
    // printf("%c\n", lowercase[str_length]);
    
    // // int hash_index = lowercase[0] - 'a';
    // printf("my word is %s\n", lowercase);
    
    
    // for (int i = 0, n = strlen(word); i < n; i++)
    // {
    //     word[i] = tolower(word[i]);   
    //     printf("current char is %c\n", word[i]);
    //     diff = word[i] - 'a';
    //     printf("the diff is %i\n", diff); 
    // }
    
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;
    
        FILE* file = fopen(dictionary, "r");
        //check if dictionary is null
        if (file == NULL)
        {
            printf("File is null.");
            return false;
        }
    
        char* my_word = malloc((LENGTH+1) * sizeof(char));
        int index = 0;
        
        for (char my_char = fgetc(file); my_char != EOF; my_char = fgetc(file))
        {
            node* new_node = malloc(sizeof(node));
            if (isalpha(my_char) || (my_char == '\'' && index > 0)) 
            {
                my_word[index] = tolower(my_char);
                index++;
            }
            else if (index > 0)
            {
                // end of a word
                my_word[index] = '\0';
                strcpy(new_node->word, my_word);
                
                new_node->next = NULL;
            
                //insert into hashtable
                int char_index = 1;
                while (my_word[char_index] == '\'')
                {
                    index++;
                }
    
                int bucket_number = (my_word[0] -'a' + 1) * (my_word[char_index] - 'a' + 1);
                printf("bucket_number for %s is %i\n", my_word, bucket_number);
            
                // if it's the 1st word in that bucket
                if (hash_table[bucket_number] == NULL)
                {
                    hash_table[bucket_number] = new_node;
                    printf("1st node in new bucket number %d\n", bucket_number);
                } 
                else
                {
                    node* cursor = hash_table[bucket_number];
                    cursor->next = new_node;
                    cursor = cursor->next;
                }
            
                index = 0;
            }
            else
            {
                printf("in the ELSE");
            }
        }
        
        fclose(file);
        return true;
}