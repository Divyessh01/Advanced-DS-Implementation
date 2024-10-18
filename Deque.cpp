#include <iostream>
#include <string>
using namespace std;
#define init 1000

template <typename T> class Deque {
private:
    T* arr;
    int cap;
    int siz;
    int fron;
    int bac;

    // double the capacity of dq
    void expand(){
        cap = 1;
        if(siz != 0)   cap = siz * 2;

        T* temp = new T[cap];

        int loop = siz;
        int index = 0;
        int i = fron + 1;
        if(fron+1 >= siz)   i = 0;
        while(loop--){    
            temp[index] = arr[i];

            index++;
            if(i == siz - 1)   i = 0;
            else i++;
        }

        delete[] arr;
        arr = new T[cap];
        arr = temp ;

        fron = -1;
        bac = siz - 1;
    }


public:
    Deque(){
        arr = new T[1];
        cap = 1;
        siz = 0;
        fron = -1;
        bac = -1;
    }

    Deque(int n){
        
        cap = n;

        arr = new T[cap];
        fron = -1;
        bac = n - 1;

        siz = 0;
        while(siz <= bac){
            arr[siz++] = T{};
        }
    }

    Deque(int n, T x){

        cap = n;
        arr = new T[cap];
        fron = -1;
        bac = n - 1;

        siz = 0;
        while(siz <= bac)
            arr[siz++] = x;
    }

    bool push_back(T x);
    bool pop_back();
    bool push_front(T x);
    bool pop_front();
    T front();
    T back();
    T operator[](int n); //overload [] & show nth element
    void resize(int n);
    void resize(int n, T d);
    void reserve(int n);
    void shrink_to_fit();

    bool empty(){
        if(siz == 0)   return true;
        return false;
    }

    void clear(){
        fron = -1;
        bac = -1;
        siz = 0;
    }

    int size(){
        return siz;
    }

    int capacity(){
        return cap;
    }
    void prnt();
};


template <typename T>bool Deque<T>::push_back(T x){
    
    if(siz == cap)
        expand();

    if(bac == (cap-1)) bac = 0;
    else bac++;
    
    arr[bac] = x;
    siz++;
        
    return true;

    //edge case return false if datatype mismatch!
    //ie datatype(arr) != datatype(x)
}

template <typename T> bool Deque<T>::pop_back(){
    if(empty()) return false;

    if(bac == 0)   bac = cap - 1;
    else bac--;
    siz--;
    return true;
}

template <typename T> bool Deque<T>::push_front(T x){

    if(siz == cap)
        expand();

    if(fron == -1)
        fron = cap - 1;
        
    arr[fron--] = x;
    siz++;

    return true;
    //same edge case as in push_back()
}

template <typename T> bool Deque<T>::pop_front(){
    if(empty()) return false;

    if(fron == (cap - 1))  fron = 0;
    else fron++;

    siz--;
    return true;
}

template <typename T> T Deque<T>::front(){
    if(empty()) return T{};

    if(fron == (cap - 1))  return arr[0];
    else    return arr[fron + 1];
}

template <typename T> T Deque<T>::back(){
    if(empty())   return T{};

    return arr[bac];
}

template <typename T> T Deque<T>::operator[](int n){
    if((n>=0 && n>=siz) || (n<0 && (-n)>siz)) return T{};

    if(n >= 0){
        return arr[(fron + n + 1)%cap];
    }

    return arr[(bac + n + 1 + cap)%cap];
}

template <typename T> void Deque<T>::resize(int n){
    if(n > siz){
        while(siz < n){
            push_back(T{});
        }
    } else{
        while(n < siz){
            pop_back();
        }
    }
}

template <typename T> void Deque<T>::resize(int n, T d){
    if(n > siz){
        while(siz < n){
            push_back(d);
        }
    } else{
        while(n < siz){
            pop_back();
        }
    }
}

template <typename T> void Deque<T>::reserve(int n){
    if(n > cap){

        T* temp = new T[n];

        int loop = siz;
        int index = 0;
        int i = fron + 1;
        if(fron+1 >= cap) i = 0;

        while(loop--){
            temp[index] = arr[i];
            index++;
            if(i == cap - 1)   i = 0;
            else i++;
        }

        delete[] arr;
        arr = new T[n];
        arr = temp;

        cap = n;
        fron = -1;
        bac = siz - 1;
    }
}

template <typename T> void Deque<T>::shrink_to_fit(){
    
    if(siz != cap){

        T* temp = new T[siz];

        int loop = siz;
        int index = 0;
        int i = fron + 1;
        if(fron+1 >= cap) i = 0;
        while(loop--){
            temp[index] = arr[i];
            index++;
            if(i == cap - 1)   i = 0;
            else i++;
        }

        delete[] arr;
        arr = new T[siz];
        arr = temp;

        cap = siz;
        fron = -1;
        bac = siz - 1;
    }
}

int main(){

    Deque<string> dq;
    string s;

    int choice = -1;
    while (choice != 0) {
        cin >> choice;
        if(choice == 0){
            break;
        }
        else if (choice == 1) {
            dq = Deque<string>();
        }
        else if (choice == 2) {
            int n;
            cin >> n;
            dq = Deque<string>(n);
        }
        else if (choice == 3) {
            int n;
            cin >> n;
            cin >> s;
            dq = Deque<string>(n, s);
        }
        else if (choice == 4) {
            cin >> s;
            cout << boolalpha << dq.push_back(s) << endl;
        }
        else if (choice == 5) {
            cout << boolalpha << dq.pop_back() << endl;
        }
        else if (choice == 6) {
            cin >> s;
            cout << boolalpha << dq.push_front(s) << endl;
        }
        else if (choice == 7) {
            cout << boolalpha << dq.pop_front() << endl;
        }
        else if (choice == 8) {
            s = dq.front();
            cout << s << endl;
        }
        else if (choice == 9) {
            s = dq.back();
            cout << s << endl;
        }
        else if (choice == 10) {
            int n;
            cin >> n;
            cout << dq[n] << endl;
        }
        else if (choice == 11) {
            cout << boolalpha << dq.empty() << endl;
        }
        else if (choice == 12) {
            cout << dq.size() << endl;
        }
        else if (choice == 13) {
            int n;
            cin >> n;
            dq.resize(n);
        }
        else if (choice == 14) {
            int n;
            cin >> n >> s;
            dq.resize(n, s);
        }
        else if (choice == 15) {
            int n;
            cin >> n;
            dq.reserve(n);
        }
        else if (choice == 16) {
            dq.shrink_to_fit();
        }
        else if (choice == 17) {
            dq.clear();
        }
        else if (choice == 18) {
            cout << dq.capacity() << endl;
        }
        else {
            cout << "Enter a valid operation: [0-18]" << endl; 
        }
    }

    return 0;
}