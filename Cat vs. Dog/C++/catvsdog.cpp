//
//  catvsdog.cpp
//
//  Created by Abel Pascual on 23/01/13.
//  Copyright (c) 2013 Abel Pascual. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Class that handles the votes of the users and have some attributes
 * used in the resolution process
 */
class Vote
{
private:
    // Animal that is wanted to be kept
    string toKeep;
    // Animal that is wanted to be thrown
    string toThrow;
    
    // List of incompatible votes
    vector<Vote*> notCompatible;
    // Boolean indicating if this vote has been explored
    bool alreadyExplored;
    // Vote linked
    Vote *link;
    
public:
    // Typical set of methods to access to the attibutes
    Vote(string tk, string tt);
    string getToKeep();
    string getToThrow();
    vector<Vote*> getNotCompatible();
    void addNotCompatibleRule(Vote *vote);
    bool isAlreadyExplored();
    void setAlreadyExplored(bool e);
    Vote* getLink();
    void setLink(Vote *v);
};

/** Class Vote functions implementation **/

// Constructor
Vote::Vote(string tk, string tt)
{
    toKeep = tk;
    toThrow = tt;
    alreadyExplored = false;
    link = NULL;
}

string Vote::getToKeep()
{
    return toKeep;
}

string Vote::getToThrow()
{
    return toThrow;
}

vector<Vote*> Vote::getNotCompatible()
{
    return notCompatible;
}

void Vote::addNotCompatibleRule(Vote *vote)
{
    notCompatible.insert(notCompatible.end(), vote);
}

bool Vote::isAlreadyExplored()
{
    return alreadyExplored;
}

void Vote::setAlreadyExplored(bool e)
{
    alreadyExplored = e;
}

Vote* Vote::getLink()
{
    return link;
}

void Vote::setLink(Vote *v)
{
    link = v;
}

/** End of class Vote functions implementation **/


int solve(vector<Vote*> catLovers, vector<Vote*> dogLovers);
bool assign(Vote *catNode);

int aaa= 0;

// Function that controls the running and solves the problem
int main(int argc, const char * argv[])
{
    // Reading the number of scenarios
    int total;
    cin>>total;
    
    //int answers[total];
    
    if(total>0 && total <=100)
    {
        for(int i=0;i<total;i++)
        {
            // Reading number of cats, dogs and voters
            int c, d, v;
            cin>>c>>d>>v;
            aaa=v;
            if(c>=1 && c<=100 && d>=1 && d<=100 && v>=0 && v<=500)
            {
                // Vectors to store the votes depending on the preference
                vector<Vote*> catsLovers;
                vector<Vote*> dogsLovers;
                
                // Read and store the votes
                for(int j=0;j<v;j++)
                {
                    string toKeep, toThrow;
                    cin>>toKeep>>toThrow;
                    
                    if(toKeep[0]=='C')
                    {
                        catsLovers.insert(catsLovers.end(), new Vote(toKeep, toThrow));
                    }
                    else if(toKeep[0]=='D')
                    {
                        dogsLovers.insert(dogsLovers.end(), new Vote(toKeep, toThrow));
                    }
                }
                
                // Storing for every Vote other incompatible Votes
                for(Vote *cat : catsLovers)
                {
                    for(Vote *dog : dogsLovers)
                    {
                        // Store the incompatibilities only in the cats lover votes
                        if(cat->getToKeep()==dog->getToThrow() || dog->getToKeep()== cat->getToThrow())
                            cat->addNotCompatibleRule(dog);
                    }
                }
                
                // Retrieve maximum number of incompatibilities
                int incompatibilities = solve(catsLovers, dogsLovers);
                
                // Maximum number of voters satisfied would be total_number_voters - max_incompatibilities
                //answers[i] = (v-incompatibilities);
                cout<<(v-incompatibilities)<<endl;
            }
        }
    }
    
    //for(int i=0;i<total;i++)
    //    cout<<answers[i]<<endl;
    
    return 0;
}

/**
 * Function that receives two sets of votes and calculates the maximum number
 * of incompatibilities.
 */
int solve(vector<Vote*> catLovers, vector<Vote*> dogLovers)
{
    int sum = 0;
    // Iterate through the cat votes
    for(int i=0;i<catLovers.size();i++)
    {
        Vote *catNode = catLovers[i];
        
        // Set all the alreadyExplored variables to false
        for(int j=0;j<dogLovers.size();j++)
            dogLovers[j]->setAlreadyExplored(false);
        
        // If this vote can be assigned to another incompatible vote, increment sum
        if(assign(catNode)) sum++;
    }
    return sum;
}

/**
 * Function that checks if a vote can be assined to other incompatible vote.
 */
bool assign(Vote *catNode) {
    vector<Vote*> notComp = catNode->getNotCompatible();
    
    // Iterate through the incompatible votes of catNode
    for(int j=0;j<notComp.size();j++)
    {
        Vote *dogNode = catNode->getNotCompatible()[j];
        
        // If the catNode and dogNode are incompatible and dogNode has not been explored yet...
        if(!dogNode->isAlreadyExplored())
        {
            // First mark as explored dogNode
            dogNode->setAlreadyExplored(true);
            
            // If dogNode has no vote assigned yet or if it was assigned but can be changed
            if (dogNode->getLink()==NULL || assign(dogNode->getLink())){
                catNode->setLink(dogNode);
                dogNode->setLink(catNode);
                return true;
            }
        }
    }
    return false;
}


