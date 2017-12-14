//
//  main.cpp
//  Lab4
//
//  Created by Kaela Polnitz on 10/26/17.
//  Copyright © 2017 Kaela Polnitz. All rights reserved.
//

//we check to see if the two strings are the same
//encrypt the strings
//compare the encrypted strings
//a < b: -1
//a == b: 0
//a > b: 1
//use malloc, realloc, free, qsort
//malloc - original
//realloc - adding onto previously created memory
//free - freeing up space
//qsort - sorts an array of nel objects (specified width)
//  -already-made function
//encrypted via memfrob
// we need to allocate space for words, and add more if needed
//EOF = End of File
//you need a helper function
//trigger EOF with Control+D
//internet: "The memfrob() function encrypts the first
//n bytes of the memory area s by exclusive-ORing
//each character with the number 42." (linux.die.net)

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> //for memcmp
//ends with a space, not a /0
void output(const char* a)
{
    while(*a != ' ')
    {
        a++;
        putchar(*a);
    }
    return;
}

void checkMem(void * a)
{
    if (a == NULL)
    {
        printf("Memory allocation could not be completed.\n");
        exit(1);
    }
    
}

int frobcmp (char const* a, char const* b)
{
    //in the style of memcmp
    bool diff = false;
    bool isItSpaceA = false;
    bool isItSpaceB = false;
    
    //fix bug: not displaying * and #
    
    
    while(*a != ' ' && *b != ' ')
    {
        //we are going to look byte by byte for comparison to see if they're different letters
        if ((*a ^ 42) != (*b ^ 42))
        {
            diff = true;
            if (*a != ' ' && *a != ' ')
            {
                if ((*a ^ 42) < (*b ^ 42))
                {
                    return -1;
                }
                if ((*a ^ 42) > (*b ^ 42))
                {
                    return 1;
                }
            }
        }
        
                           a++;
                           b++;
        
    }
    //we want to see if there are spaces at the end of the comparisons
    
    if (*a == ' ')
    {
        isItSpaceA = true;
    }
    if (*b == ' ')
    {
        isItSpaceB = true;
    }
    //if they are the same so far but we are unsure which one is longer than the other
    if (!diff)
    {
        
        if (isItSpaceA && !isItSpaceB)
        {
            //if they are the same up to a certain point, one is just shorter than the other
            //ex: abc and abcdef
            //printf("You encountered this \n");
            return -1; //because a < b
        }
        else if (!isItSpaceA && isItSpaceB)
        {
            //same thing, but reversed of above
            return 1; //a > b
        }
    }
    return 0;
    //otherwise, they are equal
    //breakpoint here
}




int frobFunc(const void *a, const void *b)
{
    //printf("You made it to the frobFunc \n");
    return frobcmp(*((char**)a), *((char**)b));
}


int main() {
    //we are gonna get characters, character by character
    //wwe will note how many words we have also
    //we can start off with arbitrary memory and double it if needed
    //if srob receives something empty, immediately return
    int arbMem = 30;
    int doubledMem = arbMem; //number will be used for reallocating memory
    char* allWords;
    
    allWords = (char*)malloc(sizeof(char)*arbMem); //we need to keep track of words formed
    char findChar;
    int numOfWords = 0;
    int a = 0;
    
    //note memory allocation failures - would be null
    //do this everytime memory is being allocated
    
    checkMem(allWords);
    
    //printf("We are getting output:");
    findChar = getchar();
    
    while(findChar != EOF)
    {
        //remember: You can test EOF with Ctrl+D
        //if we are given no input, then exit.
        
        if (a == doubledMem) //if we max out, just make more space
        {
            //printf("You need more memory! \n");
            doubledMem *= 2;
            allWords = (char*)realloc(allWords, sizeof(char)*doubledMem);
            checkMem(allWords);
            //we can double them both for safety
        }
        
        if (findChar == ' ')
        {
            allWords[a] = findChar;
            a+=1;
            numOfWords+=1;
            
        }
        else
        {
            allWords[a] = findChar;
            a+=1;
        }
        findChar = getchar();
    }
    
    //printf("end of loop\n");
    
    //you'll need space for your SPACE
    if(a == doubledMem)
    {
        doubledMem *= 2;
        allWords = (char*)realloc(allWords, sizeof(char)*doubledMem);
        checkMem(allWords);
    }
    //we need to add space to end of words
    if (allWords[a-1] != ' ')
    {
        allWords[a] = ' ';
        numOfWords+=1;
    }
    
    if(allWords[0] == '\n' || allWords[0] == ' ')
    {
        printf("You have no input!\n");
        return 1;
    }
    
    char** newWords = (char**)malloc(sizeof(char*)*numOfWords);
    checkMem(newWords);
    
    int b = 0;
   
    
    char* originalAllWords = allWords;
    
    while (b < numOfWords)
    {
        //we look at words until we get to the last word
        newWords[b] = allWords;
        
        if (b+1 == numOfWords) break;
        
        while ((*allWords) != ' ')
        {
            allWords++;
        }
        b+=1;
        allWords++;
        
    }
    //get the words then sort them
    //printf("Right before q sort\n");
    //breakpoint here
    //printf("After sort\n");
    
    qsort(newWords, numOfWords, sizeof(char*), frobFunc);
    
    //print the output
    int j = 0;
    while(j < numOfWords)
    {
        //printf("You got in here \n");
        putchar(*(newWords[j]));
        output(newWords[j]);
        j+=1;
    }
    
    if(j == 0)
    {
        printf("You have no output\n");
        return 1;
    }
    //essentially though, you'll only get here if you have errors
    //empty input is already taken care of
    //free all the memory at the end
    free(newWords);
    free(originalAllWords);
    
    //we can't free oneWord and allWord
    
    //printf("Well you got to the end of the code");
    return 0;
}
//you must make executable before runing test cases oin shell
//report errors!!!!
//input, output, memory allocation failures
//delete unused pointers, caused memory leak!!
