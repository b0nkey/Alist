#include <iostream>
#include <bits/stdc++.h> 
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
        // swapped twice because junk in the array when i just move the ptr
        int *newList = new int [size+cap];
        for(i=0;i<size;i++){
            newList[i] = list[i];
        }
        delete list;
        size += cap;
        list = new int[size];

        for(i=0;i<size;i++){
            list[i] = newList[i];
        }
        
        delete newList;
    }

    // void extend(){
    //     // create new bigger list
    //     int* newList = new int[size+cap];

    //     // copy over
    //     for(i=0;i<size;i++){
    //         newList[i] = list[i];
    //     }

    //     // free old list

    //     // change ptr
    // }

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
        delete newArr;
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

    int aa(){
        return sizeof(list)/sizeof(list[0]);
    }
    
    void mySort(){ // standard bubble sort
        // for(i=0;i<count-1;i++){
        //     for(j=0;j<count-i-1;j++){
        //         if(list[j]>list[j+1]){
        //             int temp=list[j];
        //             list[j]=list[j+1];
        //             list[j+1]=temp;
        //         }
        //     }
        // }
        sort(list, list+count);
        isSorted = true;
    }
    
    void unsort(){
        // swap each element with another random
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
    l.getData();
    
    // l.extend();

    // for(int i=0;i<10;i++){
    //     l.insert(5);
    // }
    l.insert(2);
    l.insert(0);
    l.insert(23);
    l.insert(214);
    l.insert(100);
    l.insert(4);

    l.getData();

    Alist l2 = new Alist(l);

    cout << "new alist item\n" << "l1: " << endl;

    l.getData();

    cout << "l2: \n" << endl;

    l2.getData();

    l.mySort();
    l.getData();


    






    

    return 0;
}