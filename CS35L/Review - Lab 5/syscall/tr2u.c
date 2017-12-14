//
//  main.c
//  tr2u
//
//  Created by Kaela Polnitz on 10/31/17.
//  Copyright © 2017 Kaela Polnitz. All rights reserved.
//
//same as tr2b
//look for duplicates, wrong number of arguments, etc.
//from (what we want to translate), to (what it will be replaced with)
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, const char * argv[]) {
    const char* from;
    const char* to;
    from = argv[1];
    to = argv[2];
    

    if(argc!=3)
    {
        fprintf(stderr, "Wrong number of arguments! \n");
        return 1;
    }

    
    
    int lengthA = 0;
    int lengthB = 0;
    for (int k = 0;from[k] != '\0'; k++)
    {
        lengthA++;
    }
    
    for (int l = 0; to[l] != '\0'; l++)
    {
        lengthB++;
    }
    //printf("Your lengths: \n");
    //printf("%d", lengthA);
    //printf("\n");
    //printf("%d", lengthB);
    //printf("\n");
    if(lengthA != lengthB)
    {
        fprintf(stderr, "The lengths are not the same! \n");
        return 1;
        
    }
    
    for (int i = 0; i < lengthA; i++)
    {
        for (int j = 0; i < lengthA; i++)
        {
            if (i == j)
                j++;
            if(from[i] == from[j])
            {
                fprintf(stderr, "Sorry, you have duplicates!\n");
                return 1;
            }
        }
    }
    
    char currChar;
    bool match = false;
    int k = 0;
   
    
    //basically, if we find it in our 'key', we change it
    //with what we want to turn it INTO
    //if not, we are just going to print what we got from our scan
    
        while(read(STDIN_FILENO, &currChar, 1) != 0)
        {
            //check to see if it is something that can be translated
            for(int iterator = 0; from[iterator] != '\0'; iterator++)
            {
                //search in the key
            match = false;
               if(currChar == from[iterator])
               {
                   match = true;
                   write(STDOUT_FILENO, &to[iterator], 1);
                   //we don't have duplicates so no point in looking
                   //through loop
                   break;
               }
            }
            if(match == false)
            {
                write(STDOUT_FILENO, &currChar, 1);
            }
            
        }

    
    return 0;
}
