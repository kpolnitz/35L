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

//#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h> //for memcmp
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <sys/syscall.h>
//ends with a space, not a /0
bool fFlag = false;
void output(const char* a)
{
    while(*a != ' ')
    {
        a++;
        write(1,&(*a), 1);
    }
    return;
}

void checkMem(void * a)
{
    if (a == NULL)
    {
        //printf("Memory allocation could not be completed.\n");
        exit(1);
    }
    
}

int frobcmp (char const* a, char const* b)
{
    //in the style of memcmp
    bool diff = false;
    bool isItSpaceA = false;
    bool isItSpaceB = false;
    if (fFlag == true)
    {
        //if it has -f selected, we are sending everything to upper
        while(*a != ' ' && *b != ' ')
        {
            //we are going to look byte by byte for comparison to see if they're different letters
            if (toupper((*a ^ 42)) != toupper((*b ^ 42)))
            {
                diff = true;
                if (*a != ' ' && *a != ' ')
                {
                    if (toupper((*a ^ 42)) < toupper((*b ^ 42)))
                    {
                        return -1;
                    }
                    if (toupper((*a ^ 42)) > toupper((*b ^ 42)))
                    {
                        return 1;
                    }
                }
            }
            
            a++;
            b++;
            
        }
        
        
        
    }

    //fix bug: not displaying * and #
    
    else {
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


int main(int argc, char *argv[]) {
    //we are gonna get characters, character by character
    //wwe will note how many words we have also
    //we can start off with arbitrary memory and double it if needed
    //if srob receives something empty, immediately return
    
    
    //Assignment 5 Notes:
    //If a regular file allocate all at once
    int arbMem = 30;
    //int doubledMem = arbMem; //number will be used for reallocating memory
    char* allWords;
    char** newWords;
    
     //we need to keep track of words formed
    char findChar;
    size_t numOfWords = 0;
    size_t a = 0;
    long err = 0;

    //note memory allocation failures - would be null
    //do this everytime memory is being allocated
    struct stat fileThings;
    fstat(STDIN_FILENO, &fileThings);
    size_t sizeOfFile = fileThings.st_size;
    //we want to check arguments, so program doesn't run with wrong arguments
    /*if (argc < 2)
    {
        char errorMessage[] = "Error: Not enough arguments! \n";
        write(2, &errorMessage, sizeof(errorMessage));        //not enough arguments!
        return 1;
    }*/
    if (argc >= 2)
    {
        for (int j = 1; j < argc; j++)
        {
            if (!strncmp(argv[j], "-f", 2))
            {
                fFlag = true;
                break;
            }
            else if (j == argc - 1)
            {
                char errorMessage[] = "There is no -f argument! \n";
                write(2, &errorMessage, sizeof(errorMessage));
            }
      
        
        }
    }
    
   //ssize_t - can be read or written in operation, must signed
    if (err < 0)
    {
        char errorMessage[] = "Error: fstat didn't work.";
        write(2, &errorMessage, sizeof(errorMessage));
        return 1;
    }
    
    //checkMem(allWords);
    if(S_ISREG(fileThings.st_mode))
    {
        //printf("You get in here");
        allWords = (char*)malloc(sizeOfFile);
        //+1 - for space
        //allocate it all at once
        checkMem(allWords);
        err = read(STDIN_FILENO, allWords, sizeOfFile);
       
    //printf("We are getting output:");
    }
    else
    {
        allWords = (char*)malloc(sizeof(char)*arbMem);
        checkMem(allWords);
        
    
    }
    
    //Note: if file grows, add more memory
    while(read(STDIN_FILENO, &findChar, 1)>0)
    {
    
        //check to see if file is still growing
        if(a == arbMem)
        {
            arbMem *=2;
            allWords = (char*)realloc((allWords), arbMem);
            checkMem(allWords);
            
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
    }
    if(a == arbMem)
    {
        arbMem *= 2;
        allWords = (char*)realloc(allWords, sizeof(char)*arbMem);
        checkMem(allWords);
    }
    //we need to add space to end of words
    if (allWords[a-1] != ' ')
    {
        allWords[a] = ' ';
        numOfWords+=1;
    }
    //printf("end of loop\n");
    
    //you'll need space for your SPACE

    //we need to add space to end of words

    newWords = (char**)malloc(sizeof(char*)*numOfWords);
    checkMem(newWords);
    
    int c = 0;
    while (c < numOfWords)
    {
        //we look at words until we get to the last word
        newWords[c] = allWords;
        
        if (c+1 == numOfWords) break;
        
        while ((*allWords) != ' ')
        {
            allWords++;
        }
        c+=1;
        allWords++;
        
    }
    //get the words then sort them
    //printf("Right before q sort\n");
    //breakpoint here
    //printf("After sort\n");
    
    qsort(newWords, numOfWords, sizeof(char*), frobFunc);
    
    //print the output
    
    //char Message[] = "Well you get past qsort\n";
    //write(2, &Message, sizeof(Message));
    int j = 0;
    
    
    while(j < numOfWords)
    {
        //printf("You got in here \n");
        write(1,&(*(newWords[j])),1);                        //STDIO FUNC
        output(newWords[j]);                                 //STDIO FUNC
        j+=1;
    }
    
    
/*    if(j == 0)
    {
        printf("You have no output\n");
        return 1;
    }
 */
 
    //essentially though, you'll only get here if you have errors
    //empty input is already taken care of
    //free all the memory at the end
    free(newWords);
    //we can't free oneWord and allWord
    //printf("Well you got to the end of the code");
    return 0;
}
//you must make executable before runing test cases oin shell
//report errors!!!!
//input, output, memory allocation failures
//delete unused pointers, caused memory leak!!
