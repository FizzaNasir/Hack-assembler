#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <bitset>
using namespace std;
string A_inst(string digit)
{
    int num;
    num = stoi(digit);
    string binary = std::bitset<16>(num).to_string(); //search the use of bitset library from google
    return binary;
}
string comp(string cmp)
{
    if (cmp == "0") { return "0101010"; }
    else if (cmp == "1") { return "0111111"; }
    else if (cmp == "-1") { return "0111010"; }
    else if (cmp == "D") { return "0001100"; }
    else if (cmp == "A") { return "0110000"; }
    else if (cmp == "!D") { return "0001101"; }
    else if (cmp == "!A") { return "0110001"; }
    else if (cmp == "-D") { return "0001111"; }
    else if (cmp == "-A") { return "0110011"; }
    else if (cmp == "D+1") { return"0011111"; }
    else if (cmp == "1+D") { return"0011111"; }
    else if (cmp == "A+1") { return "0110111"; }
    else if (cmp == "1+A") { return "0110111"; }
    else if (cmp == "D-1") { return"0001110"; }
    else if (cmp == "A-1") { return"0110010"; }
    else if (cmp == "D+A") { return"0000010"; }
    else if (cmp == "A+D") { return"0000010"; }
    else if (cmp == "D-A") { return"0010011"; }
    else if (cmp == "A-D") { return"0000111"; }
    else if (cmp == "D&A") { return"0000000"; }
    else if (cmp == "A&D") { return"0000000"; }
    else if (cmp == "D|A") { return"0010101"; }
    else if (cmp == "A|D") { return"0010101"; }


    //where a=1
    else if (cmp == "M") { return "1110000"; }
    else if (cmp == "!M") { return "1110001"; }
    else if (cmp == "-M") { return "1110011"; }
    else if (cmp == "M+1") { return"1110111"; }
    else if (cmp == "M-1") { return"1110010"; }
    else if (cmp == "M+A") { return"1000010"; }
    else if (cmp == "A+M") { return"1000010"; }
    else if (cmp == "D+M") { return"1000010"; }
    else if (cmp == "M+D") { return"1000010"; }
    else if (cmp == "D-M") { return"1010011"; }
    else if (cmp == "M-D") { return"1000111"; }
    else if (cmp == "D&M") { return"1000000"; }
    else if (cmp == "M&D") { return"1000000"; }
    else if (cmp == "D|M") { return"1010101"; }
    else if (cmp == "M|D") { return"1010101"; }

    else throw string("computation not found!");
}
string Jump(string jmp)
{
    if (jmp == "null") { return "000"; }
    else if (jmp == "JGT") { return "001"; }
    else if (jmp == "JEQ") { return "010"; }
    else if (jmp == "JGE") { return "011"; }
    else if (jmp == "JLT") { return "100"; }
    else if (jmp == "JNE") { return "101"; }
    else if (jmp == "JLE") { return "110"; }
    else if (jmp == "JMP") { return "111"; }
    else throw string("jump statement not found!");
}
string dest(string des)
{
    if (des == "null") { return "000"; }
    else if (des == "M") { return "001"; }
    else if (des == "D") { return "010"; }
    else if (des == "MD") { return "011"; }
    else if (des == "A") { return "100"; }
    else if (des == "AM") { return "101"; }
    else if (des == "AD") { return "110"; }
    else if (des == "AMD") { return "111"; }
    else throw string("destination not found!");
}
string combine(string dest, string comp, string jmp)
{
    string s;
    ostringstream oss;
    oss << endl << "111" << comp << dest << jmp << endl;
    s = oss.str();
    return s;
}
string Code_Translator(string str)
{
    int i = 0;
    string dst, cmp, jmp, Ainst;
    if (str.find('=') != string::npos)
    {
        while (str[i] != '=')
        {
            string s(1, str[i]);
            dst.append(s);
            i++;
        }
        string s(1, str[i += 1]);
        while (str[i] != '\0') {
            string s(1, str[i]);
            cmp.append(s);
            i++;
        }
        return combine(dest(dst), comp(cmp), Jump("null"));
    }

    else if (str.find('@') != string::npos)  //found this string find function in stackoverflow 
    {
        int j = 0;
        while (str[j] != '\0') {
            string s(1, str[j + 1]);
            Ainst.append(s);
            j++;
        }
        return A_inst(Ainst);
    }

    else if (str.find(';') != string::npos)
    {
        int k = 0;
        while (str[k] != ';')
        {
            string s(1, str[k]);
            cmp.append(s);
            k++;
        }
        string s(1, str[k += 1]);
        while (str[k] != '\0') {
            string s(1, str[k]);
            jmp.append(s);
            k++;
        }
        return combine(dest("null"), comp(cmp), Jump(jmp));
    }
}

int main()
{
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;
    ifstream in(filename);
    string result = in ? "Processing..\n" : "Failed to open file!\n";
    cout << result;
    fstream ifile("codefile.txt", ios::in | ios::out);
    string str, inst;
    in >> ws;                         //This line will remove whitespaces from 1st line if any
    while (getline(in, str, '\n')) {
                                     //removing all the blank lines, identations, whitespaces and storing text lines 
        in >> ws;
                                      //in a new file called codefile.txt
        ifile << str << endl;
    }
    ifile.close();
    ifile.open("codefile.txt");

    while (!ifile.eof())
    {
        getline(ifile, inst, '\n');
        cout<<Code_Translator(inst);
    }
}