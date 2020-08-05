

// holds int items

class Alist{
 private:
  int length=8;
  int *list;
  list = new int [length];

 public:
  Alist(){} // default
  Alist(Stack &other); // second
  Alist operator+(Stack const &other); // overload +

};

// main function to test Alist class
int main(){// Test basic constructors and += overloading
  Alist a1, a2(true), a3(72, false), a4, a6, a7, a8;
  const int nums_count = 100;
  int n;

  for(int i=0;i<nums_count;i++){
      n = rand() % 1000;
      a1 += n;
      a2 += n;
      a3 += n;
  }

  cout << "Sizes: " << a1.get_size() << " " << a2.get_size() << " " << a3.get_size() << endl;  
  cout << "Counts: " << a1.get_count() << " " << a2.get_count() << " " << a3.get_count() << endl;  

  // Test sorting
  bool sorted = true;

  for(int i = 1; i < a2.get_count() && sorted; i++){
      if (a2[i - 1] > a2[i]){
          sorted = false;
      }
  }
          
  if(!sorted){
      cout << "a2 not initialised to sorted" << endl; 
  }
              
  a1.sort();
  
  for (int i = 1; i < nums_count; i++){
      if (a1[i - 1] > a1[i]){
          cout << "a1 not sorted" << endl;
          break;
      } 
  }
      
  a2.unsort();
  sorted = true;
  for (int i = 1; i < a2.get_count() && sorted; i++){
      if (a2[i - 1] > a2[i])
      sorted = false;
  }
  
  if (sorted){
      cout << "Unsorted failed" << endl;   
  }


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

  for (int i = 0; i < n - 6; i++){
      a1 -= a1[0];
  }
  
  cout << "Remove (should be 8): " << a1.get_size() << endl;  
  a3.save("nums.txt");
  Alist a5("nums.txt");

  if (a3 != a5){
      cout << "save / reload failed" << endl;
  }
  

  // Test copy constructors and resize
  a4 = a3;
  if (a4 != a3){
      cout << "Copy Constructor 1 Fail" << endl;
  }
  
  a4.remove(a4[50]);
  if (a4 == a3){
    cout << "Copy Constructor 2 Fail" << endl; 
  }
   
  a4.resize(50);
  cout << "Resize (should be 50 50): " << a4.get_size() << " " << a4.get_count() << endl;  

  // Test other operator overloading
  n = a1[-20];    
  n = a1[2 * nums_count];    
  for (int i = 0; i < 20; i += 2) a6 += i;
  for (int i = 1; i < 20; i += 2) a7 += i;
  a5 = a6 + a7;
  a5.sort();
  for (int i = 0; i < 20; i++){
    if (a5[i] != i){
      cout << "+ operator failed" << endl;
    }
  }
    
  a8 = a6 && a7;
  if (a8.get_count() != 0){
    cout << "&& operator failed 1" << endl;
  }
    
  a8 = a6 && a6;
  if (a8.get_count() != a6.get_count()){
    cout << "&& operator failed 2" << endl;
  }
    
  a8 = a6 ^ a7;
  if (a8.get_count() != 20){
    cout << "^ operator failed 1" << endl;
  }
   
  a8 = a6 ^ a6;
  if (a8.get_count() != 0){
    cout << "^ operator failed 2" << endl;
  }

  a8 = a5 - a7;
  a8.sort();
  for (int i = 0; i < 20; i += 2){
    if (a5[i / 2] != i / 2){
     cout << "- operator failed" << endl;
   }
  }
   
     
  a7 += 28;
  if (a7.search(28) == -1){
    cout << "+= operator failed" << endl;
  }

  a7 -= 19;
  if (a7.search(19) != -1){
    cout << "-= operator failed" << endl;
  }
   

  // Test other constructors  
  Alist a9(a8);
  a9.remove(8);
  if (a9.get_count() != a8.get_count() - 1){
    cout << "Constructor 1 Fail" << endl;
  }
   
  cout << a8 << endl;
  cout << a9 << endl;
  vector<int> vn{0, 1, 2, 3, 4};
  Alist a10(vn);
  for (int i = 0; i < vn.size(); i++){
    if (a10[i] != vn[i]){
     cout << "Constructor 2 Fail" << endl;
   }
  }
   
     
 return 0; 
}