#include <iostream>
#include <map>
#include <queue>
using namespace std;

class TreeNodeCustom{
public:
    char letter;
    int freq;
    TreeNodeCustom* left;
    TreeNodeCustom* right;
    TreeNodeCustom() : left(nullptr), right(nullptr) {} // default constructor
    TreeNodeCustom(int f, char le) : freq(f), letter(le), left(nullptr), right(nullptr) {} // 1-arg constructor
    TreeNodeCustom(int f, char le, TreeNodeCustom* l, TreeNodeCustom* r) : freq(f), letter(le), left(l), right(r) {} // 3-arg constructor

    bool operator< (const TreeNodeCustom& r) const {
        return freq>r.freq;
    }
};

struct CmpTreeNodePointers{
    bool operator()(const TreeNodeCustom* lhs, const TreeNodeCustom* rhs) const{
        return lhs->freq > rhs->freq;
    }
};

void PrintLeafNodes(TreeNodeCustom* root, string& encoding){
    if(root==nullptr) return;
    encoding.push_back('0');
    PrintLeafNodes(root->left, encoding);
    encoding.pop_back();

    if(root->left==nullptr && root->right==nullptr)
        cout << "[" << root->letter << ", " << root->freq << "]" << " -> " << encoding << endl;

    encoding.push_back('1');
    PrintLeafNodes(root->right, encoding);
    encoding.pop_back();
}

void HuffmanCodes(map<char, int> freq){

    // creating priority queue
    cout << "Letter with frequencies: \n";
    priority_queue<TreeNodeCustom*, vector<TreeNodeCustom*>, CmpTreeNodePointers> heap;
    for(pair<char, int> data : freq){
        cout << "[" << data.first << ", " << data.second << "], ";
        TreeNodeCustom* temp = new TreeNodeCustom(data.second, data.first);
        heap.push(temp);
    }
    cout << "\n\n";

    int n = freq.size();
    for(int i=0; i<n-1; i++){

        TreeNodeCustom* x = heap.top(); heap.pop(); // extract 1st min
        TreeNodeCustom* y = heap.top(); heap.pop(); // extract 2nd min

        // create new node with updated freq
        TreeNodeCustom* node = new TreeNodeCustom();
        node->freq = x->freq + y->freq;
        node->left=x;
        node->right=y;

        // push new node in the tree
        heap.push(node);
    }

    cout << "Prefix free Huffman Encoding:\n";
    // print the huffman codes
    TreeNodeCustom* root = heap.top();
    string encoding="";
    PrintLeafNodes(root, encoding);
}

int main(){

    map<char, int> freq = {{'a', 45}, {'b', 20}, {'c', 10}, {'d', 17}, {'e', 6}, {'f', 5}, {'g', 18}};

    HuffmanCodes(freq);

    return 0;
}
