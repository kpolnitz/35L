#!/usr/bin/python

#We are starting work from the randline.py file
"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

#our input format is going to be like:  comm  -12 file1 file2


#readlines() - reads an entire line from a file
#open() - allows us to read/use stuff from a file
#'r' - in read mode only
#we will think of the entry as 'comm -## [file] [file]'
#if a dash is found, take stdinput
#if not, look at the file passed.


#Piazza - uses tabs -- DO NOT USE TABS! Does not work in Python3
#1 tab prints as 8 spaces
          
import random, string, sys, locale
from optparse import OptionParser

locale.setlocale(locale.LC_ALL, 'C')

class comm: 
    def __init__(self, file1comp, file2comp):
        self.col1 = []
        self.col2 = []
        self.col3 = []
        #used for creating lists later 
        if (file1comp == '-' and file2comp == '-'):
            print("This command is undefined. Two requests for stdin")
            exit()
        if (file1comp == '-'): 
            file1 = sys.stdin.readlines()
        else:
            file1 = open(file1comp, 'r')
            self.lines1 = file1.readlines()
            file1.close()
        if (file2comp == '-'):
            file2 = sys.stdin.readlines()
        else:
            file2 = open(file2comp, 'r')
            self.lines2 = file2.readlines()
            file2.close()

    def sort(self):
        #in this function, we compare to get our third column
        #append() - add new entry to list
        #only continue if sorted
        #print ("You got to sorting")
        compare1 = 0
        compare2 = 0
        if self.isItSorted(self.lines1):
            if self.isItSorted(self.lines2):
                #print("Think it's sorted!")
                while compare1 < len(self.lines1) and compare2 < len(self.lines2):
                    #print("We got into a loop!")
                    #print("comparing\n" + self.lines1[compare1] + "and")
                    #print(" " + self.lines2[compare2])
                    #tab between columns
                    if self.lines1[compare1] == self.lines2[compare2]:
                        self.col1.append("\t")
                        self.col2.append("\t")
                        self.col3.append(self.lines2[compare2])
                        #gives us column set up
                        compare1 += 1
                        compare2 += 1

                    elif self.lines1[compare1] > self.lines2[compare2]:
                        self.col3.append("")
                        self.col2.append(self.lines2[compare2])
                        self.col1.append("\t")
                        compare2 += 1
                    elif self.lines1[compare1] <  self.lines2[compare2]:
                        self.col3.append("")
                        self.col2.append("")
                        self.col1.append(self.lines1[compare1])
                        #self.lines1[compare1] = ''
                        compare1 += 1

                while compare1 < len(self.lines1) or compare2 < len(self.lines2):
                    if compare1 < len(self.lines1):
                        self.col1.append(self.lines1[compare1])
                        self.col3.append("")
                        self.col2.append("")
                        compare1 += 1
                    if compare2 < len(self.lines2):
                        self.col1.append("\t")
                        self.col3.append("")
                        self.col2.append(self.lines2[compare2])
                        compare2 += 1
        #print("You are done sorting!")

    def unsort(self):
        #print("You are in unsorted")
        ucompare1 = 0
        ucompare2 = 0
        newIterator = 0
        while ucompare1 < len(self.lines1) and ucompare2 < len(self.lines2):
            if self.lines1[ucompare1] == self.lines2[ucompare2]:
                self.col1.append("\t")
                self.col2.append("\t")
                self.col3.append(self.lines1[ucompare1])
                ucompare1 += 1
                ucompare2 += 1
                newIterator = ucompare2
                #gives us column set up

            elif ucompare2 == len(self.lines2) - 1 and ucompare1 <= len(self.lines1) - 1:
                self.col3.append("")
                self.col1.append(self.lines1[ucompare1])
                self.col2.append("")
                ucompare1 += 1
                ucompare2 = newIterator
            else:
                ucompare2 += 1


        for  ucompare2 in range(len(self.lines2)):
            for ucompare1 in range( len(self.lines1)):
                if self.lines1[ucompare1] == self.lines2[ucompare2]:
                    break
                if ucompare1 == len(self.lines2) - 1:
                    self.col3.append("")
                    self.col2.append(self.lines2[ucompare2])
                    self.col1.append("\t")

    def isItSorted(self, fileToCheck):
        counter = 0
        while counter < len(fileToCheck) - 1:
            if (fileToCheck[counter] > fileToCheck[counter+1]):
                return False
            else:
                counter += 1
        return True


    def result(self, option1, option2, option3):

        printer = []
        other = []
        #we are going to have an array of arrays be our output
        #sys.stdout.write("We got to the loops")
        #print("You are before the loop!")
        a = 0
        i = 0
        j = 0
        k = 0
        while a < len(self.col1):
            #sys.stdout.write("Ok how many times?\n")
            printer.append(self.col1[a] + self.col2[a] + self.col3[a])
            a += 1
            #remove = printer[a].replace('\n','')  
        #delete = printer.replace("\n", "")   
        while i < len(printer):
            #we will go by line by line and print it
            #while k  < len(lineToPrint):
                    # sys.stdout.write(lineToPrint[k])
                    # k += 1

           remove = printer[i].replace("\n","")


           if printer[i] != "":
               sys.stdout.write(remove+'\n')


           i += 1
            #print("The number is: ")
            #print(i)

def main():
    version_msg="%prog 2.0"
    usage_msg= """%prog [OPTION]... FILE1 FILE2

    Output content into three columns:
    1. Just file1 content
    2. Just file2 content
    3. Content found in both.  """

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="col1", default=0,
                      help="output column1 lines")
    parser.add_option("-2",
                      action="store_true", dest="col2", default=0,
                      help="output column2 lines")
    parser.add_option("-3",
                      action="store_true", dest="col3", default=0,
                      help="output column3 lines")
    parser.add_option("-u",
                      action="store_true", dest="unsorted", default=0,
                      help="output even if unsorted")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        col1 = options.col1
        col2 = options.col2
        col3 = options.col3
        unsorted = options.unsorted
    except:
        parser.error("Not a column/unsorted: {0}".
                     format(options.col1))

    if len(args) != 2:
        parser.error("Error: wrong number of files.")
    input_file1 = args[0]
    input_file2 = args[1]
    try:
        comparison = comm(input_file1, input_file2)
        if unsorted:
            comparison.unsort()
        else:
            #print("You are in the correct place!")
            comparison.sort()
        comparison.result(col1, col2, col3)

    except IOError as er:
        errno = er.errno
        strerror = er.strerror
        parser.error("I/O error({0}): {1}".
                                  format(errno, strerror))

#how we deal with exceptions with python2
if __name__ == "__main__":
    main()

                                                                          
