#include<bits/stdc++.h>
using namespace std;


struct Node{
    char ch;
    int value;
    Node* left;
    Node* right;
    
}typedef Node;

class myComparator {
  public:
    bool operator() (const Node* p1, const Node* p2) {
     
        return p1->value > p2->value;
    }
};



void getCodes(Node* head,unordered_map<char,string>& codes)
{
    queue<pair<Node*,string>> q;
    q.push({head,""});
    while(!q.empty())
    {
        string current=q.front().second;
        Node* node = q.front().first;
        q.pop();
        int value=node->value;
        if(node->ch!='$')
        {
            codes[node->ch] = current;
        }
        if(node->left)
        {
            q.push({node->left,current + "0"});
        }
        if(node->right)
        {
            q.push({node->right,current + "1"});
        }
    }
}

int main()
{
    string x="abcasiubjrlldbndbnjbsnvpudfuyhvkbbuardlbgl";
    unordered_map<char,int> f;
    // f['a']=5;
    // f['b']=9;
    // f['c']=12;
    // f['d']=13;
    // f['e']=16;
    // f['f']=45;
    for(char c:x)  
    {
        f[c]++;
    }
   
    priority_queue<Node*, vector<Node*>,myComparator> pq;
    unordered_map<char,string> codes;
    for(auto p:f)
    {
        Node* x=(Node *) malloc(sizeof(Node));
        x->ch=p.first;
        x->left=NULL;
        x->right=NULL;
        x->value=p.second;
        pq.push(x);
    }
    while(pq.size() != 1){
        auto x=pq.top();
        pq.pop();
        auto y=pq.top();
        pq.pop();
        Node* intermediateNode=(Node*) malloc(sizeof(Node));
        int sum=x->value + y->value;
        intermediateNode->ch='$';
        intermediateNode->left=x;
        intermediateNode->right=y;
        intermediateNode->value=sum;
        pq.push(intermediateNode);

    }
    Node* head=pq.top();
    
    getCodes(head,codes);
    for(auto p:codes)
    {
        cout<<p.first<<":"<<p.second<<"\n";
    }
    

}