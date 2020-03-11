#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
	int maxLength = 16;
	int length = 0;
	char* word = malloc(sizeof(char) * maxLength);
	while (1)
	{
		char c = fgetc(file);
		if ((c >= '0' && c <= '9') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') ||
			c == '\'')
		{
			if (length + 1 >= maxLength)
			{
				maxLength *= 2;
				word = realloc(word, maxLength);
			}
			word[length] = c;
			length++;
		}
		else if (length > 0 || c == EOF)
		{
			break;
		}
	}
	if (length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
	// FIXME: implement
	assert(file != 0);
	assert(map != 0);

	char* currentWord = nextWord(file);

	while (currentWord != 0)
	{
		hashMapPut(map, currentWord, -1);
		free(currentWord);
		currentWord = nextWord(file);
	}
}

/**
 * Takes in the user input for the word and converts it to a lowercase. It will return null if invalid. Returns pointer to lowercase version of input.
 * parameters: char pointer (string)
 * return: char pointer (string).
 **/

char* inputValidation(char* input)
{
	//Defines the length of the longest word possible and length controls iteration of string arr.
	int max = 100;
	int i = 0;

	//Creates an arr of char(string) that is has a max capacity of 100.
	char word = malloc(sizeof(char) * max);


	while (i < max)
	{
		//Stores the char it will check in the iteration.
		char c = input[i];

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			//Store a lower case version of the character at index length in newly allocated word arr (string).
			word[i] = (char)tolower(c);
			i++;

			//Checks if the next index in the char arr is a null terminator indicating it is the end of the input.
			//If it is found, then it will break the loop.
			if (input[i] == '\0')
			{
				break;
			}
		}
		else //If input[i] not a char, then it returns null. Meaning, it is not a word.
		{
			free(word);
			return 0;
		}

	}

	//This is reached if the end of the word is reached, by reaching the null terminator...
	//after breaking out of the while-loop.
	word[i] = '\0';
	return word;
}


/**
 * Checks the spelling of the word provded by the user. If the word is spelled incorrectly,
 * print the 5 closest words as determined by a metric like the Levenshtein distance.
 * Otherwise, indicate that the provded word is spelled correctly. Use dictionary.txt to
 * create the dictionary.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);

    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);

    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);

        // Implement the spell checker code here..

        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }

    hashMapDelete(map);
    return 0;
}
