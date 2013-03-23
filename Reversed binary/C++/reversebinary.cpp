//
//  main.cpp
//  Pruebas CPP
//
//  Created by Abel Pascual on 13/01/13.
//  Copyright (c) 2013 Abel Pascual. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, const char * argv[])
{

    int val = 1;
    
    do{
        cin>>val;
    }
    while(val<1 || val>1000000000);
    
    
    int i = 31;
    int u = 0;
    int newVal = 0;
    bool active = false;
    while(val>0)
    {
        if((val - pow(2,i))>=0)
        {
            val = val - pow(2,i);
            newVal = newVal + pow(2,u);
            active = true;
        }
        
        if(active)
            u++;
        i--;
    }
    
    cout<<newVal;
    
    return 0;
}

