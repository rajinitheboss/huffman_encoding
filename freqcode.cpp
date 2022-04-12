#include<bits/stdc++.h>
using namespace std;

int main()
{
    ifstream infile;
    infile.open("source.txt",ios::in);
    string c;
    ofstream outfile;
    outfile.open("characterfrequency.txt",ios::out);
    int A[63]={0};
    while(getline(infile,c))
    {
        char s;
        for(int i=0;i<c.length();i++)
        {
            s=c[i];
            int k=(int)s;
            if(k>=65&& k<=90)
            {
                A[k-65]++;
            }
            else if(k>=97 && k<=122)
            {
                A[k-97+26]++;
            }
            else if(k>=48 && k<=57)
            {
                A[k-48+52]++;
            }
            else if(k==32)
            {
                A[62]++;
            }
        }
    }
    for(auto i=0;i<26;i++)
    {
        outfile<<(char)(i+65)<<" "<<A[i]<<endl;
    }
    for(auto i=26;i<52;i++)
    {
        outfile<<(char)(i+97-26)<<" "<<A[i]<<endl;
    }
    for(auto i=52;i<62;i++)
    {
        outfile<<(char)(i+48-52)<<" "<<A[i]<<endl;
    }
    outfile<<" "<<" "<<A[62]<<endl;
    return 0;
}