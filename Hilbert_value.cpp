#include <iostream>
#include <math.h> 
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

#define ORDER 1024

//int interleaveBits (int odd, int even);
void rot(int n, int &x, int &y, int rx, int ry);

/*int xy2d(int r, int x, int y) {

    int mask = (1 << r) - 1;
    int hodd = 0;
    int heven = x ^ y;
    int notx = ~x & mask;
    int noty = ~y & mask;
    int temp = notx ^ y;

    int v0 = 0, v1 = 0;
    for (int k = 1; k < r; k++) {
        v1 = ((v1 & heven) | ((v0 ^ noty) & temp)) >> 1;
        v0 = ((v0 & (v1 ^ notx)) | (~v0 & (v1 ^ noty))) >> 1;
    }
    hodd = (~v0 & (v1 ^ x)) | (v0 & (v1 ^ noty));

    return interleaveBits(hodd, heven);
}

*
 * Interleave the bits from two input integer values
 * @param odd integer holding bit values for odd bit positions
 * @param even integer holding bit values for even bit positions
 * @return the integer that results from interleaving the input bits
 *
 * @todo: I'm sure there's a more elegant way of doing this !
 
int interleaveBits(int odd, int even) {
    int val = 0;
    int max = fmax(odd, even);
    int n = 0;
    while (max > 0) {
        n++;
        max >>= 1;
    }

    for (int i = 0; i < n; i++) {
        int bitMask = 1 << i;
        int a = (even & bitMask) > 0 ? (1 << (2*i)) : 0;
        int b = (odd & bitMask) > 0 ? (1 << (2*i+1)) : 0;
        val += a + b;
    }

    return val;
}*/

int xy2d (int n, int x, int y) {
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        rot(s, x, y, rx, ry);
    }
    return d;
}

void d2xy(int n, int d, int x, int y) {
    int rx, ry, s, t=d;
    x = y = 0;
    for (s=1; s<n; s*=2) {
        rx = 1 & (t/2);
        ry = 1 & (t ^ rx);
        rot(s, x, y, rx, ry);
        x += s * rx;
        y += s * ry;
        t /= 4;
    }
    cout << x << " " << y << "\n"; 
}

void rot(int n, int &x, int &y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            x = n-1 - x;
            y = n-1 - y;
        }
 
        int t  = x;
        x = y;
        y = t;
    }
}

string* extractIndexString(string s) {
    string* container = new string[4];
    string temp = "";
    int space = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            container[space++] = temp;
            temp = "";
        }
        else
            temp += s[i];
    }
    container[space] = temp;    
    return container;
}

void printHIndex() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndexO/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        int index = xy2d(ORDER, x, y);
        ostringstream ss;
        ss << index;
        temp += ss.str();
        outfile << temp << endl;
    }
    infile.close();
    outfile.close();
}

void printHIndexN90() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndexN90/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        int x1 = ORDER - 1 - y;
        int y1 = x;
        int index = xy2d(ORDER, x1, y1);
        ostringstream ss;
        ss << index;
        temp += ss.str();
        outfile << temp << endl;
    }
    infile.close();
    outfile.close();
}

void printHIndexP90() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndexP90/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        int x1 = y;
        int y1 = ORDER - 1 - x;
        int index = xy2d(ORDER, x1, y1);
        ostringstream ss;
        ss << index;
        temp += ss.str();
        outfile << temp << endl;
    }
    infile.close();
    outfile.close();
}

void printHIndex180() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndex180/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        int x1 = ORDER - 1 - x;
        int y1 = ORDER - 1 - y;
        int index = xy2d(ORDER, x1, y1);
        ostringstream ss;
        ss << index;
        temp += ss.str();
        outfile << temp << endl;
    }
    infile.close();
    outfile.close();
}

void printHIndexTR() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndexTR/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        if (x > 0 && y > 0) {
            int x1 = x - 1;
            int y1 = y - 1;
            int index = xy2d(ORDER, x1, y1);
            ostringstream ss;
            ss << index;
            temp += ss.str();
            outfile << temp << endl;
        }
    }
    infile.close();
    outfile.close();
}

void printHIndexTL() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndexTL/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        if (x < ORDER - 1 && y > 0) {
            int x1 = x + 1;
            int y1 = y - 1;
            int index = xy2d(ORDER, x1, y1);
            ostringstream ss;
            ss << index;
            temp += ss.str();
            outfile << temp << endl;
        }
    }
    infile.close();
    outfile.close();
}

void printHIndexBR() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndexBR/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        if (x > 0 && y < ORDER - 1) {
            int x1 = x - 1;
            int y1 = y + 1;
            int index = xy2d(ORDER, x1, y1);
            ostringstream ss;
            ss << index;
            temp += ss.str();
            outfile << temp << endl;
        }
    }
    infile.close();
    outfile.close();
}

void printHIndexBL() {
    string sLine = "";
    ifstream infile;
    ofstream outfile;

    infile.open("cali-index.txt");
    outfile.open("HIndexBL/cali-HilbertIndex.txt");

    while (!infile.eof()) {
        string temp = "";
        getline(infile, sLine);
        string *lineIndex;
        lineIndex = extractIndexString(sLine);
        temp += (sLine + " ");
        int x = (int)atof(lineIndex[2].c_str());
        int y = (int)atof(lineIndex[3].c_str());
        if (x < ORDER - 1 && y < ORDER - 1) {
            int x1 = x + 1;
            int y1 = y + 1;
            int index = xy2d(ORDER, x1, y1);
            ostringstream ss;
            ss << index;
            temp += ss.str();
            outfile << temp << endl;
        }
    }
    infile.close();
    outfile.close();
}

int main() {
    printHIndex();
    printHIndexN90();      
    printHIndexP90();
    printHIndex180();
    printHIndexTR();
    printHIndexTL();
    printHIndexBR();
    printHIndexBL();
}