//
//  main.c
//  tr2b
//
//  Created by Kaela Polnitz on 10/31/17.
//  Copyright © 2017 Kaela Polnitz. All rights reserved.
//

//The tr utility shall copy the standard input to the standard
//output with substitution or deletion of selected characters.
//The options specified and the string1 and string2 operands
//shall control translations that occur while copying characters
//and single-character collating elements.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



//header includes putchar and setchar

int main(int argc, char* argv[]) {
    // insert code here...
    //arg[0] == program
    //arg[1] == from
    //arg[2] == to
    //  if not same length, do not even go, report error
    //  if from has duplicates, error
    //mixture of previous projects
    //mapping type: from - abc and to - def, we want to
    //replace characters with from
    char* from = argv[1];
    char* to = argv[2];
    char currChar;

    //check for same length
    

    //check for # of arguments
    if(argc != 3)
    {
        printf("You have the wrong number of arguments! Can't be executed. \n");
        return 1;
        
    }
    //we will check for duplicate bytes in loop
    
    int lengthA = 0, lengthB = 0;
    int i = 0;
    while (from[i] != '\0')
    {
        lengthA++;
        i++;
    }
    i = 0;
    while(to[i] != '\0')
    {
        lengthB++;
        i++;
        
    }
    
    if (lengthA != lengthB)
    {
        printf("Strings are NOT the same length! Can't be executed. \n");
        return 1;
    }
    
    for (int a = 0; a < lengthA; a++)
    {
        for (int b = 0; b < lengthB; b++)
        {
                if (a == b)
                    continue;
                if (from[a] == from[b])
                {
                    printf("Error, you have duplicate bytes! Can't be executed. \n");
                    return 1;
                }
        }
    }
    bool isitMatch = false;
    currChar = getchar();
    int c = 0;
    //be the same at this point
        //if a character of translation, translate
        //otherwise, just print the character
    while (currChar != EOF) {
  
        while (from[c] != '\0')
        {
            isitMatch = false;
            if (currChar == from[c])
            {
                putchar(to[c]);
                isitMatch = true;
                break;
            }
            c++;
        }
        
        if(isitMatch == false)
        {
            putchar(currChar);
        }
        
        currChar = getchar();
    }
    
    return 0;
}
