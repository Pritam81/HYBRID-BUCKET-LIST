#include "bits/stdc++.h"
using namespace std;
int steps = 0;
int no_of_node = 0;
int no_of_bucket = 0;
int ele_per_buck = 0;
struct node *start;
vector<struct node *> hashmap;
struct node
{
    int data;
    struct node *next;
    struct node *pre;
};
void updateHashmap(int index, struct node *&head)
{
    if (no_of_node % no_of_bucket == 0)
    {
        hashmap.clear();
        struct node *ptr = head;
        no_of_node++;
        no_of_bucket = ceil(sqrt(no_of_node));
        ele_per_buck = ceil(static_cast<double>(no_of_node) / no_of_bucket);
        for (int i = 0; i < no_of_node; i++)
        {
            steps++;
            if (i % ele_per_buck == 0)
            {
                hashmap.push_back(ptr);
            }
            ptr = ptr->next;
        }
    }
    else if (index % ele_per_buck == 0)
    {
        int bucket_no = index / ele_per_buck;
        for (int i = bucket_no; i < hashmap.size(); i++)
        {
            struct node *add = hashmap[i];
            hashmap[i] = add->pre;
            steps++;
        }
        no_of_node++;
    }
    else
    {
        int bucket_no = index / ele_per_buck;
        for (int i = bucket_no + 1; i < hashmap.size(); i++)
        {
            struct node *add = hashmap[i];
            hashmap[i] = add->pre;
            steps++;
        }
        no_of_node++;
    }
}

void insert(struct node *&head)
{
    int index;
    cout << "Enter the index to insert: ";
    cin >> index;

    if (index < 0 || index > no_of_node)
    {
        cout << "Invalid index! It should be between 0 and " << no_of_node << "." << endl;
        return;
    }

    struct node *newnode = new struct node;
    cout << "Enter the element to insert: ";
    cin >> newnode->data;

    int bucket_no = index / ele_per_buck;
    struct node *ptr = hashmap[bucket_no];
    int position = index % ele_per_buck;

    if (index == 0)
    {
        newnode->next = head;
        if (head != nullptr)
        {
            head->pre = newnode;
        }
        head = newnode;
        start = head;
    }
    else
    {
        // Traverse within the block to find the correct position
        for (int i = 0; i < position && ptr != nullptr; i++)
        {
            ptr = ptr->next;
            steps++;
        }

        if (ptr != nullptr)
        {
            newnode->next = ptr;
            newnode->pre = ptr->pre;
            if (ptr->pre)
            {
                ptr->pre->next = newnode;
            }
            ptr->pre = newnode;
        }
    }

    no_of_bucket = ceil(sqrt(no_of_node));
    ele_per_buck = ceil(static_cast<double>(no_of_node) / no_of_bucket);

    updateHashmap(index, head);

    cout << "Node inserted successfully!" << endl;
    cout << "No of steps required is:" << steps << endl;

    steps = 0;
}
void createnode(struct node *ptr)
{
    cout << "Enter the number of nodes required: " << endl;
    cin >> no_of_node;

    no_of_bucket = ceil(sqrt(no_of_node));
    ele_per_buck = ceil(static_cast<double>(no_of_node) / no_of_bucket);
    struct node *start = ptr;

    for (int i = 1; i < no_of_node; i++)
    {
        struct node *newnode = new struct node;

        int x = rand() % 10;
        newnode->data = x;
        ptr->next = newnode;
        newnode->pre = ptr;
        newnode->next = NULL;
        ptr = newnode;

        if (i % ele_per_buck == 0)
        {
            hashmap.push_back(newnode); // Push pointer to the start of each bucket
        }
    }

    // Ensure the last bucket is correctly added
    if (hashmap.size() < no_of_bucket)
    {
        hashmap.push_back(ptr);
    }
}

void traverse(struct node *travel)
{
    int count = 0;
    int i = 0;
    cout << "NODE" << "   ADDRESS" << "   Data" << endl;
    while (travel != NULL)
    {
        cout << i << "       " << travel << "  " << travel->data << endl;
        travel = travel->next;
        i++;
    }
}

void access()
{
    int index;
    cout << "Enter the index you want to access: ";
    cin >> index;

    if (index < 0 || index >= no_of_node)
    {
        cout << "Invalid index! Must be in range 0 to " << no_of_node - 1 << "." << endl;
        return;
    }

    int bucket_no = floor(static_cast<double>(index) / ele_per_buck); // Correct bucket calculation

    if (bucket_no >= hashmap.size())
    {
        cout << "Error: Bucket number out of range." << endl;
        return;
    }

    struct node *ptr = hashmap[bucket_no];
    int start = bucket_no * ele_per_buck; // Calculate correct start index
    int no_of_comp = 0;

    for (int i = start; i < index && ptr->next != nullptr; i++)
    { // Traverse nodes
        ptr = ptr->next;
        no_of_comp++;
    }

    if (ptr == nullptr)
    {
        cout << "Error: Unable to access node. Invalid bucket configuration." << endl;
        return;
    }

    cout << endl
         << "Element at index " << index << " is " << ptr->data << endl;
    cout << "Element is at Bucket " << bucket_no << endl;
    cout << "Number of comparisons required: " << no_of_comp << endl;
}

