/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"


typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;


// 26*26 "buckets"
// node* hash_table [26] = {NULL};
node* hash_table [676] = {NULL};

// to track count of words loaded
int word_count;

// hash function
int hash_function (const char* word) 
{
    int index = 1;
    if (word[index] == '\0')
    {
        return word[0] -'a' + 1;
    }
    else 
    {
        while (word[index] == '\'')
        {
            index++;
        }   
    }
    return (word[0] -'a' + 1) * (word[index] - 'a' + 1);
}


/**
 ** Loads dictionary into memory.  Returns true if successful else false.
 **/
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    //check if dictionary is null
    if (file == NULL)
    {
        printf("File is null.");
        return false;
    }
    
    char* my_word = calloc((LENGTH+1), sizeof(char));
    int index = 0;
    
    for (char my_char = fgetc(file); my_char != EOF; my_char = fgetc(file))
    {
        node* new_node = calloc(sizeof(node), 1);
        if (isalpha(my_char) || (my_char == '\'' && index > 0)) 
        {
            my_word[index] = tolower(my_char);
            index++;
        }
        else
        {
            // end of a word
            my_word[index] = '\0';
            
            // initialized new_node with values
            strcpy(new_node->word, my_word);
            new_node->next = NULL;
            
            // get bucket number
            int bucket_number = hash_function(my_word);
            
            // if it's the 1st word in that bucket
            if (hash_table[bucket_number] == NULL)
            {
                hash_table[bucket_number] = calloc(sizeof(node), 1);
                strcpy(hash_table[bucket_number]->word, new_node->word);
                hash_table[bucket_number]->next = new_node->next;
            } 
            else
            {
                // appending at the head
                new_node->next = hash_table[bucket_number];;
                hash_table[bucket_number] = new_node;
            }
            
            word_count++;
            index = 0;
            
        }
    }
    
    free(my_word);
    fclose(file);
    return true;
}


/**
 ** Returns true if word is in dictionary else false.
 **/
bool check(const char* word)
{
    int str_length = strlen(word);
    char* lowercase = malloc(sizeof(char) * str_length+1);
    for (int i = 0; i < str_length; i++)
    {
        lowercase[i] = tolower(word[i]);   
    }
    lowercase[str_length] = '\0';
    
    int hash_index = hash_function(lowercase);
    node* cursor = hash_table[hash_index];
    
    while (cursor != NULL)
    {
         if (strcmp(cursor->word, lowercase) == 0)
         {
             return true;
         } 
        cursor = cursor->next;
    }
    free(lowercase);
    return false;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}


/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < 676; i++)
    {
        free(hash_table[i]);
    }
    return true;
}
