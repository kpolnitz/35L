//
//  main.cpp
//  CSWK3
//
//  Created by Kaela Polnitz on 4/16/17.
//  Copyright © 2017 Kaela Polnitz. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;


int main() {
    
    string name;
    int value;
    string category;
    double amount;
    
    const double FIRSTMIL_FEE =  0.013 * 1000;
    const double NEXT9MIL_FEE = 0.01 * 1000;
    const double OVER10MIL_FEE = 0.009 * 1000;
    const double SPECIAL_FEE = 0.002 * 1000; //if 'mutual fund' or 'royalty'
    
    cout << "Asset name: ";
    getline(cin, name);
   
 
    if (name == "") {
        cout << "---" << endl;
        cout << "You must enter an asset name." << endl;
        return 1;
    }
    
    cout << "Value (in thousands): ";
    cin >> value;
    
    cin.ignore(10000,'\n');
    
    if (value < 0) {
        cout << "---" << endl;
        cout << "The asset value must be nonnegative." << endl;
        return 1;
    }
    //a value of 0 would still be output, doesn't fit any of the criteria
    
    cout << "Category: ";
    getline(cin, category);
    
    if (category == "") {
        cout << "---" << endl;
        cout << "You must enter an asset category." << endl;
        return 1;
    }
    //return -1 used so that if it returns one of these strange cases it will not print the last cout
    //statement
    
    if (value <= 1000)
        amount = value * FIRSTMIL_FEE;
    
   
    else if (value <= 10000)
    {
        //firstmilfee/specialfee applied the first 1000, the rest has the next9milfee applied to it

        if (category == "mutual fund" || category == "royalty")
            amount = (1000 * FIRSTMIL_FEE) + ((value - 1000) * SPECIAL_FEE);
        
        else
        amount = (1000 * FIRSTMIL_FEE) + ((value - 1000) * NEXT9MIL_FEE);
    
    }
    
    else
    {
        //firstmilfee/specialfee applied to first 1 mil, next9milfee applied to next 9 mil
        //rest of value has over10milfee applied to it
        if (category == "mutual fund" || category == "royalty")
            amount = (1000 * FIRSTMIL_FEE) + (9000 * SPECIAL_FEE) + ((value - 10000) * OVER10MIL_FEE);

        else
            amount = (1000 * FIRSTMIL_FEE) + (9000 * NEXT9MIL_FEE) + ((value - 10000) * OVER10MIL_FEE);
    }
  
   
    cout << "---" << endl;
    cout << "The trustee fee for " << name <<  " is $" << amount << "." << endl;
    
}
