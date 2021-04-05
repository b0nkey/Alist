#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#define DEFAULTCAP 8
using namespace std;

class Alist{
 private:
    int initialCap; // capacity incrementor / decrementor
    int count; // member count in list
    int size; // current capacity of list[]
    bool isSorted; // sorted flag
    int *list = nullptr; // pointer to start of list

 public:
    // ~~~~~ Constructors ~~~~
    Alist(); // Default Constructor
    Alist(bool b); // Sort State Constructor
    Alist(int newCap, bool b); // Cap + Sort State Constructor
    Alist(const char loadFile[]); // Load Constructor
    Alist(Alist const &original); // Copy Constructor
    Alist(Alist&& temp); // Move Constructor
    Alist(vector <int> v); // Vector Constructor
    ~Alist(); // Destructor
    // ~~~~~~~~~~~~~~~~~~~~~~~


    // ~~ Setters / Getters ~~
    void set_initial_cap(int capSet);
    void set_size(int sizeSet);
    void set_count(int countSet);
    void set_sort_state(bool state);

    int get_size() const;
    int get_count() const;
    int get_initial_cap() const;
    bool get_sort_state()const;
    // ~~~~~~~~~~~~~~~~~~~~~~~


    // ~~~~~~~ Methods ~~~~~~~
    void extend();
    void insert(int num);
    void sort();
    void unsort();
    void load(const char *fileName, Alist &r);
    void resize(int x);
    void shrink();
    bool remove(int item);
    // int randNum();
    int binarySearch(int arr[], int left, int right, int num);
    int search(int item);
    int save(string fileName);
    // ~~~~~~~~~~~~~~~~~~~~~~~


    // ~~~~~~ Overloads ~~~~~~
    Alist& operator=(const Alist &source); // Copy Assignment
    // Alist& operator=(Alist &&right) noexcept; // Move Assignment
    Alist& operator+=(int n); 
    Alist& operator-=(int n);
    Alist operator&&(const Alist &right);
    Alist operator^(const Alist &right);
    const Alist operator+(const Alist &right) const;
    const Alist operator-(const Alist &right) const;
    int &operator[](int index);
    bool operator!=(const Alist &right);
    bool operator==(const Alist &right);
    friend std::ostream& operator<<(std::ostream &out, const Alist &right);
    // ~~~~~~~~~~~~~~~~~~~~~~~
};




// ~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~ Constructors ~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~

Alist::Alist(){ // Default Constructor
    set_initial_cap(DEFAULTCAP);
    set_size(initialCap);
    set_count(0);
    set_sort_state(false);
    list = new int [initialCap];
}

Alist::Alist(bool b){ // Sort State Constructor
    set_initial_cap(DEFAULTCAP);
    set_size(initialCap);
    set_count(0);
    set_sort_state(b);
    list = new int [initialCap];
}

Alist::Alist(int newCap, bool b){ // Sort Status + Cap Override Constructor
    set_initial_cap(newCap);
    set_size(initialCap);
    set_count(0);
    set_sort_state(b);
    list = new int [initialCap];
}

Alist::Alist(const char loadFile[]){ // Load Constructor
    set_initial_cap(DEFAULTCAP);
    set_size(initialCap);
    set_count(0);
    set_sort_state(true);
    list = new int [initialCap];
    load(loadFile, *this);
}

Alist::Alist(Alist const &original){ // Copy Constructor
    int i;
    set_size(original.size);
    set_count(original.count);
    set_initial_cap(original.initialCap);
    set_sort_state(original.isSorted);

    list = new int [initialCap]; 
    for(i=0;i<count;i++){ list[i] = original.list[i]; }
}

Alist::Alist(Alist&& temp){ // Move Constructor
    *this = temp;
    temp = nullptr;
}

Alist::Alist(vector <int> v){ // Vector Constructor
    int i;
    set_initial_cap(v.size());
    set_size(v.size());
    set_count(0);
    set_sort_state(false);

    list = new int[initialCap];
    for(int i : v){
        insert(i);
    }
}

Alist::~Alist(){ // Destructor
    delete[] list;
}



// ~~~~~~~~~~~~~~~~~~~~~~~
// ~~ Setters / Getters ~~
// ~~~~~~~~~~~~~~~~~~~~~~~

void Alist::set_initial_cap(int capSet){ this->initialCap = capSet; }
void Alist::set_size(int sizeSet){ this->size = sizeSet; }
void Alist::set_count(int countSet){ this->count = countSet; }
void Alist::set_sort_state(bool state){ this->isSorted = state; }

