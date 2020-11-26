#include<bits/stdc++.h>

using namespace std;

struct binary_tree
{
    int value;
    binary_tree *left=nullptr;      //for small value.
    binary_tree *right=nullptr;     //for greater value.
};

binary_tree *tree=nullptr;

void add(int input)
{
    if(tree==nullptr)
    {
        tree=new binary_tree();
        tree->value=input;
    }
    else
    {
        binary_tree *new_node=tree;
        while(true)
        {
            if(new_node->value>input)
            {
                if(new_node->left==nullptr)
                {
                    break;
                }
                else
                {
                    new_node=new_node->left;
                    continue;
                }
            }
            else if(input>new_node->value)
            {
                if(new_node->right==nullptr)
                {
                    break;
                }
                else
                {
                    new_node=new_node->right;
                }
            }
            else
                return;
        }
        binary_tree *new_input_node=new binary_tree();
        new_input_node->value=input;
        if(input>new_node->value)
        {
            new_node->right=new_input_node;
        }
        else
        {
            new_node->left=new_input_node;
        }
    }
}

bool value_in_tree(int val)
{
    binary_tree *current=tree;
    while(current->value!=val)
    {
        if(current->value>val)
        {
            if(current->left==nullptr)
                return 0;
            current=current->left;
        }
        else
        {
            if(current->right==nullptr)
                return 0;
            current=current->right;
        }
    }
    return 1;
}


//this function is confusing. I guess it's not implemented in right way.
bool remov(int val)
{
    binary_tree *current=tree;
    while(current->value!=val)
    {
        if(current->value>val)
        {
            if(current->left==nullptr)
                return 0;
            current=current->left;
        }
        else
        {
            if(current->right==nullptr)
                return 0;
            current=current->right;
        }
    }
    return 1;
}

void preOrder(binary_tree *myTree)
{
    if(myTree->left==nullptr && myTree->right==nullptr)
    {
        cout<<myTree->value<<" ";
        return;
    }
    else if(myTree->left==nullptr && myTree->right!=nullptr)
    {
        cout<<myTree->value<<" ";
        preOrder(myTree->right);
    }
    else if(myTree->left!=nullptr && myTree->right==nullptr)
    {
        cout<<myTree->value<<" ";
        preOrder(myTree->left);
    }
    else
    {
        cout<<myTree->value<<" ";
        preOrder(myTree->left);
        preOrder(myTree->right);
    }

   /* if (node == nullptr)
		return;
	cout << myTree->data << " ";

	preOrder(myTree->left);
	preOrder(myTree->right);*/


}

void inOrder(binary_tree *myTree)
{
    if (myTree == nullptr)
		return;

	inOrder(myTree->left);

	cout << myTree->value << " ";

	inOrder(myTree->right);
}

void postOrder(binary_tree *myTree)
{
    if (myTree == nullptr)
		return;

	postOrder(myTree->left);
	postOrder(myTree->right);
	cout << myTree->value << " ";
}

bool isin(int ch[],int val,int pos)
{
    for(int i=0;i<pos;i++)
    {
        if(ch[i]==val)
            return true;
    }
    return false;
}

int main()
{
    add(5);
    add(34);
    add(235);
    inOrder(tree);
}