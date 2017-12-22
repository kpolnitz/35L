//
//  main.cpp
//  CSWK6
//
//  Created by Kaela Polnitz on 5/10/17.
//  Copyright © 2017 Kaela Polnitz. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <cassert>
using namespace std;

int enumerate(const string a[], int n, string target);
int locate(const string a[], int n, string target);
bool locateSequence(const string a[], int n, string target, int& begin, int& end);
int locationOfMin(const string a[], int n);
int moveToEnd(string a[], int n, int pos);
int moveToBeginning(string a[], int n, int pos);
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int eliminateDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int divide(string a[], int n, string divider);



int main()
{
    string h[7] = { "malory", "sterling", "lana", "cheryl", "", "cyril", "lana" };
    assert(enumerate(h, 7, "lana") == 2);
    assert(enumerate(h, 7, "") == 1);
    assert(enumerate(h, 7, "krieger") == 0);
    assert(enumerate(h, 0, "lana") == 0);
    assert(locate(h, 7, "lana") == 2);
    assert(locate(h, 2, "lana") == -1);
    int bg;
    int en;
    assert(locateSequence(h, 7, "cheryl", bg, en) && bg == 3 && en == 3);
    
    string g[4] = { "malory", "sterling", "cheryl", "cyril" };
    assert(locationOfMin(g, 4) == 2);
    assert(locateDifference(h, 4, g, 4) == 2);
    assert(subsequence(h, 7, g, 4));
    assert(moveToEnd(g, 4, 1) == 1 && g[1] == "cheryl" && g[3] == "sterling");
    
    string f[4] = { "cyril", "cheryl", "sterling", "lana" };
    assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "sterling" && f[2] == "cheryl");
    
    string e[5] = { "cyril", "cyril", "cyril", "sterling", "sterling" };
    assert(eliminateDups(e, 5) == 2 && e[1] == "sterling");
    
    string x[4] = { "cyril", "krieger", "krieger", "pam" };
    string y[4] = { "cheryl", "krieger", "lana", "sterling" };
    string z[10];
    assert(makeMerger(x, 4, y, 4, z, 10) == 8 && z[5] == "lana");
    
    assert(divide(h, 7, "lana") == 3);

    
}

int enumerate(const string a[], int n, string target) //return number of strings = target
{
    if (n < 0)
        return -1;
    int occurences = 0;                               //counts how many times it has been seen
    for (int i = 0; i < n; i++)
    {
        
            if(a[i] == target)
                occurences += 1;
    
    }
   
    return occurences;
}

int locate(const string a[], int n, string target)    //return position of string = target
{
    if (n < 0)
        return -1;
    int located;                                      //position of located string
    for (int j = 0; j < n; j++)
    {
        if (a[j] == target)
        {
            located = j;
            return located;
        }
    }
        return -1;
    
}

bool locateSequence(const string a[], int n, string target, int& begin, int& end) //earliest consecutive occurrence of target
{
    if (n < 0)
        return false;
    for(int k = 0; k < n; k++)
    {
        
        if(a[k] == target)
        {
            begin = k;
            end = k;
            for (int v = k+1; v <= n; v++)
            {
                if (a[k] == a[v])
                    end = v;
                else
                    return true;
                
            }
            
            
        }
        
        
    }
 
      return false;
    
}

int locationOfMin(const string a[], int n)
{
    
    if (n <= 0)
        return -1;
    int p = 0;
    for(int minPos = 0; minPos < n; minPos++)
    {
        for(p = 0; p < n; p++)
        {
            if(a[minPos] > a[p])
                break;
                
        }
        if(p == n)
            return minPos;
    }

    return 0;       //ideally, this should never be reached
}


int moveToEnd(string a[], int n, int pos)
{
    if (n <= 0)     //if the array is 0 or less, there are no positions to check
        return -1;
    if (pos < 0)    //position cannot be negative
        return -1;
    if (pos >= n)   //position cannot be greater than the positions in the array (i.e -- you can't look for position 6 in an array with size 6)
        return -1;
    string movingString = a[pos]; //string that is going to be moved the end
    
    for (int m = 0; m < n; m++)
    {
        if (m > pos)
            a[m-1] = a[m];
        
    }
    a[n-1] = movingString;       //sets it as the last string
    
    for (int m = 0; m < n; m++)
        cerr << a[m] << endl;
    return pos;
    
}

int moveToBeginning(string a[], int n, int pos)
{
    if (n <= 0)                       //can't move strings with a pos that is not in the array (no 0 pos, etc. in a zero/negative array)
        return -1;
    if (pos < 0)                      //can't have a negative position in an array
        return -1;
    if (pos >= n)                     //can't have a position that is more than given
        return -1;
    string anotherMovingString = a[pos];
    
    for (int m = pos; m > 0; m--)
    {
        
            a[m] = a[m-1];            //shifts everthing to the right to make room for the string in the beginning
        
    }
    a[0] = anotherMovingString;       //sets the first position to be the moved string
    
    for (int m = 0; m < n; m++)
        cerr << a[m] << endl;
  
    return pos;
}


