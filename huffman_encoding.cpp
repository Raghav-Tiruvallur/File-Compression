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


// char getCharacter(char c,Node* temp)
// {
//     queue<pair<Node*,string>> q;
//     q.push({temp,""});
//     while(!q.empty())
//     {
//         Node* node=q.front().first;
//         string current=q.front().second;
//         q.pop();
//         if(node->ch==c)
//         {
//             return current;
//         }
//         if(node->left)
//         {
//             q.push(node->left);
//         }
        
//     }
// }



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
    string x="abcasiubjrlldbndbnjbsnvpudfuyh vkbbuar dlbgl";
    unordered_map<char,int> f;
    ifstream file("file.txt");
    ofstream compressed_file("compressed.txt");
    string data;
    string fileData;
    while(getline(file,data))
    {
        fileData+=data+"\n";
    }
    for(char c:fileData)  
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
    Node* temp=head;
    getCodes(head,codes);
    string encodedText;
    for(char c:fileData)
    {
        encodedText+=codes[c];
    }
    string uncompressed_data;
    Node* root=temp;
    for(char c:encodedText)
    {
        if(temp->ch!='$')
        {
            uncompressed_data+=temp->ch;
            temp=root;
        }
        if(c == '0')
        {
            temp=temp->left;
        }
        else if(c == '1')
        {
            temp=temp->right;
        }
    }
    cout<<uncompressed_data<<"\n";

}