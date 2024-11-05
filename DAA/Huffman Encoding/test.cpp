#include <iostream>
using namespace std;

class Node
{
public:
    int val;
    string symbol;
    string huffmanCode;
    Node *left;
    Node *right;

    Node(int n, string s)
    {
        this->val = n;
        this->symbol = s;
        this->huffmanCode = "";
        this->left = nullptr;
        this->right = nullptr;
    }
};

struct Compare
{
    bool operator()(const Node *l, const Node *r)
    {
        return l->val > r->val;
    }
};

class HuffmanEncoding
{
    Node *root;
    priority_queue<Node *, vector<Node *>, Compare> pq;

    void printCodes(Node *node, const string &val = "")
    {
        string newVal = val + node->huffmanCode;
    }

public:
    HuffmanEncoding(vector<string> &arr, vector<int> &freq)
    {
        this->root = nullptr;
        int n = arr.size();

        for (int i = 0; i < n; i++)
        {
            Node *node = new Node(freq[i], arr[i]);
            pq.push(node);
        }
    }

    void buildTree()
    {
        while (pq.size() > 1)
        {
            Node *l = pq.top();
            pq.pop();
            Node *r = pq.top();
            pq.pop();
            l->huffmanCode = "0";
            r->huffmanCode = "1";

            Node *node = new Node(l->val + r->val, l->symbol + r->symbol);
            node->left = l;
            node->right = r;
            pq.push(node);
        }

        this->root = pq.top();
        pq.pop();
    }

    void display()
        [if (this -> root != nullptr)
             printCodes(this->root);
    ]
};