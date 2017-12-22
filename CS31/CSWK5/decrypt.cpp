//
//  main.cpp
//  CSWK7
//
//  Created by Kaela Polnitz on 5/17/17.
//  Copyright © 2017 Kaela Polnitz. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>

using namespace std;

const int MAXLENGTH = 70;
const int MAX_LENGTH = 80;
const int KEY_LENGTH = 28;
const char defaultkey[KEY_LENGTH] = "00000000000000000000000000 "; //predetermined key with all 0s (not letters)

bool decrypt(const char ciphertext[], const char crib[]);
bool makeAMap(char message[], char cipher[], char map[], char key[], int pos);
int findAWord(char message[], const char cipher[], char map[], int pos); //finds pos of beginning of word w/ right syntax
bool makeTheDecryption(char cipher[],char key[]); //decrypts the ciphertext with the given key


int main()
{
   
}
//convert to C strings

bool decrypt(const char ciphertext[], const char crib[])
{
 
    if (strlen(crib) == 0) //if empty return false
        return false;
    
    
    char message[80];// copy of the crib
    char copyOfCipher[80];
    char copyOfKey[28];
    
    
    strcpy(copyOfKey, defaultkey);          //copy key into a modifiable array
    strcpy(message, crib);                  //copy crib into a modifable array
    strcpy(copyOfCipher, ciphertext);       //copy cipher into a modifiable array
    
    
    for(int k = 0; message[k] != '\0'; k++)
    {
        
        if(!isalpha(message[k]) && k == 0)              //run the crib through several loops to get rid of unnecessary characters
        {
            while (!isalpha(message[0]))
                
            {
                
                int s = 0;
                while (message[s] != isalpha(message[s]))
                {
                    
                    message[s] = message[s+1];
                    s++;
                    
                }
                
            }
            
        }
        
        
        else if(!isalpha(message[k]) && k == strlen(message) - 1)
        {
            int z = strlen(message) - 1;
            
            while (!isalpha(message[z]))
            {
                message[z] = '\0';
                z--;
            
            
            }
        }
        else if (!isalpha(message[k]) && k != strlen(message) - 1 && k != 0)
        {
            //cerr << "It gets there when " << k << endl;
            if(isalpha(message[k-1]))
                message[k] = ' ';
            else
            {
                
                int o = k;
                while (!isalpha(message[o]))
                {
                   //cerr << message << endl;
                    
                    while (message[o] != isalpha(message[o]) && o < strlen(message))
                    {
                      
                        message[o] = message[o+1];
                        o++;
                    
                        
                    }
                    break;
                
                }
                k--;
            }
            
            
        }
        
        
    }
    
    for (int i = 0; message[i] != '\0'; i++)
    {
        int m = message[i];
        message[i] = tolower(m);
    }
    
    //cerr << "Final Message: " << message << endl;
    
    
    //----------------------------Done checking the crib-------------------------------//
    
    
    for(int j = 0; copyOfCipher[j] != '\0';j++)
    {
        if(copyOfCipher[j] == '\n')
            continue;
        if(!isalpha(copyOfCipher[j]) && j == 0)      //run the cipher through several loops to get rid of unnecessary characters
                                                     //we handle \n by not looking for it; stays in print
        {
            while (!isalpha(copyOfCipher[0]))
                
            {
                
                int t = 0;
                while (copyOfCipher[t] != isalpha(copyOfCipher[t]))
                {
                    
                    copyOfCipher[t] = copyOfCipher[t+1];
                    t++;
                    
                }
                
            }
            
        }
        
        
        else if(!isalpha(copyOfCipher[j]) && j == strlen(copyOfCipher) - 1)
        {
            int a = strlen(copyOfCipher) - 1;
            
            while (!isalpha(copyOfCipher[a]))
            {
                copyOfCipher[a] = '\0';
                a--;
                
                
            }
        }
        else if (!isalpha(copyOfCipher[j]) && j != strlen(copyOfCipher) - 1 && j != 0)
        {
         
            if(isalpha(copyOfCipher[j-1]))
                copyOfCipher[j] = ' ';
            else
            {
                
                int p = j;
                while (!isalpha(copyOfCipher[p]))
                {
                 
                    
                    while (copyOfCipher[p] != isalpha(copyOfCipher[p]) && p < strlen(copyOfCipher))
                    {
                        
                        copyOfCipher[p] = copyOfCipher[p+1];
                        p++;
                        
                        
                    }
                    break;
                    
                }
                j--;
            }
            
            
        }
        
        
    }
    
    for (int l = 0; copyOfCipher[l] != '\0'; l++)
    {
        int s = copyOfCipher[l];
        copyOfCipher[l] = tolower(s);
    }
    
    //cerr << "Final Cipher: " << copyOfCipher << endl;
    
    
    //----------------------------Done checking the cipher-------------------------------//
    
    //MAPPING STAGE
    char copyofCipher[80];
    strcpy(copyofCipher, ciphertext);
    char valueMap[80];
    int pos = 0;

   
    for (int l = 0; l < strlen(copyofCipher); l++)
        copyofCipher[l] = tolower(copyofCipher[l]);
    
 
    while (pos != -1 && pos < strlen(copyofCipher))                                      //constant loop of checking for the correct key
    {
      
        
        pos = findAWord(message, copyOfCipher, valueMap, pos);
        //cerr << "Your position in cipher is: " << pos << endl;
        //cerr << "You're looking at position " << pos << " of the string" << endl;
        //cerr << "You're looking at " << copyOfCipher[pos] << endl;
        if (pos == -1 || pos >= strlen(copyofCipher))                                   //if not a valid place in the cipher, return false
            return false;
        if(makeAMap(message, copyOfCipher, valueMap, copyOfKey, pos))                   //if key works, move on to decryption
            break;
    
        else                                            //if making the key above doesn't work, then you must go to the beginning of the next word
        {
            //cerr << "It is not the correct key" << endl;
            
            for(int t = pos; t < strlen(copyofCipher); t++)
            {
                if(copyofCipher[t] == ' ')
                {
                    if(isalpha(copyofCipher[t+1]))
                    {
                        pos = t+1;
                        break;
                        
                    }
                
                }
                
                if(t >= strlen(copyofCipher))
                    return false;
            }
           
            
        }
        

    }
    if (pos == -1 || pos >= strlen(copyofCipher))     //if not a valid place in the cipher, return false
        return false;
    
char cipherForDecryption[80];
strcpy(cipherForDecryption, ciphertext);             //make a cipher that can be edited and printed
//cerr << cipherForDecryption << endl;
makeTheDecryption(cipherForDecryption, copyOfKey);
    
    cout << cipherForDecryption << endl;

        return true;
  
    
}