int Alist::get_size() const{ return this->size;}
int Alist::get_count() const{ return this->count; }
int Alist::get_initial_cap() const{return this->initialCap; }
bool Alist::get_sort_state() const{ return this->isSorted; }



// ~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~ Methods ~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~


void Alist::extend(){ // extends capacity by cap
    int i;
    int hold [size+initialCap]; // Temp hold array

    for(i=0;i<size;i++)  hold[i] = list[i];
    size = size + initialCap;
    resize(size);
    for(i=0;i<count;i++)  list[i] = hold[i];
    // Transfer to temp array, resize, then transfer back
}

void Alist::shrink(){
    size -= initialCap; // Resize <size>
    int hold[size], i;
    for(i=0;i<size;i++)  hold[i] = list[i]; // Move list data to temp array
    resize(size); // Resize this->list
    for(i=0;i<size;i++)  list[i] = hold[i]; // Repopulate this->list with temp array
}

void Alist::insert(int num){
    if(count == size) extend(); // Extend if full

    if(isSorted == false)  list[count] = num; // Insert at end of list
    else if(isSorted == true){
        int i, insertIndex=0;
        for(i=0;i<count;i++){
            if(num <= list[i]){ // Find where to put in sorted array
                insertIndex = i;
                break;
            }
            if(i==count-1)  insertIndex = count; // Last index
        }
        i=count;
        while(i>insertIndex){ // Shuffle every value above new index back one
            list[i] = list[i-1];
            i--;
        }
        list[insertIndex] = num;
    }
    count++;
}

bool Alist::remove(int item){
    int index = search(item);
    if(index == -1)  return false; // Check if item is in list
     
    if(!isSorted){
        list[index] = list[count-1]; // Move last item in array to removed member
        count--;
        if(count+initialCap == size)  shrink(); // Shrink if able
        return true;
    }

    if(isSorted){
        for(int i=index;i<count-1;i++)  list[i] = list[i+1];
        // Move all members back one index to replace removed member

        count--;
        if(count+initialCap == size)  shrink(); // Shrink if able
        return true;
    }
    return false;
}

void Alist::sort(){
    std::sort(list, list+count);
    isSorted = true;
}

void Alist::unsort(){
    // swap each element with another random
    int r, temp, i;
    for(i=0;i<count;i++){
        r = rand() % count; // Random number between 0 and count
        temp = list[i]; // Temp hold
        
        list[i] = list[r]; // Assign i to a random member
        list[r] = temp;
    }
    isSorted = false;
}

int Alist::binarySearch(int arr[], int left, int right, int num){
    // Works by checking the value in the middle of the array, then comparing
    // it with the searched value.

    // If the value matches, that index is returned.

    // If the middle index value is less than the searched item, remove the right
    // half of the array and re-run the search on the remaining array.

    // If the middle index value is more than the searched item, remove the left
    // half of the array and re-run the search on the remaining array.

    // There are a few ways to write this function. This version is recursive.

    if (left <= right) {
        int mid = (left + right)/2; // Find mid
        if(arr[mid] == num) return mid; // Return mid if num is found
        if(arr[mid] > num) return binarySearch(arr, left, mid-1, num); 
        if(arr[mid] < num) return binarySearch(arr, mid+1, right, num);
    }
    return -1;
}

int Alist::search(int item){
    // Binary search if list is sorted, check every index if unsorted.
    int i;
    if(isSorted == true)  return binarySearch(list, 0, count, item);
    else
        for(i=0;i<count;i++)
            if(list[i] == item) return i;  
    return -1;
}

int Alist::save(string fileName){
    ofstream f;
    int i;

    f.open(fileName); // Open file
    f << initialCap << ' ' << count << ' '
    << size << ' ' << isSorted << ' ';
    // Write object data to file

    for(i=0;i<count;i++)  f << list[i] << ' '; // Write list data to file
    f.close(); // close file
    return true;
}

void Alist::load(const char *fileName, Alist &r){
    ifstream f(fileName);
    int x, i;

    // Move forward through the file and set the object data

    f >> x;
    r.initialCap = x;

    f >> x;
    r.count = x;

    f >> x;
    r.size = x;

    f >> x;
    r.isSorted = x;

    r.list = new int [r.size];

    for(i=0;i<r.count;i++){ // Read list data and assign to object list
        f >> x;
        r.list[i] = x;
    }
    f.close(); // Close file
}

