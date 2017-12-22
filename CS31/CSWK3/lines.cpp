//
//  lines.cpp
//  picture
//
//  Created by Kaela Polnitz on 5/2/17.
//  Copyright © 2017 Kaela Polnitz. All rights reserved.
//

#include <stdio.h>
#include "graphlib.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>



using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int BG = 0;
const int FG = 1;

bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg);
int  executeCommands(string commandString, char& plotChar, int& mode, int& badPos);
bool processHV(string commandString, int& pos, int& dir, int& distance, string stringDist);
bool processfb(string commandString, int& pos, int& fgbg, char& plotChar);



void plotHorizontalLine(int r, int& c, int distance, char ch, int fgbg);
void plotVerticalLine(int& r, int c, int distance, char ch, int fgbg);
void plotRectangle(int r, int c, int height, int width, char ch);
void plotNegativeVert(int& r, int c, int distance, char ch, int fgbg);
void plotNegativeHoriz(int r, int& c, int distance, char ch, int fgbg);






int main ()
{

    int mode = FG;
    char plotChar = '*';
    int badPos;
    clearGrid();
    
  
    
    
  for (;;)
    {
      
        
        
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        cerr << "Your string was " << cmd << endl;
       

        int executionStatus = executeCommands(cmd, plotChar, mode, badPos);
        cerr << "Your return value was " << executionStatus << endl;
        if (cmd == "") //returns 0 after successful execution, exits code
            return 0;
        
        switch(executionStatus)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << badPos+1 << endl;
                break;
            case 2:
                cout << "Cannot execute command at position " << badPos+1 << endl;
                break;
            default:
                cerr << "You shouldnt get here." << endl;
                break;
        }

   
    }
}

int executeCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int changingR = 1;
    int changingC = 1;
    char changingChar = '*';
    int changingfgbg = 0;
    int loopingR = 1;
    int loopingC = 1;
    
    int differenceInC;  //amount to add to R/C every time
    int differenceInR;
    int distance = 0;
    
    for(int j = 0; j != commandString.size(); j++)  //loop that checks the string syntactically first
    {
        cerr << "Top of loop!" << endl;
        if(isalpha(commandString[j]))
        {
            cerr << "Character checking is " << commandString[j] << endl;
            
            if(commandString[j] == 'c' || commandString[j] == 'C')
            {
              
               
                if((j+1) != commandString.size())
                {
                    if(commandString[j+1] != 'h' && commandString[j+1] != 'H'
                       && commandString[j+1] != 'v' && commandString[j+1] != 'V' && commandString[j+1] != 'c' && commandString[j+1] != 'C' && commandString[j+1] != 'f' && commandString[j+1] != 'b' && commandString[j+1] != 'F' && commandString[j+1] != 'B')
                    {
                        badPos = j+1;
                        
                        return 1;
                    }
                }
            }
            else if(commandString[j] == 'h' || commandString[j] == 'H' ||
                    commandString[j] == 'v' || commandString[j] == 'V')
            {
                if ((j+1) == commandString.size())
                {
                    badPos = j+1;
                    return 1;
                }
                if(commandString[j+1] == '-')
                {
                
                    if((j+2) == commandString.size())
                    {
                       
                        badPos = j + 2;
                        return 1;
                    }
                    if(!isdigit(commandString[j+2]))
                    {
                        badPos = j;
                        return 1;
                    }
                    else if(!isdigit(commandString[j+3]))
                    {
                        j=j+2;
                        continue;
                    }
                    else
                        j = j+3;
                }
                
                else if(isdigit(commandString[j+1]))
                {
                    j = j + 1;
                    if(isdigit(commandString[j+1]))
                    {
                        j++;
                    continue;
                    }
                    
                    
                }
                else
                {
                    badPos = j+1;
                    return 1;
                }
                
            }
            
            else if(commandString[j] == 'f' || commandString[j] == 'b' || commandString[j] == 'F' || commandString[j] == 'B')
            {
                
                if ((j+1) == commandString.size())
                {
                    badPos = j+1;
                    return 1;
                }
                else
                {
                    j = j+1;
                }
                
               
            }
            
            else
            {
                badPos = j;
                return 1;
            }
            
        }
        else
        {
            badPos = j;
            return 1;
        }
        
    }
    cerr << "IT IS SYNTACTICALLY CORRECT" << endl;
    
