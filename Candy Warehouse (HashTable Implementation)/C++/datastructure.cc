#include "datastructure.hh"

using namespace std;

/*Generate hashValue*/
unsigned int Datastructure::GetHash(const std::string& str) const {
    unsigned int hash = 131;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash ^= ((hash << 5) + str[i] + (hash >> 2));
    }
    return hash % sizeFinal;
}

Datastructure::Datastructure() {

    sizeFinal = DEFAULT_TABLE_SIZE;
    countCandies = 0;
    Nthreshold = 0.75f;
    NmaxSize = 0;
    hashtable = new Tstruct*[sizeFinal];
    for (int i = 0; i < sizeFinal; i++) {
        hashtable[i] = NULL;
    }
    setThreshold(Nthreshold);
}

Datastructure::~Datastructure() {

}

void Datastructure::add(const string &ID, const string &location,
        unsigned int amount, const string &name) {

    int hashIndex = GetHash(ID);
    Tstruct* newNode = NULL;
    if (hashtable[hashIndex] == NULL) {
        newNode = new Tstruct(ID, location, amount, name, NULL);
        hashtable[hashIndex] = newNode;
        countCandies += 1;
    } else {
        newNode = hashtable[hashIndex];
       while (newNode != NULL) {
            if (newNode->pID == ID) {
                newNode->pAmount = newNode->pAmount + amount;
                break;
            } else if (newNode->next == NULL) {
                newNode = new Tstruct(ID, location, amount, name, hashtable[hashIndex]);
                hashtable[hashIndex] = newNode;
                countCandies += 1;
                break;
            }
            newNode = newNode->next;
        }
    }
    newNode = NULL;
    if (countCandies >= NmaxSize)
             ResizeHashTable();
}

void Datastructure::substract(const string &ID, unsigned int amount) {
    int hashIndex = GetHash(ID);
    Tstruct* temp;
    bool found = false;
    if (hashtable[hashIndex] != NULL) {
        // checking the head node
        if (hashtable[hashIndex]->pID == ID) {
            found = true;
            if (amount > hashtable[hashIndex]->pAmount) {
                cout << NOT_ENOUGH_CANDY << endl;
                cout << "Amount: " << hashtable[hashIndex]->pAmount
                        << " Shelf: " << hashtable[hashIndex]->pLocID << endl;
            } else {
                hashtable[hashIndex]->pAmount = hashtable[hashIndex]->pAmount - amount;
                cout << "Amount: " << hashtable[hashIndex]->pAmount
                        << " Shelf: " << hashtable[hashIndex]->pLocID << endl;
                if (hashtable[hashIndex]->pAmount == 0) {
                    temp = hashtable[hashIndex];
                    hashtable[hashIndex] = hashtable[hashIndex]->next;
                    delete temp; //deleting head node placed in start
                    countCandies -= 1; //decreasing number of candies
                }
            }
        }//end else if
        else { //check inside linklist because value not found in head node
            Tstruct* nodeBefore;
            temp = hashtable[hashIndex]->next;
            nodeBefore = hashtable[hashIndex];
            while (temp != NULL) {
              if (temp->pID == ID)// if the values match,
                {
                    found = true;
                    //if specific candy found but given amount is greater
                    if (/*found &&*/ amount > temp->pAmount) {
                        cout << NOT_ENOUGH_CANDY << endl;
                        cout << "Amount: " << temp->pAmount << " Shelf: "
                                << temp->pLocID << endl;
                    } else /*if (found)*/ {
                        temp->pAmount = temp->pAmount - amount;
                        cout << "Amount: " << temp->pAmount << " Shelf: "
                                << temp->pLocID << endl;
                        //deleting the node if amount ia zero
                        if (temp->pAmount == 0) {
                            nodeBefore->next = temp->next;
                            delete temp; // deleting node to be deleated
                            countCandies -= 1; //decreasing number of candies
                        }
                    }
                    break;
                }
                nodeBefore = temp;
                temp = temp->next; // otherwise, move on
            }
            nodeBefore = NULL;

        }//end else only
    }
    if (!found) //if not found
        cout << NOT_AVAILABLE << endl;
}

void Datastructure::find(const string &ID) const {
    //getting the hash value of ID
    int hashIndex = GetHash(ID);
    Tstruct* head;
    head = hashtable[hashIndex];
    bool found = false;
    while (head != NULL) {
        if (head->pID == ID) { // if the value matches, then
            cout << head->pname << " " << head->pAmount << " "
                    << head->pLocID << endl;
            found = true;
            break;
        }
        head = head->next; //otherwise, move on
    }
    if (!found) //if not found.
        cout << NOT_AVAILABLE << endl;
    head = NULL;
}

size_t Datastructure::count() const {
    //number of different candies in total!!
    return countCandies;
}

void Datastructure::empty() {

    Tstruct *tempHead;
    for (int i = 0; i < sizeFinal; i++) {
        if (hashtable[i] != NULL) {
            //if its not NULL assigning to temporary pointer
            tempHead = hashtable[i];
            while (tempHead != NULL) {
                //getting reference of next node
                hashtable[i] = hashtable[i]->next;
                delete tempHead; //deleting the previous
                tempHead = hashtable[i];
            }
        }
    }
    tempHead = NULL; //dangling pointer
    countCandies = 0;
}

void Datastructure::ResizeHashTable() {
    size_t oldTableSize = sizeFinal;
    //making the size double
    sizeFinal *= 2;
    //setting threshold for new table
    setThreshold(Nthreshold);
    //NmaxSize = (int) (sizeFinal * Nthreshold);
    Tstruct **oldTable = hashtable;
    hashtable = new Tstruct*[sizeFinal];
    //assigning null to all new objects
    for (int i = 0; i < sizeFinal; i++) {
        hashtable[i] = NULL;
    }
    countCandies = 0;
    //transfering data from old to new table
    for (int hash = 0; hash < oldTableSize; hash++) {
        if (oldTable[hash] != NULL) {
            Tstruct *oldEntry;
            Tstruct *entry = oldTable[hash];
            while (entry != NULL) {
                add(entry->pID, entry->pLocID, entry->pAmount, entry->pname);
                oldEntry = entry;
                entry = entry->next;
                delete oldEntry;
            }
        }
    }
    delete[] oldTable;
}

void Datastructure::setThreshold(float threshold) {
    this->Nthreshold = threshold;
    NmaxSize = (int) (sizeFinal * threshold);
}