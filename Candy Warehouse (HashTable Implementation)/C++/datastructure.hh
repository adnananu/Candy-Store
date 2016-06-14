
#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <iostream>
using std::string;

const std::string NOT_AVAILABLE = "Product not in warehouse.";
const std::string NOT_ENOUGH_CANDY = "Not enough candy available.";

class Datastructure {
public:

    Datastructure();

    ~Datastructure();

    //Generates Hash Value of given Key
    unsigned int GetHash(const std::string& str) const;

    //To resize the hashTable
    void ResizeHashTable();
    
    //function to set threshold
    void setThreshold(float threshold);
    
    // Adds candies to the datastructure (command "A")
    void add(const std::string& ID, const std::string& location,
            unsigned int amount, const std::string& name);

    // Removes candies from the datastructure (command "D")
    void substract(const std::string& ID, unsigned int amount);

    // Finds candy and prints its status (command "F")
    void find(const std::string& ID) const;

    // Returns how many different types of candy the datastructure contains (command "C")
    size_t count() const;

    // Empties the datastructure (command "E")
    void empty();

    
    Datastructure(const Datastructure&) = delete;
    Datastructure& operator=(const Datastructure&) = delete;

private:

    
    struct Tstruct {
        std::string pID;
        std::string pLocID;
        unsigned int pAmount;
        std::string pname;
        Tstruct *next;
        
        Tstruct(){};
        
        Tstruct(string _pID, string _pLocID, 
                unsigned int _pAmount, string _pname, Tstruct *_next){
        
            this->pID = _pID;
            this->pLocID = _pLocID;
            this->pAmount = _pAmount;
            this->pname = _pname;
            this->next = _next;
        }
        
    };
    const int DEFAULT_TABLE_SIZE  = 1000;
    Tstruct** hashtable;
    size_t sizeFinal;
    size_t countCandies;
    float Nthreshold;
    int NmaxSize;
};

#endif