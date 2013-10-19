#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;


const char helpStr[] = "Usage: \n" \
    "    taska11 infile [outfile] \n";

const int defaultVal = 1;


class TContext {

  public:
    TContext(int argc, const char* argv[]);
    ~TContext();

    istream* getIn();
    ostream* getOut();

  private:
    istream *in;
    ostream *out;

    void printHelp();
    void openInFile(const char* fileName);
    void openOutFile(const char* fileName);
};

istream* TContext::getIn(){

    return in;
}

ostream* TContext::getOut(){

    return out;
}

TContext::~TContext(){

    delete in;
    if (out != &cout)
        delete out;
}

TContext::TContext(int argc, const char* argv[]){

    if  (argc != 2 && argc != 3){
        printHelp();
        exit(0);
    }

    openInFile(argv[1]);
    if (argc >= 3)
        openOutFile(argv[2]);
    else
        out = &cout;
}

void TContext::printHelp(){
    cout << helpStr;
}

void TContext::openInFile(const char* fileName){

    ifstream *in = new ifstream(fileName);
    in->exceptions ( ifstream::failbit | ifstream::badbit );
    if (in->is_open()){
        this->in = in;
        return;
    }

    delete in;
    cout << "Can't open file: " << fileName << endl;
    exit(1);
}

void TContext::openOutFile(const char* fileName){

    ofstream *out = new ofstream(fileName);
    if (out->is_open()){
        this->out = out;
        return;
    }

    delete out;
    cout << "Can't open file: " << fileName << endl;
    exit(1);
}


int getNOD(int a, int b){
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}


class TFraction {

  public:
    TFraction();
    TFraction(int numerator, int denominator);

    int getNumerator() const;
    void setNumerator(int numerator);

    int getDenominator() const;
    void setDenominator(int denominator);

    int getIntPart() const;
    const TFraction getFractPart() const;

    const TFraction operator+(const TFraction& rv) const;
    const TFraction operator-(const TFraction& rv) const;
    const TFraction operator*(const TFraction& rv) const;
    const TFraction operator/(const TFraction& rv) const;

    bool operator>(const TFraction& rv) const;
    bool operator<(const TFraction& rv) const;
    bool operator==(const TFraction& rv) const;
    bool operator!=(const TFraction& rv) const;

    const TFraction simplify() const;

  private:
    int numerator;
    int denominator;

    int cmp(const TFraction& rv) const;
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

int TFraction::getIntPart() const{

    return numerator/denominator;
}

const TFraction TFraction::getFractPart() const{

    int intPart = getIntPart();
    return TFraction(numerator - denominator*intPart,
                     denominator);
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

    return TFraction(numerator*rv.numerator,
                     denominator*rv.denominator);
}

const TFraction TFraction::operator/(const TFraction& rv) const{

    return TFraction(numerator*rv.denominator,
                     denominator*rv.numerator);
}


int TFraction::cmp(const TFraction& rv) const{

    return numerator*rv.denominator - rv.numerator*denominator;
}

bool TFraction::operator>(const TFraction& rv) const{

    return cmp(rv) > 0;
}

bool TFraction::operator<(const TFraction& rv) const{

    return cmp(rv) < 0;
}

bool TFraction::operator==(const TFraction& rv) const{

    return cmp(rv) == 0;
}

bool TFraction::operator!=(const TFraction& rv) const{

    return cmp(rv) != 0;
}

const TFraction TFraction::simplify() const{

    int nod = getNOD(numerator, denominator);
    return TFraction(numerator/nod, denominator/nod);
}

ostream& operator<<( ostream& out, const TFraction& fraction){

    out << fraction.getNumerator() << "/" << fraction.getDenominator();
    return out;
}

istream& operator>>( istream& in, TFraction& fraction){

    int numerator, denominator;
    try{
        in >> numerator >> denominator;
    }
    catch(...){
        cout << "Incorrect input data" << endl;
        exit(1);
    }
    fraction.setNumerator(numerator);
    fraction.setDenominator(denominator);
    return in;
}

int main( int argc, const char* argv[] )
{
    TContext context(argc, argv);
    istream *in = context.getIn();
    ostream *out = context.getOut();

    TFraction a, b;
    *out << "a-b=" << a-b << endl;

    TFraction min, max, sum, current;

    *in >> current;
    min = current;
    max = current;
    sum = current;

    while(!in->eof()){
        *in >> current;
        sum = sum + current;
        if (current > max)
            max = current;
        if (current < min)
            min = current;
    }

    *out << "Min: " << min.simplify() << endl;
    *out << "Max: " << max.simplify() << endl;
    *out << "Sum: " << sum.getIntPart() << " " << sum.getFractPart().simplify() << endl;
}