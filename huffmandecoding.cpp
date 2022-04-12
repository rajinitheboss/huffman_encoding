#include<bits/stdc++.h>
using namespace std;
class Node
{
    private:
        int key;
        Node *left;
        Node *right;
        char c;
    public:
        Node()
        {
            c='\0';
            this->left=NULL;
            this->right=NULL;
            key=0;
        }    
        void updatekey(int key)
        {
            this->key=key;
        }
        void updatechar(char c)
        {
            this->c=c;
        }
        int getkey()
        {
            return key;
        }
        void updateleft(Node *ptr)
        {
            this->left=ptr;
        }
        void updateright(Node *ptr)
        {
            this->right=ptr;
        }
        char getchar()
        {
            return c;
        }
        Node* getleft()
        {
            return this->left;
        }
        Node* getright()
        {
            return this->right;
        }
};
class Tree
{
    private:
        Node * root;
        map<char,string> m;
    public:
        Tree()
        {
            root=NULL;
        }
        Node* insert(Node * ptr1,Node *ptr2)
        {
            Node *newptr=new Node;
            newptr->updatekey(ptr1->getkey()+ptr2->getkey());
            if(ptr1->getkey()<ptr2->getkey())
            {
                newptr->updateleft(ptr1);
                newptr->updateright(ptr2);
            }
            else
            {
                newptr->updateright(ptr1);
                newptr->updateleft(ptr2);
            }
            return newptr;
        }
        void updateroot(Node * ptr)
        {
            root=ptr;
            return;
        }
        int rootvalue()
        {
            return root->getkey();
        }
        string treetraverse(string k)
        {
            string p;
            Node *ptr=root;
            for(int i=0;i<k.length();i++)
            {
                if(k[i]=='1')
                    ptr=ptr->getright();
                else
                    ptr=ptr->getleft();
                if(ptr->getchar()!='\0')
                {
                    p=p+ptr->getchar();
                    ptr=root;
                }
            }
            return p;
        }
        void traverse()
        {
            string s="";
            traverse(root,s);
        }
        void traverse(Node* ptr,string s)
        {
            if(ptr->getchar()!='\0')
            {
                m[ptr->getchar()]=s;
                return ;
            }
            string k=s+'0';
            traverse(ptr->getleft(),k);
            string p=s+'1';
            traverse(ptr->getright(),p);
        }
        void printmap()
        {
            map<char,string> ::iterator it;
            for(it=m.begin();it!=m.end();it++)
            {
                cout<<(*it).first<<" "<<(*it).second<<endl;
            }
        }
        string encode(string s)
        {
            string ans="";
            for(int i=0;i<s.length();i++)
            {
                ans=ans+m[s[i]];
            }
            return ans;
        }
};
class myprioityqueue
{
    private:
        vector<Node*> arrayadd;
    public:
        void pop()
        {
            arrayadd.erase(arrayadd.begin());
            return;
        }
        void push(Node *ptr)
        {
            bool flag=0;
            for(int i=0;i<arrayadd.size();i++)
            {
                if(arrayadd[i]->getkey()>ptr->getkey())
                {
                    arrayadd.insert(arrayadd.begin()+i,ptr);
                    flag=1;
                    break;
                }
            }
            if(!flag)
            {
                arrayadd.push_back(ptr);
            }
        }
        Node * peak()
        {
            return arrayadd[0];
        }
        int size()
        {
            return arrayadd.size();
        }
};
int main()
{
    ifstream infile;
    infile.open("characterfrequency.txt",ios::in);
    string s;
    int k;
    myprioityqueue q;
    while(getline(infile,s))
    {
        char c=s[0];
        string p=s.substr(2);
        k=stoi(p);
        Node *ptr=new Node();
        ptr->updatekey(k);
        ptr->updatechar(c);
        q.push(ptr);
    }
    Tree t;
    while(q.size()!=1)
    {
        Node *ptr1=q.peak();
        q.pop();
        Node* ptr2=q.peak();
        q.pop();
        Node *ptr=t.insert(ptr1,ptr2);
        q.push(ptr);
    }
    t.updateroot(q.peak());
    q.pop();
    t.traverse();
    ifstream inf;
    inf.open("encodedstring.txt",ios::in);
    ofstream ouf;
    ouf.open("decodedstring.txt",ios::out);
    string inp;
    while(getline(inf,inp))
    {
        ouf<<t.treetraverse(inp)<<endl;
    }
    ouf.close();
    inf.close();
    return 0;
}