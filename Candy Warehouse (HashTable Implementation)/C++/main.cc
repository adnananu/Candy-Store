//
//  main.cpp
//  HW2_candy
//

#include "datastructure.hh"

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <string>
using std::string;
using std::getline;

#include <fstream>
using std::ifstream;

#include <sstream>
using std::istringstream;

#include <chrono>

#include <tuple>
using std::tuple;
using std::make_tuple;
using std::tie;
using std::get;

#include <vector>
using std::vector;

#include <cstdlib>
using std::rand;
using std::srand;


const string READ = "R";
const string ADD = "A";
const string REMOVE = "D";
const string FIND = "F";
const string EMPTY = "E";
const string COUNT = "C";
const string QUIT = "Q";
const string GEN = "G";
const string EFF = "P";

// const string PRINT = "P";
const string PROMPT = "> ";
const string DEFAULT_FILE = "varasto.txt";

void ReadFile( const string& file, Datastructure& DS );

tuple<unsigned long int,string> mempeak();

void generate(Datastructure &ds, unsigned int amount);

void efficiencyTest(Datastructure &ds, unsigned int amount, unsigned int cycles, unsigned long int startmem);


int main() {
    unsigned long int startmem = get<0>(mempeak());
    Datastructure DS;
    string command = " ";
    
    string name;
    string loc;
    string ID;
    string file;
    char nextchar;
    unsigned int amnt = 0;

    do{
        cout << PROMPT;
        cin >> command;
        if (cin.eof())
        {
            //cerr << "eof" << endl;
            command = QUIT;
        }
        
        if( command == READ )
        {
            nextchar = cin.peek();
            if(nextchar == '\n' || nextchar == '\r')
            {
                file = DEFAULT_FILE;
            }
            else
            {
                cin >> file;
            }
            //DS.empty();
            cout << READ << " " << file << endl;
            ReadFile( file, DS );
        }
        else if (command == GEN)
        {

            unsigned int amount = 0;
            cin >> amount;
            cout << GEN << " " << amount << endl;
            generate(DS, amount);
        }
        else if (command == EFF)
        {
            unsigned int amount, cycles = 0;
            cin >> amount >> cycles;
            cout << EFF << " " << amount << " " << cycles << endl;
            efficiencyTest(DS, amount, cycles, startmem);
        }
        else if( command == ADD )
        {
            cin >> ID >> loc >> amnt;
            cin.get();
            getline(cin, name);
            cout << ADD << " " << ID << " " << loc << " " << amnt << " "
                      << name << endl;
            DS.add(ID, loc, amnt, name);
        }
        else if( command == REMOVE )
        {
            cin >> ID >> amnt;
            cout << REMOVE << " " << ID << " " << amnt << endl;
            DS.substract( ID, amnt );
        }
        else if( command == FIND )
        {
            cin >> ID;
            cout << FIND << " " << ID << endl;
            DS.find( ID );
        }
        else if( command == EMPTY )
        {
            cout << EMPTY << endl;
            DS.empty();
        }
        else if( command == COUNT )
        {
            cout << COUNT << endl;
            cout << DS.count() << " different kinds of candy." << endl;
        }
//        else if( command == PRINT )
//        {
//            nextchar = cin.peek();
//            if(nextchar == '\n' || nextchar == '\r')
//            {
//                file = DEFAULT_FILE;
//            }
//            else
//            {
//                cin >> file;
//            }
//            DS.save_to_file( file );
//        }
        else
        {
            continue;
        }
    }while( command != QUIT && !cin.eof());
    cout << QUIT << endl;
    
    return EXIT_SUCCESS;
}


void generate(Datastructure &ds, unsigned int amount)
{
    srand(amount);
    vector<string> candy_types{"LKS", "GUM", "SMK", "MIX", "SUK", "TIK", "VHT", "WIN"};
    static const char alphas[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    static const char ints[] = "123456789";

    for ( unsigned int k = 0; k < amount; k++)
    {
        string id("");
        id += candy_types.at((unsigned int)rand() % (candy_types.size() - 1));
        id += ":098765retfg:1212:965";
        unsigned short i = rand() % 19 + 4;
        while (id[i] == ':'){
            i = rand() % 19 + 4;
        }
        unsigned short j = rand() % 19 + 4;
        while (id[j] == ':' or i == j){
            j = rand() % 19 + 4;
        }
        if (i >= 16){
            unsigned int a = ints[(unsigned int)rand() % 9];
            id[i] = a;
        }
        else id[i] = alphas[(unsigned int)rand() % (sizeof(alphas) - 1)];

        if (j >= 16){
            unsigned int a = ints[(unsigned int)rand() % 9];
            id[j] = a;
        }
        else id[j] = alphas[(unsigned int)rand() % (sizeof(alphas) - 1)];

        ds.add(id, "8.97", 1000, "Ali Shah");
    }

}

void efficiencyTest(Datastructure &ds, unsigned int amount, unsigned int cycles, unsigned long int startmem){


    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::system_clock::now();

    for(unsigned k = 0; k < cycles; ++k){
        ds.empty();
        ds.add("GUM:31415926:1007:961", "3.25", 1000, "Sami Pakor");
        ds.add("SUK:10thTardis:1028:144", "1.56", 1000, "Fazin Sahir");
        generate(ds, amount);
        for (unsigned j = 0; j < amount/3; ++j){
            ds.add("MIX:GLaDOS:2148:615", "2.22", 1000, "Nasira");
            ds.add("WIN:DeepThought:4242:424", "4.20", 1000, "Haris");
            ds.add("VHT:StarGateSG1:1021:824", "7.00", 1000, "Omar");
            ds.find("GUM:31415926:1007:961");
            ds.find("SUK:10thTardis:1028:144");
            ds.find("MIX:GLaDOS:2148:615");
            ds.find("WIN:DeepThought:4242:424");
            ds.find("VHT:StarGateSG1:1021:824");
            ds.substract("MIX:GLaDOS:2148:615", 1000);
            ds.substract("WIN:DeepThought:4242:424", 1000);
            ds.substract("VHT:StarGateSG1:1021:824", 1000);
        }
        ds.substract("GUM:31415926:1007:961", 1000);
        ds.substract("SUK:10thTardis:1028:144", 1000);
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end-start;
    unsigned long int maxmem;
    string unit;
    tie(maxmem, unit) = mempeak();
    maxmem -=  startmem;
    cerr << elapsed.count() << " sec, " << maxmem << " " << unit << endl;


}

void ReadFile( const string& file, Datastructure& DS )
{
    ifstream file_stream( file );
    if( !file_stream )
    {
        file_stream.close();
        cout << "File not found." << endl;
        return;
    }

//     DS.empty();

    string line;
    string ID;
    string loc;
    unsigned int amnt;
    string name;
    while( getline( file_stream, line ))
    {
        istringstream line_stream( line );
        getline(line_stream, ID, ';');
        line_stream >> amnt;
        line_stream.get();
        getline(line_stream, loc, ';');
        getline(line_stream, name);
        DS.add( ID, loc, amnt, name );
    }
    file_stream.close();
}

tuple<unsigned long int,string> mempeak(){
    ifstream file_stream("/proc/self/status");
    if( file_stream ){    
        string line;
        string ID;
        unsigned long int amnt;
        string unit;
        while( getline( file_stream, line ))
        {
            istringstream line_stream( line );
            getline(line_stream, ID, ':');
            if (ID == "VmPeak"){
                line_stream >> amnt;
                line_stream >> unit;
                return make_tuple(amnt, unit);
            }
        }
    }
    file_stream.close();
    return make_tuple(0, "?");
}