int findAWord(char message[], const char cipher[], char map[], int pos) //checks to see if it is the beginning of the crib, checking syntax
{
    
    
    
    for (int k = pos; k < strlen(cipher); k++)                      //less than string length because you might not explicitly run into the zero byte
    {
        
        
        
        if (k == pos || cipher[k-1] == ' ' || cipher[k-1] == '\n')  //accounting for new line character
        {
            
            bool isItAMatch = true;
            
            int posInCrib = 0;
            
            
            while(posInCrib < strlen(message))
            {
                //cerr << cipher[k+posInCrib] << " " << message[posInCrib] << endl;
           
                if(cipher[k+posInCrib] != '\n' && ((isalpha(cipher[k+posInCrib]) && isalpha(message[posInCrib])) || (!isalpha(cipher[k+posInCrib]) && !isalpha(message[posInCrib])))) //if they are both letters or both not letters, or if the cipher is starting a new line
                {
                 
                   
                    posInCrib++;
                    
                }
                
                else
                {                                                   //if it doesn't satisfy the above conditions, it's not a match
                    //cerr << "It should get here at some point " << endl;
                    isItAMatch = false;
                    break;
                }
                
                
            }
          
            
                if(isItAMatch)
                {
                    if(isalpha(cipher[k+strlen(message)]) && k + strlen(message) < strlen(cipher)) // if the next word in the cipher is a letter, then it must not match
                        isItAMatch = false;
                    
                    //otherwise, continue looking
                    else
                        return k;
                }
            
            if (!isItAMatch)   //if it isn't a match, find the beginning of the next work
            {
            for(int positionInCipher = k; positionInCipher < strlen(cipher); positionInCipher++)
            {
              
                if(cipher[positionInCipher] == ' ')
                {
                    if(isalpha(cipher[positionInCipher+1]))
                    {
                        return positionInCipher+1;
                        
                    }
                    
                }
                
                if(positionInCipher >= strlen(cipher))
                    return -1;
            }
            }
            
        }
    
    }
    
    return -1; //otherwise the position cannot be found
}

bool makeAMap(char message[], char cipher[], char map[], char key[], int pos)
{
    
    int keyPos;
    strcpy(key, defaultkey);
    for (int i = pos; i < strlen(message) + pos; i++)                               //i-pos - position inside of the crib
    {
        //cerr << "You are looking at " << message[i-pos] << endl;

        if (message[i-pos] == ' ')
            continue;
        if (isalpha(message[i-pos]))
        {
            
            keyPos = cipher[i] - 'a';
            
            if(key[keyPos] != '0')
            {
                
               if( key[keyPos] != message[i-pos])
                   return false;
            }
            else
            {
               key[keyPos] = message[i-pos];
            }
            
        }
    }
    
    //cerr << "Your key looks like " << key << endl;
    return true;
}



bool makeTheDecryption(char cipher[],char key[])
{
    char cipherToDecrypt[80];
    strcpy(cipherToDecrypt, cipher);
    
    for (int z = 0; cipherToDecrypt[z] != '\0'; z++)
    {
        int f = cipherToDecrypt[z];
        cipherToDecrypt[z] = tolower(f);
    }
    
  
    for(int i = 0; i < KEY_LENGTH - 1; i++)
        key[i] = toupper(key[i]);
    
    for (int j = 0; j < strlen(cipherToDecrypt); j++)
    {
    
        if(key[cipherToDecrypt[j] - 'a'] != '0' && isalpha(cipherToDecrypt[j]))
            cipherToDecrypt[j] = key[cipherToDecrypt[j] - 'a'];
        
    }
    
    //cerr << "Your cipher message now: " << cipherToDecrypt << endl;
    strcpy(cipher, cipherToDecrypt);
    return true;
}

