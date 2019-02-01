/**
https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
https://www.geeksforgeeks.org/sum-nodes-binary-tree/
*/
#include <iostream>
#include <iomanip> // setw
using namespace std;
#define COUNT 10

class Node
{
public:
	int Key = 0;
	class Node* Left = nullptr, *Right = nullptr; // declare ptr's in one line
	Node(const int Key):Key(Key){}
};

// recursive function to traversal Binary Tree of Nodes and sum Keys
int sumBT(const Node* const Root)
{
	if (Root == nullptr)
		return 0;
	return Root->Key + sumBT(Root->Left) + sumBT(Root->Right);
}

/* Given a binary tree, print its nodes according to the "bottom-up" postorder traversal. */
void printPostorder(class Node* Root)
{
    if (Root == NULL)
        return;

    // first recur on Left subtree
    printPostorder(Root->Left);
    // then recur on Right subtree
    printPostorder(Root->Right);
    // now deal with the Root
    cout << Root->Key << " ";
}

/* Given a binary tree, print its nodes in inorder */
void printInorder(class Node* Root)
{
    if (Root == NULL)
        return;

    /* first recur on Left child */
    printInorder(Root->Left);
    /* then print the Key of Root */
    cout << Root->Key << " ";
    /* now recur on Right child */
    printInorder(Root->Right);
}

/* Given a binary tree, print its nodes in preorder */
void printPreorder(class Node* Root)
{
    if (Root == NULL)
        return;

    /* first print Key of Root */
    cout << Root->Key << " ";
    /* then recur on Left sutree */
    printPreorder(Root->Left);
    /* now recur on Right subtree */
    printPreorder(Root->Right);
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(Node* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->Right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->Key);

    // Process left child
    print2DUtil(root->Left, space);
}

// Wrapper over print2DUtil()
void print2D(Node* root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

void postorder(Node* p, int indent = 0)
{
    if(p != NULL) {
        if(p->Right) {
            postorder(p->Right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->Right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< p->Key << endl;
        if(p->Left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            postorder(p->Left, indent+4);
        }
    }
}

int main()
{
    class Node* Root = new Node(1);
    Root->Left = new Node(2);
    Root->Right = new Node(3);
    Root->Left->Left = new Node(4);
    Root->Left->Right = new Node(5);
    Root->Right->Left = new Node(6);
    Root->Right->Right = new Node(7);
    Root->Left->Left->Left = new Node(8);
    Root->Left->Left->Right = new Node(9);

    cout << "\nPreorder traversal of binary tree is \n";
    printPreorder(Root);

    cout << "\nInorder traversal of binary tree is \n";
    printInorder(Root);

    cout << "\nPostorder traversal of binary tree is \n";
    printPostorder(Root);

    cout << "\nSum Of BT \n" << sumBT(Root) << endl;

    print2D(Root);
    cout << endl;
    postorder(Root);
    return 0;
}
