#include <iostream>

using namespace std;
/// Hossam Mohamed Aboud
template <class T,int m>
struct BtreeNode
{
    T* keys;
    BtreeNode **childs;
    BtreeNode *parent;
    int currentkeys;
    bool leaf;
    BtreeNode(bool leaf1)
    {
        leaf=leaf1;
        keys=new T[m];
        childs= new BtreeNode<T,m>*[m+1];
        for(int i = 0; i < m+1; i++)///null childs
        {
            childs[i] = NULL;
        }
        currentkeys=0;
        parent = NULL;
    }
    void insertkeys(T value)///add value to nonfull node
    {
        int lastposition=currentkeys-1;

            while(lastposition>-1&&keys[lastposition]>value)///shift right if needed
            {
                keys[lastposition+1]=keys[lastposition];
                lastposition--;
            }
            keys[lastposition+1]=value;
            currentkeys++;

    }
    void split()
    {

        BtreeNode <T,m> *newnode=new BtreeNode <T,m>(leaf);
        ///find the mid value to divide the node
        int mid=currentkeys/2;
        if(currentkeys%2==0)
        {
            mid=mid-1;
        }
        T midvalue=keys[mid];

        int i=0,j=mid+1;
        for(;j<currentkeys;i++,j++)///divide the values and childs in 2 nodes
        {
            newnode->keys[i]=keys[j];
            newnode->currentkeys++;
            newnode->childs[i]=childs[j];
            childs[j]=NULL;
        }
        newnode->childs[i]=childs[j];
        childs[j]=NULL;
        currentkeys=mid;
        if(parent==NULL)///connect new nodes with parnet
        {
            BtreeNode <T,m> *newnode2=new BtreeNode <T,m>(false);
            newnode2->keys[0]=midvalue;
            newnode2->currentkeys++;
            newnode2->childs[0]=this;
            newnode2->childs[1]=newnode;
            parent=newnode2;
            newnode->parent=newnode2;
        }
        else
        {
            newnode->parent = parent;
            parent->insertkeys(midvalue);
            for(i = 0; i < m+1;i++)///find current child position to swap it
            {
                if(parent->childs[i] == this)
                {
                    break;
                }
            }
            BtreeNode <T,m> *temp = parent->childs[i+1];
            BtreeNode <T,m> *temp2;
            parent->childs[i+1] = newnode;
            for(j = i+2; j < m+1; j++)///add new child in his position
            {
                temp2 = parent->childs[j];
                parent->childs[j] = temp;
                temp = temp2;
            }
            if(parent->currentkeys==m)///if parent full split him
            {
                parent->split();
            }

        }

    }
};
template <class T,int m>
class BTree
{
    private:
        BtreeNode <T,m> *root=NULL;
        void print1(BtreeNode <T,m> *node,string space=" ")
        {
            if (node != NULL)
            {
                printkeys(node->keys,node->currentkeys);
                for(int i=0;i<m;i++)
                {
                    if(node->childs[i]!=NULL)
                    {
                        cout<<space;
                        print1(node->childs[i],space+" ");
                    }
                }

            }
        }
        void printkeys(T*keys,int currentKeys)
        {
            for(int i=0;i<currentKeys;i++)
            {
                if(i<currentKeys-1)
                    cout<<keys[i]<<",";
                else
                    cout<<keys[i]<<endl;
            }

        }
    public:
        Btree()
        {
            root=NULL;
        }
        void Insert(T value)
        {

            if(root==NULL)///insert in empty tree
            {

                root=new BtreeNode<T,m>(true);
                root->keys[0]=value;
                root->currentkeys=1;

            }
            else
            {

                BtreeNode <T,m> *currnode=root;
                while(!currnode->leaf)///find leaf node to insert
                {
                    if(value>currnode->keys[currnode->currentkeys-1])
                    {
                        currnode=currnode->childs[currnode->currentkeys];
                    }
                    else
                    {
                        for(int i=0;i<currnode->currentkeys;i++)
                        {
                            if(currnode->keys[i]>value)
                            {
                                currnode=currnode->childs[i];

                                break;
                            }
                        }
                    }

                }

                currnode->insertkeys(value);
                if(currnode->currentkeys==m)///split the node if exceed the maximum keys after insert
                {

                    currnode->split();
                    if(root->parent!=NULL)///handl right root after spliting
                    {
                        root=root->parent;
                    }
                }

            }
        }
        void Print()///print
        {
            print1(root);
        }
};
int main()
{
    // Construct a BTree of order 3, which stores int data
    BTree<int,3> t1;

    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);

    t1.Print(); // Should output the following on the screen:

    /*
    1,4
      0
      2,3
      5
    */

    // Construct a BTree of order 5, which stores char data
    BTree<char,5> t;

    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');

    t.Print(); // Should output the following on the screen:

    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */

    return 0;
}