int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    int smallestN;
    if (n1 < n2)
        smallestN = n1;
    else
        smallestN = n2;
    
    int pos = 0;
    
    for(int j = 0; j < smallestN; j++)
    {
       if(a1[j] != a2[j])
       {
           pos = j;
           return pos;
       }
        
    }
    
    return smallestN;                  //if you get through the entire smaller string,
                                       //then the difference will the position after the last position of the smaller string
}

int eliminateDups(string a[], int n)
{
    if (n < 0)
        return -1;
    
    int dups = 0;
    
    for(int k = 0; k < n - 1; k++)
    {
       int target = k + 1;
        
        if(a[k] == a[target])
        {
            dups++;
            
            for(int j = target; j < n - 1; j++)     //if there is a duplicate, the items after it will be moved down (deleting it)
            {
                a[j] = a[j + 1];
                
            }
            
        k = k - 1;                                 //checks again for the duplicate
        n = n - 1;                                 //decreases the array after scooting all of the strings up
            
                
        }
        
    
    }
    
    for (int j = 0; j < n; j++)
        cerr << a[j] << endl;
    
    cerr << "The number of duplicates is: " << dups << endl;
    cerr << "The length of the string without duplicates is: " << n << endl;

    return n;
}


bool subsequence(const string a1[], int n1, const string a2[], int n2)

{
   
    int subLen = n2;                              //easier to understand
    int Len = n1;
    
    if(subLen > Len || subLen < 0 || Len < 0)
        return false;
  
    
    int subLenPos = 0;
    
    for(int k = 0; k < Len; k++)
    {
        
        
        if(a1[k] == a2[subLenPos])
        {                                         //if the longer string has not matched it, it will go into loop until it finds it
            cerr << "Did it get here?" << endl;
            subLenPos++;
        }
      
        if(subLenPos == subLen)
            break;
        
        
    }
    cerr << subLen << " and " << subLenPos << endl;
    
    
    if(subLenPos != subLen)                       //number of matches should be equal to the length of the string
        return false;
    
    return true;
}


int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
                                                 //going to go through the first string to make sure it's in alphabetical order
    
    if(n1 < 0 || n2 < 0)
        return -1;
    if(n1 + n2 > max)
        return -1;
    
    for(int i = 0; i < n1 - 2; i++)
    {
        
             if(a1[i] > a1[i + 1])
                return -1;
    
    }
    
                                                //going to go through the second string to make sure it's in alphabetical order
    for(int j = 0; j < n2 - 2; j++)
    {
        
            if(a2[j] > a2[j + 1])
                return -1;
    }
    
    
  
    
    
    int i = 0; //counter for the first string
    int j = 0; //counter for 2nd string
    int k = 0; //counter for result
    

    //checking for order to put into result
    
while ( i < n1 && j < n2)
{
    cerr << a1[i] << " and " << a2[j] << endl;
    
  if (a1[i] <= a2[j])
  {
      result[k] = a1[i];  //you add to the result array the item of the first array then move the position of the result and first array
      i++;
      k++;
  }

  else
  {
      result[k] = a2[j];  //you add to the result array the item of the first string then move the position of the result and second array
      j++;
      k++;
      
  }

}
    
   if (i == n1)
   {                                                 //if the first array ends, add the rest of the second array
       for (int l = j; l < n2; l++)
       {
           result[k] = a2[l];
           k++;
       }
   }
   else if (j == n2)                                 //if the second array ends, add the rest of the first array
   {
       for (int m = i; m < n1; m++)
       {
           result[k] = a1[m];
           k++;
       }
       
   }
    
    
    
    for (int p = 0; p < n1+n2; p++)                  //prints the resulting string
    {
        cerr << result[p] << endl;
     
    }
        cerr << "----------------" << endl;
    return n1+n2;
}
 


//smaller than divider, before. greater than divider, after
int divide(string a[], int n, string divider)
{
    
    int posofTemp = 0;
    int returnvalue;
    if (n < 0)
        return -1;
    string dividedArray[100];                     //make an array that could hold all of the divided items
    for(int k = 0; k < n; k++)
    {
            if(a[k] < divider)
            {
                dividedArray[posofTemp] = a[k];   // if < divider, it will add these parts first
                posofTemp++;                      //keeps track of the last value < divider
            }
    }
   
    returnvalue = posofTemp;
    for(int t = 0; t < n; t++)
    {
        if(a[t] == divider)                      // if == divider, it will add these parts next (needs to be in middle)
        {
            dividedArray[posofTemp] = a[t];
            posofTemp++;
        }
        
    }
    for(int m = 0; m < n; m++)
    {
            if(a[m] > divider)                   // if > divider, it will add these parts next
            {
                dividedArray[posofTemp] = a[m];
                posofTemp++;
            }
        
    }
    
    for(int o = 0; o < n; o++)
    {
        a[o] = dividedArray[o];                 //copies content into the original array
    }
    
    for(int p = 0; p < n; p++)                  //prints new array with division
        cerr << a[p] << endl;
    return returnvalue;
    
}
 
