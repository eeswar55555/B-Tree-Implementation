// TIME complexity  = O(nlogn)
// SPACE complexity = O(1)

#include<bits/stdc++.h>
using namespace std;

//****************************************
int d=2;  // you can change "d" value here
//****************************************

struct bnode
{
    int count=0;
    int keys[9999]={0};
    bnode* ptr[9999]={NULL};
};
typedef struct bnode* BTPTR;

int max_height=0;

void print(BTPTR T,int h=0)
{
    if(T==NULL)
    return ;
    max_height=max(max_height,h);
    int i=0;
    for(i=0;i<T->count;i++)
    {
        print(T->ptr[i],h+1);
        // cout<<T->keys[i]<<" ";
    }
    print(T->ptr[i],h+1);
}
void printt(BTPTR T,int l,int h=0)
{
    if(T==NULL)
    return ;
    int i=0;
    for(i=0;i<T->count;i++)
    {
        printt(T->ptr[i],l,h+1);
        if(h==l)
        cout<<T->keys[i]<<" ";
    }
    printt(T->ptr[i],l,h+1);
}

// ******** IMPORTANT GLOBALS ********** THESE ARE USED IF WE WISH TO ADJUST A NEW KEY,PTR TO A PARENT NODE
bool R_U_ADJUSTING=false;
int new_key;
BTPTR new_node;

// ******** ||||||||||||||||| **********

// THIS WILL SORT THE TREE NODE IN o(n) time
void sort_node(BTPTR T)
{
    if(T->count >=2 and T->keys[T->count-1] > T->keys[T->count-2])
    return ;

    int key = T->keys[T->count-1];
    bnode* right_pointer = T->ptr[T->count];
    int i=T->count-2;
    
    for(i = T->count-2 ;i>=0;i--)
    {
        if(T->keys[i]>key)
        {
            T->keys[i+1]=T->keys[i];
            T->ptr[i+2]=T->ptr[i+1];
        }
        else
        break;
    }
    i++;
    T->keys[i]=key;
    T->ptr[i+1]=right_pointer;
}

// THIS WILL PUT ALL THE VALUES GREATER THAN MEDIAN IN A NEW RIGHT SIDE NODE 
void put_values(BTPTR T, BTPTR new_right_node)
{
    int median=T->count/2;
    new_key=T->keys[median];

    for(int i=median+1 ; i<T->count ; i++)
    {
        new_right_node->keys[i-median-1]=T->keys[i];
        new_right_node->ptr[i-median-1]=T->ptr[i];
    }
    new_right_node->ptr[T->count-median-1]=T->ptr[T->count];
    new_right_node->count=T->count-median-1;
    new_node=new_right_node;

    T->count=median;
}

// MAIN FUNCTION IN WHICH WE ARE ADDING
void Add(BTPTR T,int key)
{
            // BEFORE ADDING INTO CURRENT TREE NODE CHECK IF IT IS NEEDED TO BE ADDED IN CHILDREN NODES 
            for(int i=0; i <= d ;i++)
            {
                if(T->ptr[i]!=NULL and (key < T->keys[i] or key < T->ptr[i]->keys[0] or i==T->count))
                {
                    Add(T->ptr[i],key);

                    if(R_U_ADJUSTING)
                    {
                        T->keys[T->count++]=new_key;
                        T->ptr[T->count]=new_node;
                        goto label1;
                    }
                    else
                    return ;
                }
            }
            T->keys[T->count++]=key;
    //         for(int i=0;i<T->count;i++)
    // cout<<T->keys[i]<<" ";
    // cout<<endl;

            label1 :
            sort_node(T);
            if( T->count > d ) // IF overflow
            {
                R_U_ADJUSTING=true;
                //take median and split
                BTPTR new_right_node=new(bnode);
                //now put all medians right values in new_right_node
                put_values( T , new_right_node);
            }
            else
            R_U_ADJUSTING=false;
}

void lvl_print(BTPTR T)
{
    max_height=0;
    print(T);
    for(int i=0;i<=max_height;i++)
    {printt(T,i);cout<<endl;}
    // queue<BTPTR> q;
    // q.push(T);

    // while(!q.empty())
    // {

    //     BTPTR P = q.front();q.pop();

    //     if(P==NULL)
    //     continue;


    //     int i=0;
    //     for(i=0;i<P->count;i++)
    //     {
    //         q.push(P->ptr[i]);
    //         cout<<P->keys[i]<<" ";
    //     }
    //     q.push(P->ptr[i]);
    //     cout<<endl;
    // }
}

int main()
{
    BTPTR T=new(bnode);

    // int A[10]={5,55,7,2,65,53,1,6,4,10};
    
    for(int i=10;i>=1;i--)
    {
        Add(T,11-i);  // add key to tree
        if(R_U_ADJUSTING)  // create a new parent node
        {
            BTPTR root=new(bnode);
            root->keys[root->count++]=new_key;
            root->ptr[0]=T;
            root->ptr[1]=new_node;
            R_U_ADJUSTING=false;
            T=root;
        }
        lvl_print(T);
        cout<<"\n------------------------------\n";
    }
}
