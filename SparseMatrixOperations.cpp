#include <iostream>
#include <iomanip>
using namespace std;

template <typename T> struct Array {
    int row;
    int col;
    T val;
};

template <typename T>
void expand(Array<T>* (&mat), int& cap, int size){
    cap = 1;
    if(size != 0) cap = size * 2;

    Array<T>* temp = new Array<T>[cap];

    for(int i = 0; i < size; i++){
        temp[i].row = mat[i].row;
        temp[i].col = mat[i].col;
        temp[i].val = mat[i].val;
    }

    delete[] mat;
    mat = new Array<T>[cap];
    mat = temp ;
}

// take array input
template <typename T>
int array_input(int n, int m, Array<T>* (&mat), int& cap){
    T val;
    int point = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> val;
            if(val == 0){
                continue;
            }

            if(point == cap){
                expand(mat, cap, point);
            }

            mat[point].row = i;
            mat[point].col = j;
            mat[point].val = val;

            point++;
        }
    }
    return point;
}

// print array
template <typename T>
void print(Array<T>* (&mat), int size){
    cout << "=======================================" << endl;
    for(int i = 0; i < size; i++){
        cout << "row: " << mat[i].row << " | col: " << mat[i]. col << " | val:" << mat[i].val << endl;
    }
    cout << "=======================================" << endl;
}

// array addition
template <typename T>
void array_addition(Array<T>* (&mat1), Array<T>* (&mat2), int n, int m, int size1, int size2){
    int point1 = 0, point2 = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if((point1 < size1 and point2 < size2) and (mat1[point1].row == i and mat1[point1].col == j) and (mat2[point2].row == i and mat2[point2].col == j)){
                cout << /* setw(5) << right <<*/ mat1[point1++].val + mat2[point2++].val << " ";
            } else if(point1 < size1 and mat1[point1].row == i and mat1[point1].col == j){
                cout << /* setw(5) << right <<*/ mat1[point1++].val << " ";
            } else if(point2 < size2 and mat2[point1].row == i and mat2[point1].col == j){
                cout << /* setw(5) << right <<*/ mat2[point2++].val << " ";
            } else{
                cout << /* setw(5) << right <<*/ 0 << " ";
            }
        }
        cout << endl;
    }
}

// sort by col for transpose
template <typename T>
void sortbycol(Array<T>* (&mat), int size){
    bool flag = true;
    for(int i = 0; i < size - 1; i++){
        flag = true;
        for(int j = 0; j < size - i - 1; j++){
            if (mat[j].col > mat[j + 1].col) {
                swap(mat[j].row, mat[j + 1].row);
                swap(mat[j].col, mat[j + 1].col);
                swap(mat[j].val, mat[j + 1].val);
                flag = false;
            }
        }
        if (flag)
            break;
    }
}

// array transpose
template <typename T>
void array_transpose(int n, int m, Array<T>* (&mat), int& cap){
    T val;
    int point = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> val;
            if(val == 0){
                continue;
            }

            if(point == cap){
                expand(mat, cap, point);
            }

            mat[point].row = i;
            mat[point].col = j;
            mat[point].val = val;

            point++;
        }
    }

    sortbycol(mat, point);

    int size = point;
    point = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(point < size and mat[point].col == i and mat[point].row == j){
                cout << /* setw(5) << right <<*/ mat[point++].val << " ";
            } else{
                cout << /* setw(5) << right <<*/ 0 << " ";
            }
        }
        cout << endl;
    }
}

// sorted by row(preserve it) + sort by col
template <typename T>
void multisort(Array<T>* (&res), int size){
    int actualrows = 1;
    for(int i = 1; i < size; i++){
        if(res[i].row == res[i-1].row) continue;
        actualrows++;
    }

    int colsperrow[actualrows];
    for(int i = 0; i < actualrows; i++){
        colsperrow[i] = 1;
    }

    int index = 0;
    for(int i = 1; i < size; i++){
        if(res[i].row == res[i-1].row) colsperrow[index]++;
        else index++;
    }

    index = 0;
    bool flag = true;
    for(int i = 0; i < size - 1; i++){
        if(res[i+1].row == res[i].row){
            for(int j = 0; j < colsperrow[index] - 1; j++){
                flag = true;
                for(int k = 0; k < colsperrow[index] - j - 1; k++){
                    if (res[k].col > res[k + 1].col) {
                        swap(res[k].col, res[k + 1].col);
                        swap(res[k].val, res[k + 1].val);
                        flag = false;
                    }
                }
                if (flag)
                    break;
                index++;
            }
        }
    }
}

// array multiplication
template <typename T>
void array_multiplication(Array<T>* (&res), Array<T>* (&mat1), Array<T>* (&mat2), int n1, int m1, int n2, int m2, int capres, int size1, int size2){
    int point = 0;
    for(int i = 0; i < size1; i++){
        for(int j = 0; j < size2; j++){
            if(mat1[i].col == mat2[j].row){
                bool exist = false;
                for(int k = 0; k < point; k++){
                    if(res[k].row == mat1[i].row and res[k].col == mat2[j].col){
                        res[k].val += mat1[i].val * mat2[j].val;
                        exist = true;
                    }
                }
                if(!exist){
                    if(point == capres){
                        expand(res, capres, point);
                    }
                    res[point].row = mat1[i].row;
                    res[point].col = mat2[j].col;
                    res[point].val = mat1[i].val * mat2[j].val;
                    point++;
                }
            }
        }
    }

    multisort(res, point);

    // cout output
    int size = point;
    point = 0;
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < m2; j++){
            if(point < size and res[point].row == i and res[point].col == j){
                cout << /* setw(5) << right <<*/ res[point++].val << " ";
            } else{
                cout << /* setw(5) << right <<*/ 0 << " ";
            }
        }
        cout << endl;
    }

}


int main(){

    int structure;
    cin >> structure;

    int init = 0;
    int cap1 = init;
    int cap2 = init;
    int size1 = 0, size2 = 0;
    Array<int>* mat1 = new Array<int>[init];
    Array<int>* mat2 = new Array<int>[init];
    Array<int>* res = new Array<int>[init];

    if(structure == 1 or structure == 2){
        int operation;
        cin >> operation;

        int n, m;
        int n2, m2;

        if(operation == 1){
            if(structure == 1){
                cin >> n >> m;
                int size1 = array_input(n, m, mat1, cap1);
                cin >> n >> m;
                int size2 = array_input(n, m, mat2, cap2);
                array_addition(mat1, mat2, n, m, size1, size2);
            } else{
                //ll_input();
                //ll_addition();
            }
        } else if(operation == 2){
            if(structure == 1){
                cin >> n >> m;
                array_transpose(n, m, mat1, cap1);
            } else{
                // Linked List transpose
            }
        } else if(operation == 3){
            if(structure == 1){
                cin >> n >> m;
                int size1 = array_input(n, m, mat1, cap1);
                cin >> n2 >> m2;
                int size2 = array_input(n2, m2, mat2, cap2);
                array_multiplication(res, mat1, mat2, n, m, n2, m2, init, size1, size2);
            } else{
                // Linked List multiplication
            }
        } else{
            cout << "Invalid operation." << endl;
            return 0;
        }
    } else{
        cout << "Invalid structure choice." << endl;
        return 0;
    }

    return 0;
}