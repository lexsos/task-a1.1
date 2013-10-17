#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

char helpStr[] = "Usage: \n" \
    "    taska11 infile [outfile] \n";

void printHelp(){
    cout << helpStr;
}

istream* openInFile(const char* fileName){

    ifstream *in = new ifstream(fileName);
    if (!in->is_open()){
        delete in;
        return NULL;
    }
    return in;
}

ostream* openOutFile(const char* fileName){

    ofstream *out = new ofstream(fileName);
    if (!out->is_open()){
        delete out;
        return NULL;
    }
    return out;
}

struct TContext {
    istream *in;
    ostream *out;
};

void prepareContext(TContext& context, int argc, const char* argv[]){
    context.out = &cout;
    if  (argc != 2 && argc != 3){
        printHelp();
        exit(0);
    }
    context.in = openInFile(argv[1]);
    if (!context.in){
        cout << "Can't open file: " << argv[1] << endl;
        exit(1);
    }
    if (argc >= 3)
        context.out = openOutFile(argv[2]);
    if (!context.out){
        cout << "Can't open file: " << argv[2] << endl;
        delete context.in;
        exit(1);
    }
}

void freeContext(TContext& context){
    delete context.in;
    if (context.out != &cout)
        delete context.out;
}

int main( int argc, const char* argv[] )
{
    TContext context;
    prepareContext(context, argc, argv);
    int i;
    *context.in >> i;
    *context.out << i;
    freeContext(context);
}