void getaddress()
{
    cout << "INDEX   " << "ADDRESS" << endl;
    for (int i = 0; i < hashmap.size(); i++)
    {
        cout << i << "        " << hashmap[i] << endl;
    }

    cout << "no of node: " << no_of_node << endl;
}

void deletion()
{
    steps=0;
    cout << "Enter the index you wish to delete" << endl;
    int index;
    cin >> index;
    if (index < 0 || index >= no_of_node)
    {
        cout << "Index out of range" << endl;
        return;
    }
    int bucket_no = index / ele_per_buck;
    struct node *ptr = hashmap[bucket_no];
    int position = index % ele_per_buck;

    int new_no_of_bucket = ceil(sqrt(no_of_node - 1));
    int new_ele_per_buck = ceil(static_cast<double>(no_of_node - 1) / new_no_of_bucket);

    if (new_ele_per_buck != ele_per_buck || new_no_of_bucket != no_of_bucket)
    {

        if (index == 0)
        {
            start=start->next;
            ptr->next=NULL;
            delete(ptr);
            
        }
        else if (index == no_of_node - 1)
        {
            ptr->pre->next=NULL;
            delete(ptr);
        }
        else
        {

            for (int i = 0; i < position && ptr != nullptr; i++)
            {
                ptr = ptr->next;
                steps++;
            }

            ptr->pre->next = ptr->next;
            ptr->next->pre = ptr->pre;
            delete (ptr);
            
        }
        hashmap.clear();
            struct node *ptr = start;
          
            no_of_bucket = ceil(sqrt(no_of_node-1));
            ele_per_buck = ceil(static_cast<double>(no_of_node-1) / no_of_bucket);
            for (int i = 0; i < no_of_node-1; i++)
            {
               if (i % ele_per_buck == 0)
                {
                    hashmap.push_back(ptr);
                }
                ptr = ptr->next;
                steps++;
            }
    }
    else{
         no_of_bucket = ceil(sqrt(no_of_node-1));
        ele_per_buck = ceil(static_cast<double>(no_of_node-1) / no_of_bucket);

        if(position==0){

            for(int i=bucket_no;i<hashmap.size();i++){
                struct node * add= hashmap[i];
                hashmap[i]=add->next;
                steps++;

            }
            if(index==0){
                start=start->next;
                ptr->next=NULL;
                delete(ptr);


            }
            else{
                  ptr->pre->next=ptr->next;
                  ptr->next->pre=ptr->pre;
                  delete(ptr);

            }
        }
        else{
            for (int i = 0; i < position && ptr != nullptr; i++)
            {
                ptr = ptr->next;
                steps++;
            }

             if(index!=no_of_node-1){
            for(int i=bucket_no+1;i<hashmap.size();i++){
                struct node * add= hashmap[i];
                hashmap[i]=add->next;
                steps++;
            }
             }

            if(index==no_of_node-1){

                   ptr->pre->next=NULL;
                   delete(ptr);

            }
            else{

                ptr->pre->next=ptr->next;
                ptr->next->pre=ptr->pre;
                delete(ptr);


            }

        }
    }

    no_of_node--;
    cout<<"Node deletion successfull"<<endl;
    cout<<"Steps required is:"<<steps<<endl;
    steps=0;

}
int main()
{

    struct node *head = new struct node;
    struct node *ptr = head;
    head->data = 10;
    head->next = NULL;
    head->pre = NULL;
    hashmap.push_back(head);
    start = head;
    int choice;
    while(true)
    {

    cout<<"Enter the option you wish to perform"<<endl;
    cout<<"1.Create a list"<<endl;

    cout<<"2.Access element of node with index"<<endl;

    cout<<"3.Insert node in a list"<<endl;

    cout<<"4.delete a node from list"<<endl;

    cout<<"5.Traverse and show all element with index and address"<<endl;

    cout<<"6.Get Hashmap and Bucket details"<<endl;

    cout<<"7.Happy Exit :-)"<<endl;

        cin>>choice;
       switch (choice)
       {
           case 1: {
            createnode(start);
            break;
           }
           case 2:{
                access();
                break;
           }
           case 3:{
            insert(start);
            break;
           }
           case 4:{
                    deletion();
                    break;
           }
           case 5:{
            traverse(start);
            break;
           }
           case 6:{
            getaddress();
            break;

           }
           case 7:{
            exit(0);
           }
           default:{

            cout<<"Invalid Option"<<endl;

           }

           


                        
    }
    
}
}