void Alist::resize(int x){
    int hold[x]; // Temporary hold array

    for(int i=0;i<x;i++)  hold[i] = list[i]; // Copy list data to temp hold
    this->list = new int[x];   // Redefine list with new size

    for(int i=0;i<x;i++)  list[i] = hold[i]; // Copy data back to new array

    set_size(x); // Set new list size
    if(count > x)  count = x; // Ensure amount of values does not exceed array size
}


// ~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~ Overloads ~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~


Alist& Alist::operator=(const Alist &source){
    int i;
    set_initial_cap(source.get_initial_cap());
    set_size(source.get_initial_cap());
    set_count(0);
    set_sort_state(source.get_sort_state());
    list = new int [initialCap];
    
    for(i=0;i<source.count;i++)  insert(source.list[i]);
    return *this;
}

Alist& Alist::operator+=(int n){
    insert(n);
    return *this;
}

int& Alist::operator[](int index){
    if(index<0 || index>=count) // Bounds check
        cout << "Invalid Index " << index << endl;
    return this->list[index]; 
}

bool Alist::operator!=(const Alist &right){
    int i;
    if(get_initial_cap() == right.get_initial_cap()) return false;
    if(get_count() == right.get_initial_cap()) return false;
    if(get_size() == right.get_size()) return false;
    if(get_sort_state() == right.get_sort_state()) return false;

    for(i=0;i<get_count();i++)  if(list[i] == right.list[i]) return false;

    return true;
}

bool Alist::operator==(const Alist &right){
    int i;
    if(initialCap != right.initialCap)  return false;
    if(count != right.initialCap)  return false;
    if(size != right.size)  return false;
    if(isSorted != right.isSorted)  return false;

    for(i=0;i<count;i++)
        if(list[i] != right.list[i])  return false;
    return true;
}

Alist& Alist::operator-=(int n){
    remove(n);
    return *this;
}

const Alist Alist::operator+(const Alist &right) const{
    int i;
    Alist returnObj(*this); // Copy this into a return obj. Don't want to modify <this>

    for(i=0;i<right.count;i++)  returnObj.insert(right.list[i]); // Copy data
    return returnObj;
}

const Alist Alist::operator-(const Alist &right) const{
    int i;
    Alist returnObj(*this); // Copy this into a return obj. Don't want to modify <this>

    for(i=0;i<right.count;i++)  returnObj.remove(right.list[i]);
    return returnObj;
}

Alist Alist::operator&&(const Alist &right){
    Alist returnObj(initialCap, isSorted);
    int i;

    // Nested loops for each array. A single loop would only work if both lists were
    // the same length, and stored values in a static location in the list.
    for(i=0;i<count;i++)
        for(int j=0;j<right.count;j++)
            if(list[i] == right.list[j]) returnObj.insert(list[i]);
    return returnObj;
}

Alist Alist::operator^(const Alist &right){
    Alist returnObj(initialCap, isSorted);
    bool flag=false;
    int i, j;

    // Nested loops, same reason as && overload
    // Uses a flag to decide if an item is inserted.
    for(i=0;i<count;i++){
        for(j=0;j<right.count;j++){
            if(list[i] == right.list[j]){
                flag=false;
                break;
            }
            flag=true;
        }
        if(flag==true)  returnObj.insert(list[i]);
    }

    for(i=0;i<right.count;i++){
        for(j=0;j<count;j++){
            if(right.list[i] == list[j]){
                flag=false;
                break;
            }
            flag=true;
        }
        if(flag==true)  returnObj.insert(right.list[i]);
    }
    return returnObj;
}

std::ostream& operator<< (std::ostream &out, const Alist &right){
    int i;
    // Stores list data in out object and returns it
    for(i=0;i<right.count;i++)  out << right.list[i] << ' ';
    return out;
};

























