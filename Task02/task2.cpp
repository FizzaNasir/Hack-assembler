#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <bitset>
int x = 16;
int count_lines=0;
using namespace std;

    bool is_digit(string str)   //to check if string is only numbers or not
    {
        for (int i = 0; i < str.length(); i++) {
            if (str.at(i) >= '0' && str.at(i) <= '9') { return true; }
            else { return false; }
        }
        return false;
    }
    string removeSpaces(string str)
    {
        string strng = "";
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] != ' ')
            {
                string s(1, str[i]);
                strng.append(s);
            }
        }
        return strng;
    }
    string removeBrackets(string str)
    {
        string s;
        for (int i = 0; i < str.size(); ++i) {
            if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
                s = s + str[i];
            }
        }
        str = s;
        return str;
    }

    class Symbol_Table
    {
    private:
        class ListNode
        {
        public:
            string sym;
            int val;
            ListNode* next;
            ListNode(string s, int v)
            {
                sym = s;
                val = v;
                next = NULL;
            }
        };
        ListNode* head;


    public:
        Symbol_Table()
        {
            head = NULL;
        }

        ~Symbol_Table()
        {
            ListNode* tmp = head;
            while (tmp != NULL)
            {
                head = head->next;
                delete tmp;
                tmp = head;
            }
        }

        void append(string s, int v)
        {
            if (head == NULL)
            {
                head = new ListNode(s, v);
                return;
            }

            ListNode* tmp = head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new ListNode(s, v);
        }

        void display()
        {
            ListNode* tmp = head;
            while (tmp != NULL)
            {
                cout << tmp->sym << ": " << tmp->val << endl;
                tmp = tmp->next;
            }
        }
        void write(string filename, string str)
        {
            ofstream out(filename, ios::app);
            ListNode* tmp = head;
            while (tmp->sym != str)
            {
                tmp = tmp->next;
            }
            out << "@" << tmp->val << endl;
        }

        bool search(string str)
        {
            ListNode* tmp = head;
            while (tmp != NULL)
            {
                string check = tmp->sym;
                if (tmp->sym == str)
                {
                    return true;
                }
                tmp = tmp->next;
            }
            return false;
        }

        void load_labels(string s)
        {
            string str = removeSpaces(s);
            if (str.find("(") != string::npos)
            {
                string st = removeBrackets(str);
                this->append(st, count_lines);
                count_lines--;
            }
        }

        void load_symbols(string s)
        {
            string str = removeSpaces(s);
            if (str.find("@") != string::npos)
            {
                string::size_type i = str.find("@");
                if (i != string::npos)
                {
                    str.erase(i, 1);
                }
                if (this->search(str) == true)
                {
                    //do nothing
                }
                else if (this->search(str) == false && (is_digit(str)==true))
                {   //do nothing

                }
                else if (this->search(str) == false )
                {
                    this->append(str, x);
                    x++;
                }
            }
        }

        void read_symbols(string s, string filename)
        {
            string str = removeSpaces(s);
            ofstream out(filename, ios::app);  //codefile 2
            if (str.find("@") != string::npos)
            {
                string::size_type i = str.find("@");
                if (i != string::npos)
                {
                    str.erase(i, 1);
                }
                if (this->search(str) == true)
                {
                    this->write(filename, str);
                }
                else if (is_digit(str) == true)
                {
                    out << "@" << str << endl;
                }
            }
            else if (str.find("(") != string::npos)
            {
                //do nothing
            }
            else
            {
                out << str << endl;
            }
        }
    };

    string A_inst(string digit)
    {
        int num;
        num = stoi(digit);
        string binary = std::bitset<16>(num).to_string(); //searched the method of application of bitset from google
        return binary;
    }
    string comp(string cmp)
    {   //where a=0

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
        else if (cmp == "A+1") { return "0110111";}
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
        if (str.find('=') != string::npos)   //found this find function from stackoverflow
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

        else if (str.find('@') != string::npos)
        {
            int j = 0;
            while (str[j] != '\0') {   //while string is not end
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
        Symbol_Table c;

        c.append("R0", 0);
        c.append("R1", 1);
        c.append("R2", 2);
        c.append("R3", 3);
        c.append("R4", 4);
        c.append("R5", 5);
        c.append("R6", 6);
        c.append("R7", 7);
        c.append("R8", 8);
        c.append("R9", 9);
        c.append("R10", 10);
        c.append("R11", 11);
        c.append("R12", 12);
        c.append("R13", 13);
        c.append("R14", 14);
        c.append("R15", 15);
        c.append("SCREEN", 16384);
        c.append("KBD", 24576);
        c.append("SP", 0);
        c.append("LCL", 1);
        c.append("ARG", 2);
        c.append("THIS", 3);
        c.append("THAT", 4);
        string filename;
        cout << "Enter filename:";
        cin >> filename;
        ifstream in(filename);
        string result1 = in ? "Processing.." : "Failed to open file!";
        cout << result1;

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

        string write;
        while (!ifile.eof()) {
            getline(ifile, inst, '\n');
            c.load_labels(inst);
            count_lines++;
        }
        ifile.close();
        ifile.open("codefile.txt");

        while (!ifile.eof()) {
            getline(ifile, inst, '\n');
            c.load_symbols(inst);
        }
        ifile.close();
        ifile.open("codefile.txt");

        while (!ifile.eof()) {
            getline(ifile, inst, '\n');
            c.read_symbols(inst, "codefile2.txt");
        }

        fstream ofile("codefile2.txt", ios::in | ios::out);
        string result = ofile ? "Processing..\n" : "Failed to open file!\n";
        cout << result;
        while (!ofile.eof())
        {
            getline(ofile, inst, '\n');
            cout<< Code_Translator(inst);
        }
    }