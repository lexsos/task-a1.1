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

const int defaultVal = 1;

class TFraction {

  public:
    TFraction();
    TFraction(int numerator, int denominator);

    int getNumerator() const;
    void setNumerator(int numerator);

    int getDenominator() const;
    void setDenominator(int denominator);

    const TFraction operator+(const TFraction& rv) const;
    const TFraction operator-(const TFraction& rv) const;
    const TFraction operator*(const TFraction& rv) const;
    const TFraction operator/(const TFraction& rv) const;

    const TFraction simplify() const;

  private:
    int numerator;
    int denominator;
};


TFraction::TFraction(){

    numerator = defaultVal;
    denominator = defaultVal;
}

TFraction::TFraction(int numerator, int denominator){

    this->numerator = numerator;
    this->denominator = denominator;
}


int TFraction::getNumerator() const{

    return numerator;
}

void TFraction::setNumerator(int numerator){

    this->numerator = numerator;
}

int TFraction::getDenominator() const{

    return denominator;
}

void TFraction::setDenominator(int denominator){

    this->denominator = denominator;
}

const TFraction TFraction::operator+(const TFraction& rv) const{

    int numerator, denominator;
    numerator = this->numerator*rv.denominator +
                this->denominator*rv.numerator;
    denominator = this->denominator*rv.denominator;
    return TFraction(numerator, denominator);
}

const TFraction TFraction::operator-(const TFraction& rv) const{
    int numerator, denominator;
    numerator = this->numerator*rv.denominator -
                this->denominator*rv.numerator;
    denominator = this->denominator*rv.denominator;
    return TFraction(numerator, denominator);
}

const TFraction TFraction::operator*(const TFraction& rv) const{

    return TFraction(this->numerator*rv.numerator,
                     this->denominator*rv.denominator);
}

const TFraction TFraction::operator/(const TFraction& rv) const{

    return TFraction(this->numerator*rv.denominator,
                     this->denominator*rv.numerator);
}

const TFraction TFraction::simplify() const{
    //TODO:
    return TFraction();
}

ostream& operator<<( ostream& out, const TFraction& fraction){

    out << fraction.getNumerator() << "/" << fraction.getDenominator();
    return out;
}


int main( int argc, const char* argv[] )
{
    TContext context;
    prepareContext(context, argc, argv);
    int i;
    *context.in >> i;
    *context.out << i << endl;

    TFraction a, b(1, 2);
    *context.out << a << endl;
    *context.out << b*b << endl;
    *context.out << b/b << endl;
    *context.out << b+b << endl;
    *context.out << b-b << endl;

    freeContext(context);
}