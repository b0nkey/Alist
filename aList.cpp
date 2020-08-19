#include <iostream>
#include <cstdlib>
#define DEFAULTCAP 8
using namespace std;

// TODO: make setter for changing cap then call that from assigned cap constructor
// TODO: declaring l2 then assigning works for overload but on-the-spot does not.
// TODO: make setter and getter methods and change permissions (const) where needed
// TODO: Check insert method. does it add one space? i think you just copypasted


class Alist{
 private:
    int i, j;
    int cap; // size incrementor / decrementor
    int count; // member count in list
    int size; // list size
    bool isSorted; 
    int *list = nullptr; // pointer to start of list

 public:
    Alist(int initialCap=DEFAULTCAP, bool sorted=false){
        list = new int [initialCap];
        cap = initialCap;
        size = initialCap;
        count = 0;
        if(sorted == true) sort();
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
        delete[] list;
    }
    
    // SETTERS AND GETTERS

    void setSize(int sizeSet){ this->size = sizeSet; }
    void setCount(int countSet){ this->count = countSet; }
    void setSorted(bool sortedSet){ this->isSorted = sortedSet; }

    int get_size(){ return this->size;}
    int get_count(){ return this->count; }
    bool getIsSorted(){ return this->isSorted; }

    void getData(){
        cout << "\nItems on list: " << count << endl;
        cout << "List size: " << size << endl;
        showContents();
    }

    void extend(){ // extends size by cap
        // maybe just make this return a new list

        int newList [size+cap];
        for(i=0;i<size;i++){
            newList[i] = list[i];
        }
        // delete[] list;
        size += cap;
        list = new int[size];

        for(i=0;i<size;i++){
            list[i] = newList[i];
        }
        
        // delete[] newList;
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

    void insert(int num){
        if(count == size) extend(); 

        if(isSorted == false){
            list[count] = num;
        }else{
            int i, insertIndex;
            for(i=0;i<count;i++){
                if(num <= list[i]){
                    insertIndex = i;
                    break;
                }
                if(i==count-1) insertIndex = i+1;
            }
            i=count;
            while(i>insertIndex){
                list[i] = list[i-1];
                i--;
            }
            list[insertIndex] = num;
        }
        count++;
    }

    void remove(){
        list[count] = 0;
        count--;
    }
    
    void sort(){
        std::sort(list, list+count);
        isSorted = true;
    }
    
    void unsort(){
        // swap each element with another random
        int r, temp;
        for(i=0;i<count;i++){
            r = randNum();
            temp = list[i];
            
            list[i] = list[r];
            list[r] = temp;
        }
        isSorted = false;
    }
    
    int randNum(){
        int a = rand() % count;
        return a;
    }
    
    
    // OVERLOADS

    Alist& operator=(Alist &source){
        cout << "in op= overload" << endl;
        cap = source.cap;
        count = source.count;
        size = source.size;
        isSorted = source.isSorted;
        if(source.list){
            list = new int[source.size];
            for(i=0;i<count;++i){ list[i] = source.list[i]; }
        }else{
            list = nullptr;
        }  
        return *this; 
    }

    Alist operator+=(int &n){
        // this->insert(n);
        // return this;

        if(count == size) extend(); 

        if(isSorted == false){
            list[count] = n;
        }else{
            int i, insertIndex;
            for(i=0;i<count;i++){
                if(n <= list[i]){
                    insertIndex = i;
                    break;
                }
                if(i==count-1) insertIndex = i+1;
            }
            i=count;
            while(i>insertIndex){
                list[i] = list[i-1];
                i--;
            }
            list[insertIndex] = n;
        }
        count++;
        return this;
    }

    int operator[](int index){ return this->list[index]; }

    bool operator<(Alist right){
        if(this->get_count() < right.get_count()){ return true; }
        else{ return false; }
    }

    bool operator>(Alist right){
        if(this->get_count() > right.get_count()){ return true; }
        else{ return false; }
    }



    //move consttuctor
    //copy assignment 
    //move assignment
    //remove
    //save
    //search
};




    



int main(){
    Alist l1;
    int i,j,k;
    
    for(i=0;i<14;i++){
        l1.insert(i);
    }

    // Alist l2 = new Alist(l1);
    // Alist l2=l1;
    // l2.getData();

    // l1.sortList();
    // int x = 9;
    // l1 += x;

    // l1.getData();

    Alist a1;
    const int nums_count = 100;
    int n = 4;

    for(int i=0;i<nums_count;i++){
      n = rand() % 1000;
      a1 += n;
    }

    a1.getData();
    

    return 0;
}