int main(){ 
    // Test basic constructors and += overloading
    Alist a1, a2(true), a3(72, false), a4, a6, a7, a8;
    const int nums_count = 100;
    int n;
    for (int i = 0; i < nums_count; i++) {
        n = rand() % 1000;
        a1 += n;
        a2 += n;
        a3 += n;
    }
    cout << "Sizes: " << a1.get_size() << " " << a2.get_size() << " " << a3.get_size() << endl;
    cout << "Counts: " << a1.get_count() << " " << a2.get_count() << " " << a3.get_count() << endl;

    // Test sorting
    bool sorted = true;
    for (int i = 1; i < a2.get_count() && sorted; i++)
        if (a2[i - 1] > a2[i])
            sorted = false;
    if (!sorted)
        cout << "a2 not initialised to sorted" << endl;
    a1.sort();
    for (int i = 1; i < nums_count; i++)
        if (a1[i - 1] > a1[i]) {
            cout << "a1 not sorted" << endl;
            break;
        }
    a2.unsort();
    sorted = true;
    for (int i = 1; i < a2.get_count() && sorted; i++)
        if (a2[i - 1] > a2[i])
            sorted = false;
    if (sorted)
        cout << "Unsorted failed" << endl;

    // Test explicit methods and -= overloading
    n = a1[20];
    cout << "Double remove: " << a1.remove(n) << " " << a1.remove(n) << endl;
    cout << "Search present, not present: " << a1.search(a1[50]) << " " << a1.search(n) << endl;
    a1 += n;
    cout << "Search (should be 20 57): " << a1.search(n) << " " << a2.search(n) << endl;
    a1.extend();
    cout << "Extend (should be 112): " << a1.get_size() << endl;
    a1.shrink();
    cout << "Shrink (should be 104): " << a1.get_size() << endl;
    n = a1.get_size();
    for (int i = 0; i < n - 6; i++)
        a1 -= a1[0];
    cout << "Remove (should be 8): " << a1.get_size() << endl;
    a3.save("nums.txt");
    Alist a5("nums.txt");
    if (a3 != a5)
        cout << "save / reload failed" << endl;

    // Test copy constructors and resize
    a4 = a3;
    if (a4 != a3)
        cout << "Copy Constructor 1 Fail" << endl;
    a4.remove(a4[50]);
    if (a4 == a3)
        cout << "Copy Constructor 2 Fail" << endl;
    a4.resize(50);
    cout << "Resize (should be 50 50): " << a4.get_size() << " " << a4.get_count() << endl;

    // Test other operator overloading
    n = a1[-20];
    n = a1[2 * nums_count];
    for (int i = 0; i < 20; i += 2)
        a6 += i;
    for (int i = 1; i < 20; i += 2)
        a7 += i;
    a5 = a6 + a7;
    a5.sort();
    for (int i = 0; i < 20; i++)
        if (a5[i] != i)
            cout << "+ operator failed" << endl;
    a8 = a6 && a7;
    if (a8.get_count() != 0)
        cout << "&& operator failed 1" << endl;
    a8 = a6 && a6;
    if (a8.get_count() != a6.get_count())
        cout << "&& operator failed 2" << endl;
    a8 = a6 ^ a7;
    if (a8.get_count() != 20)
        cout << "^ operator failed 1" << endl;
    a8 = a6 ^ a6;
    
    if (a8.get_count() != 0)
        cout << "^ operator failed 2" << endl;

    a8 = a5 - a7;
    a8.sort();


    for (int i = 0; i < 20; i += 2)
        if (a5[i / 2] != i / 2)
            cout << "- operator failed" << endl;
    a7 += 28;
    if (a7.search(28) == -1)
        cout << "+= operator failed" << endl;
    a7 -= 19;
    if (a7.search(19) != -1)
        cout << "-= operator failed" << endl;

    // Test other constructors  
    Alist a9(a8);
    a9.remove(8);
    if (a9.get_count() != a8.get_count() - 1)
        cout << "Constructor 1 Fail" << endl;

    cout << a8 << endl;
    cout << a9 << endl;
    vector < int > vn {
        0,
        1,
        2,
        3,
        4
    };
    Alist a10(vn);
    for (int i = 0; i < vn.capacity(); i++)
        if (a10[i] != vn[i])
            cout << "Constructor 2 Fail" << endl;
    return 0;
}

/*

I left my move assignment until last and couldnt get it to work in time.
Even though it doesnt work, ill dump it here in case the logic is worth
a half mark.

It would have made my insert & remove a bit more efficient by giving the list
pointer a new owner istead of doing two lots of data transfer.

*/


// Alist& operator=(Alist &&right) noexcept;

// Alist& Alist::operator=(Alist &&right) noexcept{ // Move Assignment
//    if(this != &right){
//        delete[] this->list;
//        this->list = right.list;
//        right.list = nullptr;
//     }

//     return *this;
// }