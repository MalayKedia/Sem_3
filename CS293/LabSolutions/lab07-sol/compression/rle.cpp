#include "rle.h"

// Constructor
rle::rle(int gamma)
{
    this->gamma = gamma;
}

// Convert integer to gamma-bit binary string
string rle::f(int i)
{
    string s;
    while (i > 0)
    {
        s = to_string(i % 2) + s;
        i /= 2;
    }
    while (s.length() < rle::gamma)
    {
        s = '0' + s;
    }
    return s;
}

// Convert gamma-bit binary string to integer
int rle::g(string i)
{
    int s = 0;
    for (int j = 0; j < rle::gamma; j++)
    {
        s = s * 2 + (i[j] - '0');
    }
    return s;
}


// Compress the input file
string rle::compress(string input_string)
{
    string ans="";
    ofstream output("input.txt");
    output << input_string;
    output.close();
    ifstream input("input.txt");
    output.close();
    char c;
    int count = 1;
    char prev = input.get();
    ans += prev;
    while (input.get(c))
    {
        if (c == prev)
        {
            count++;
        }
        else
        {
            while (count > (1 << gamma) - 1)
            {
                ans += f((1<<gamma)-1);
                count -= (1<<gamma)-1;
                ans += f(0);
            }
            ans += f(count);
            count = 1;
        }
        prev = c;
    }
    while (count > (1 << gamma) - 1)
    {
                ans += f((1<<gamma)-1);
                count -= (1<<gamma)-1;
                ans += f(0);
            
    }
    ans += f(count);
    input.close();
    return ans;
}

// Decompress the input file
string rle::decompress(string input_string)
{
    string ans="";
    ofstream output("input1.txt");
    output << input_string;
    output.close();
    ifstream input("input1.txt");
    if (!input.is_open())
    {
        cout << "Error opening file" << endl;
        return "Error";
    }
    char c;
    char c1;
    string s="";
    input >> c;
    int parity = 0;
    // Read gamma-gamma bits from input file and print c that many times in output file
    while (input >> c1 )
    {
        string s1 = "";
        s1 += c1;
        for (int i=0;i<rle::gamma-1;i++)
        {
            input >> c1;
            s1 += c1;
        }
   
        int count = g(s1);
        for (int i=0;i<count;i++)
        {
            if (parity == 0) ans +=  c;
            else if (c == '0') ans += '1';
            else if (c == '1') ans+= '0';
           
        }
        
        parity = 1-parity;
    }
    input.close();
    return ans;
}

