#include <iostream>
// #include <bits/stdc++.h>
#include <cstdlib>
#define DEFAULTCAP 8
using namespace std;

// TODO: make a setter for changing the cap then call that from assigned cap constructor


class Alist{
 private:
    int i, j;
    int cap; // size incrementor / decrementor
    int count; // member count in list
    int size; // list size
    bool isSorted; 
    int *list = nullptr; // pointer to start of list

 public:
    Alist(){ // deault constructor
        cap = DEFAULTCAP;
        list = new int [DEFAULTCAP];
        size = cap;
        count = 0;
        isSorted = false;
    } 
    
    Alist(int initialCap){ // assigned cap constructor
        list = new int [initialCap];
        cap = initialCap;
        size = initialCap;
        count = 0;
    }

    Alist(Alist *a2){ // copy constructor
        cap = a2->cap;
        count = a2->count;
        size = a2->size;
        isSorted = a2->isSorted;
        list = new int [cap];
        for(i=0;i<count;i++){ list[i] = a2->list[i]; }
    }

    ~Alist(){ //destructor
        delete list;
    }

    void getData(){
        cout << "\nItems on list: " << count << endl;
        cout << "List size: " << size << endl;
        showContents();
    }

    void extend(){ // extends size by cap
        int *newList = new int [size+cap];
        for(i=0;i<size;i++){
            newList[i] = list[i];
        }
        delete[] list;
        size += cap;
        list = new int[size];

        for(i=0;i<size;i++){
            list[i] = newList[i];
        }
        
        delete[] newList;
    }

    int shrink(){
        if((size-count) < cap){
            return 0;
        }
        size -= cap;
        int *newArr = new int[size];
        for(i=0;i<size;i++){ newArr[i] = list[i]; }
        delete list;
        list = new int[size];
        for(i=0;i<size;i++){ list[i] = newArr[i]; }
        delete[] newArr;
        return 1;
    }

    void showContents(){
        cout << "List Contents: " << endl;
        for(i=0;i<count;i++){
            cout << "[" << i << "]" << " = " <<  list[i] << endl;
        }
    }   

    void insert(int num){ // add sorted conditional
        if(count == size){ extend(); }
        list[count] = num;
        count++;

    }

    void remove(){
        list[count] = 0;
        count--;
    }
    
    void sortList(){
        sort(list, list+count);
        isSorted = true;
    }
    
    void unsort(){
        // swap each element with another random

        cout << "starting rand" << endl;
        int r, temp;
        for(i=0;i<count;i++){
            r = randNum();
            temp = list[i];
            
            list[i] = list[r];
            list[r] = temp;
            
        }

    }
    
    int randNum(){
        int a = rand() % count;
        return a;
    }
    //move consttuctor
    //copy assignment 
    //move assignment
    //remove
    //unsort
    //save
    //search
};




    



int main(){
    Alist l;

    l.insert(2);
    l.insert(5);
    l.insert(0);
    l.insert(1);
    l.insert(0);
    l.insert(4);
    l.insert(6);
    l.insert(5);

    l.getData();

    l.sortList();
    l.getData();

    l.unsort();
    l.getData();
    






    

    return 0;
}