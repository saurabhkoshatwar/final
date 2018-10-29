#include<iostream>
#include<omp.h>
#include<queue>
using namespace std;
class node{
    public:
    node *left,*right;
    int data;
};
class bfs{
    public:
    node* insert(node* root,int data)
    {
        if(!root)
        {
            root = new node;
            root->data = data;
            root->left = NULL;
            root->right = NULL;
            return root;
        }
        queue<node*> q;
        q.push(root);

        while(!q.empty())
        {
            node* temp = q.front();
            q.pop();

            if(temp->left == NULL)
            {
                temp->left = new node;
                temp->left->data = data;
                temp->left->right = NULL;
                temp->left->left = NULL;
                return root;
            }
            else{
                q.push(temp->left);
            }

            if(temp->right == NULL)
            {
                temp->right = new node;
                temp->right->data = data;
                temp->right->right = NULL;
                temp->right->left = NULL;
                return root;
            }
            else{
                q.push(temp->right);
            }
            
        }
    }

    void doBfs(node *root)
    {

        queue<node*> q;
        q.push(root);

        while(!q.empty())
        {
            node *temp ;
            #pragma omp parallel for
            for(int i=0;i<q.size();i++)
            {
                #pragma omp critical
                {
                    temp = q.front();
                    q.pop();
                    cout<<temp->data<<" ";
                }
                #pragma omp critical
                {        
                if(temp->left)
                    q.push(temp->left);
                if(temp->right)
                    q.push(temp->right);  
                }     
            }
        }
    }    

};

int main()
{
    bfs b;
    char ans;
    int data;
    node* root=NULL;

    do{
        cout<<"Enter Data"<<endl;
        cin>>data;
        root = b.insert(root,data);
        cout<<"More Nodes?(y/n)"<<endl;
        cin>>ans;
    }while(ans=='y' || ans=='Y');
    b.doBfs(root);
    return 0;
}