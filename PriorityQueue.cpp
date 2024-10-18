#include <iostream>
using namespace std;

class priority_queue {
private:
    int* heap;
    int cap;
    int siz;

    bool high_num;

    void expand(){
        cap = 1;
        if(siz != 0)   cap = siz * 2;

        int* temp = new int[cap];

        for(int i = 0; i < siz; i++){
            temp[i] = heap[i];
        }

        delete[] heap;
        heap = new int[cap];
        heap = temp ;
    }

    void print(){
        cout << "=======================" << endl;
        for(int i = 0; i < siz; i++){
            cout << "i: " << i << " | " << "val: " << heap[i] << endl;
        }
        cout << "=======================" << endl;
    }

    void swim(){
        int last = siz - 1;
        while(last > 0){
            int parent = (last - 1) / 2;
            if(!high_num){
                if(heap[last] < heap[parent]){
                    swap(heap[last], heap[parent]);
                    last = parent;
                } else{
                    break;
                }
            } else{
                if(heap[last] > heap[parent]){
                    swap(heap[last], heap[parent]);
                    last = parent;
                } else{
                    break;
                }
            }
        }
    }

    void sink(){
        int index = 0;
        int left = index * 2 + 1;
        int right = index * 2 + 2;

        while(left < siz){
            int temp = index;

            if(right < siz and left < siz){
                if(!high_num){
                    if(heap[left] <= heap[right]){
                        if(heap[index] > heap[left]){
                            swap(heap[index], heap[left]);
                            index = left;
                        }
                    } else{
                        if(heap[index] > heap[right]){
                            swap(heap[index], heap[right]);
                            index = right;
                        }
                    }
                } else{
                    if(heap[left] >= heap[right]){
                        if(heap[index] < heap[left]){
                            swap(heap[index], heap[left]);
                            index = left;
                        }
                    } else{
                        if(heap[index] < heap[right]){
                            swap(heap[index], heap[right]);
                            index = right;
                        }
                    }
                }
            } else if(left < siz){
                if(!high_num){
                    if(heap[index] > heap[left]){
                        swap(heap[index], heap[left]);
                        index = left;
                    }
                } else{
                    if(heap[index] < heap[left]){
                        swap(heap[index], heap[left]);
                        index = left;
                    }
                }
            }

            if(temp == index){
                break;
            }
            left = index * 2 + 1;
            right = index * 2 + 2;
        }
    }

public:

    priority_queue(){
        heap = new int[10];
        cap = 10;
        siz = 0;
        high_num = false;
    }

    priority_queue(bool flag){
        high_num = flag;
        heap = new int[10];
        cap = 10;
        siz = 0;
    }

    int size(){
        return siz;
    }

    void push(int val){
        if(siz == cap){
            expand();
        }
        heap[siz] = val;
        siz++;
        swim();
        // print();
    }

    int top(){
        if(siz == 0){
            exit(1);
        }
        return heap[0];
    }

    void pop(){
        if (siz == 0)
            return;

        heap[0] = heap[siz-1];
        siz--;
        sink();
        // print();
    }

    bool empty(){
        if(siz) return false;
        return true;
    }
};

int main(){

    bool high_num_priority = false; // set true for min-heap | high-num = high-priority
    int choice = -1;
    priority_queue pq;

    while(choice != 0){
        cin >> choice;

        switch (choice)
        {
        case 0:
            break;
        case 1:
            // default: max-heap | low-num = high-priority
            pq = priority_queue(high_num_priority);
            break;
        case 2:
            cout << pq.size() << endl;
            break;
        case 3:
            int el;
            cin >> el;
            pq.push(el);
            break;
        case 4:
            cout << pq.top() << endl;
            break;
        case 5:
            pq.pop();
            break;
        case 6:
            cout << boolalpha << pq.empty() << endl;
            break;
        default:
            break;
        }
    }

    return 0;
}