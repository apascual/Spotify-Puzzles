//
//  main.cpp
//  Pruebas CPP
//
//  Created by Abel Pascual on 13/01/13.
//  Copyright (c) 2013 Abel Pascual. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <cstdlib>

using namespace std;

struct Item {
    double q_i;
    string name;
};


bool custom_comparer(Item const& lhs, Item const& rhs) {
    return lhs.q_i > rhs.q_i;
}

int main(int argc, const char * argv[])
{
    int total, selection;
    if(!(cin>>total>>selection))
        return 20;
    
    cin.clear();
    cin.ignore(10000, '\n');
    
    if(total>=1 && total<=50000 && selection>=1 && selection<=total)
    {
        vector<Item> list (total);
        
        
        for(int i=0;i<total;i++)
        {
            double f_i = 0;
            string auxName = "";
            if(!(cin>>f_i>>auxName))
                return 30;
            
            cin.clear();
            cin.ignore(10000, '\n');
            /*
             cin.ignore();
             string line = "";
             getline( cin, line);
             
             string::size_type loc = line.find( " ", 0);
             if( loc != string::npos ) {
             
             //cout<<line.substr(0,loc)<<endl;
             //cout<<line.substr(loc+1)<<endl;
             f_i = atol(line.substr(0,loc).c_str());
             auxName = line.substr(loc+1);
             }
             else{
             return 10;
             }
             */
            
            
            //   cout<<f_i<<endl;
            
            if(f_i<0 || f_i>pow(10,12))
                return 1;
            
            //cout<<auxName;
            
            if(auxName.length()<1)
                return 2;
            
            if(auxName.length()>30)
                return 4;
            
            for(int j=0;j<auxName.length();j++)
            {
                //48-57 97-122 95
                if(!((auxName[j]>=48 && auxName[j]<=57) ||
                     (auxName[j]>=97 && auxName[j]<=122) ||
                     auxName[j] == 95))
                {
                    return 3;
                }
            }
            
            list[i].q_i = f_i*(i+1);
            list[i].name = auxName;
        }
        
        stable_sort(list.begin(), list.end(), &custom_comparer);
        
        for(int i=0;i<selection;i++)
        {
            cout<<list[i].name<<endl;
        }
    }
    else{
        return -1;
    }
    return 0;
}