//the loop that looks for logic/rightness of the commands
    for (int i = 0; i != commandString.size(); i++)
    {
        
        cerr << "YOU GOT TO THE IMPORTANT LOOP" << endl;
        differenceInR = loopingR - changingR;   //used to keep track of points, adds on difference to either r or c in loop
        differenceInC = loopingC - changingC;
        changingR = changingR + differenceInR;
        changingC = changingC + differenceInC;
 
        string dist;
        
            int dir;
           
            if(commandString[i] == 'c' || commandString[i] == 'C') //sets to * at (1,), used for plotting latter
            {
                
            
                distance = 0;
                changingR = 1;
                changingC = 1;
                changingChar = '*';
                loopingC = changingC + distance;
                loopingR = changingR + distance;
            }
            
            else if(commandString[i] == 'h' || commandString[i] == 'H' ||
                    commandString[i] == 'v' || commandString[i] == 'V')
            {
               
                if(!processHV(commandString, i, dir, distance, dist))
                {
                    badPos = i;
                    return 1;
                }
           
                
                
            }
            
            else if(commandString[i] == 'f' || commandString[i] == 'b' || commandString[i] == 'F' || commandString[i] == 'B')
            {
            
                
                if(i == 0)
                {
                    cerr << "---------------" << endl;
                    plotLine(1, 1, HORIZ, 0, '*', FG);
                }
                
                    distance = 0;
                
                    if (!processfb(commandString, i, changingfgbg, changingChar))
                    {
                        badPos = i;
                        return 1;
                    }
                    plotChar = changingChar;    //reflects the looping value that changes the reference
                    mode = changingfgbg;
                
            }
       
                
            else
            {
                badPos = i;
                return 1;
            }
            
            if(dir == HORIZ) //will add the distance to either R or C
            {
                loopingC = changingC + distance;
            }
            else if(dir == VERT)
            {
                loopingR = changingR + distance;
               
            }
        
            
            if(commandString[i] == 'c' || commandString[i] == 'C')
            {
                for(int e = 1; e <= 20; e++)           //loop clears entire grid without setting characters inside executeCommand
                {
                    plotLine(e, 1, HORIZ, 29, ' ', FG);
                }
                plotLine(1, 1, HORIZ, 0, '*', 1);
                
                plotChar = changingChar;
            }
            if(commandString[i-1] == 'f' || commandString[i-1] == 'b' || commandString[i-1] == 'F' || commandString[i-1] == 'B')
            {
                if(i == 0)
                {
                    cerr << "-------------------------------------" << endl;
                    plotLine(1, 1, HORIZ, 0, '*', FG);
                }
            }
            else
            {
                cerr << "IT GOT TO PLOTLINE" << endl;
                if(!plotLine(changingR, changingC, dir, distance, plotChar, mode)) //tests for out of grid
                {
                    
                        
                    if(distance > 0 && distance > 9) //10 and higher
                    {
                        
                        
                        if (dir == HORIZ)
                        {
                            if(changingC + distance > 30)
                            {
                                cerr << "IT GOT HERE" << endl;
                                badPos = i-2;
                                return 2;
                            }
                            
                        }
                        if (dir == VERT)
                        {
                            if(changingR + distance > 20)
                            {
                                badPos = i-2;
                                return 2;;
                                
                            }
                        }
                        
                        
                    }
                    else if (distance < 0 && distance < -9) //-10 and higher
                    {
                        
                        
                        
                        if (dir == HORIZ)
                        {
                            if (changingC + distance < 1) //watch for 0 case
                            {
                                badPos = i-3;
                                return 2;
                            }
                        }
                        if (dir == VERT)
                        {
                            if (changingR + distance < 1)
                            {
                                badPos = i-3;
                                return 2;
                            }
                        }
                        
                        
                    }
                    else if (distance > 0 && distance < 10) //9 and lower
                    {
                        
                        
                        if (dir == HORIZ)
                        {
                            if(changingC + distance > 30)
                            {
                                badPos = i-1;
                                return 2;
                            }
                        }
                        if (dir == VERT)
                        {
                            if (changingR + distance > 20)
                            {
                                badPos = i-1;
                                return 2;;
                            }
                        }
                        
                    }
                    else if (distance < 0 && distance > -10)//-9 and higher
                    {
                        
                        if(dir == HORIZ)
                        {
                            if(changingC + distance < 1)
                            {
                                badPos = i-2;
                                return 2;
                            }
                        }
                        if(dir == VERT)
                        {
                            if (changingR + distance < 1)
                            {
                                badPos = i-2;
                                return 2;
                            }
                        }
                        
                    }
                }
            }
        
        
    } //for-statement end
    
   
    
    return 0;
}

bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg)
{
    
    if(!isprint(plotChar))
        return false;
    
    if (r > 20 || c > 30)
        return false;
    
    else if (r < 1 || c < 1)
        return false;
    
    if(dir != HORIZ && dir != VERT)
        return false;
    if(fgbg != 0 && fgbg != 1)
        return false;
        
    
    setChar(r, c, getChar(r, c));
    
    
    if(distance > 0 && distance > 9) //10 and higher
    {
        
        
        if (dir == HORIZ)
        {
            if(c + distance > 30)
            {
                
                return false;
            }
            
        }
        if (dir == VERT)
        {
            if(r + distance > 20)
            {
                
                return false;
                
            }
        }
        
        
    }
    else if (distance < 0 && distance < -9) //-10 and higher
    {
 
        
        
        if (dir == HORIZ)
        {
            if (c + distance < 1)
            {
               
                return false;
            }
        }
        if (dir == VERT)
        {
            if (r + distance < 1)
            {
                
                return false;
            }
        }
        
        
    }
    else if (distance > 0 && distance < 10) //9 and lower
    {
        
        
        if (dir == HORIZ)
        {
            if(c + distance > 30)
            {
                
                return false;
            }
        }
        if (dir == VERT)
        {
            if (r + distance > 20)
            {
               
                return false;
            }
        }
        
    }
    else if (distance < 0 && distance > -10)//-9 and higher
    {
   
        if(dir == HORIZ)
        {
            if(c + distance < 1)
            {
                
                return false;
            }
        }
        if(dir == VERT)
        {
            if (r + distance < 1)
            {
                
                return false;
            }
        }
        
    }
    
    if (dir == HORIZ)
    {
        if (distance > 0)
        {
            plotHorizontalLine(r, c, distance, plotChar, fgbg);
            
        }
        
        else if (distance == 0)
        {
            plotHorizontalLine(r, c, 0, plotChar, fgbg);
        }
        
        else if (distance < 0)
            plotNegativeHoriz(r, c, distance, plotChar, fgbg);
    }
    else if (dir == VERT)
    {
        if (distance > 0)
        {
            plotVerticalLine(r, c, distance, plotChar, fgbg);
        }
        
        else if (distance == 0)
        {
            
            plotVerticalLine(r, c, 0, plotChar, fgbg);
        }
        else
        {
            
            plotNegativeVert(r, c, distance, plotChar, fgbg);
        }
    }
    

    else
        return false;
    
    
    cerr << "where is it at?" << endl;
    return true;
}


void plotHorizontalLine(int r, int& c, int distance, char ch, int fgbg)
{
    
    for (int i = c; i <= c + distance; i++)
    {
    
        if (fgbg == BG)
        {
            
            if (getChar(r,i) == ' ')
                setChar(r, i, ch);
                
        }
        else if (fgbg == FG)
            setChar(r, i, ch);
        else
            return;
        
    }
    
}

void plotVerticalLine(int& r, int c, int distance, char ch, int fgbg)
{

    for (int j = r; j <= r + distance; j++)
    {
        
        if (fgbg == BG)
        {
            
            if (getChar(j,c) == ' ')
                setChar(j, c, ch);
        }
        else if (fgbg == FG)
            setChar(j, c, ch);
        else
            return;
    }
}

void plotRectangle(int r, int c, int height, int width, char ch, int fgbg)
{
   
    plotHorizontalLine(r, c, width, ch, fgbg); //from the point
    

    plotVerticalLine(r, c, height, ch, fgbg); //from the point

    plotHorizontalLine(r + height - 1, c, width, ch, fgbg); //from lower left corner
    plotVerticalLine(r, c + width - 1, height, ch, fgbg);   //from upper right corner
    
    
}

void plotNegativeVert(int& r, int c, int distance, char ch, int fgbg) //created for negative direciton (vertical)
{
    
    for (int j = r; j >= r + distance; j--)
    {
        
        if (fgbg == BG)
        {
            
            if (getChar(j,c) == ' ')
                setChar(j, c, ch);
            
        }
        else if (fgbg == FG)
            setChar(j, c, ch);
        //otherwise return false?
        else
            return;

        
    }
}
    
    

void plotNegativeHoriz(int r, int& c, int distance, char ch, int fgbg) //created for negative direction (horizontal)
{
    for (int i = c; i >= c + distance; i--)
    {
        if (fgbg == BG)
        {
            
            if (getChar(r,i) == ' ')
                setChar(r, i, ch);
            
        }
        else if (fgbg == FG)
            setChar(r, i, ch);
        
        else
            return;
    }
    
}



bool processHV(string commandString, int& pos, int& dir, int& distance, string stringDist) //analyzes horizontal/vertical command
{

    //we know that this character is a letter
    if(commandString[pos] == 'h' || commandString[pos] == 'H')
        dir = HORIZ;
    
    else if(commandString[pos] == 'v' || commandString[pos] == 'V')
        dir = VERT;
    
   
    if(commandString[pos+1] == '-')             //determines whether it is a negative number
    {
        distance = -1;
        pos++;
        pos++;
    }
    
    else if(isdigit(commandString[pos+1]))
    {
        distance = 1;
        pos++;
    }
    else
    {
        
        return 1;
    }
    do
    {
        stringDist += commandString[pos];
        pos++;
        
    }while( stringDist.size() < 2 && pos != commandString.size() && isdigit(commandString[pos]));
    cerr << "Position is" << commandString[pos] << endl;
    cerr << "Your string is " << stringDist << endl;
    if (stringDist.size() == 2)
    {
      distance *=  ((10*(stringDist[0] - '0')) + (1*(stringDist[1]-'0')));      //multiplication -- makes value positive or negative
    }
    else if (stringDist.size() == 1)
        distance *= 1*(stringDist[0] - '0');
   
    pos--;
    


    return true;
}








bool processfb(string commandString, int& pos, int& fgbg, char& plotChar) //analyzes foreground/background
{
    
    if (commandString[pos] == 'f' || commandString[pos] == 'F')
    {
        fgbg = FG;
    }
    else
        fgbg = BG;

    
    pos++;
    
    plotChar = commandString[pos]; //sets character to character after F/B
    
    return true;
    
}


