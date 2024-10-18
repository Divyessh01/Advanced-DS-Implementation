#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V>
struct Node
{

    K key;
    V val;
    Node *left;
    Node *right;
    int bf;
    int height;
    int total;

    Node(K k, V v)
    {
        key = k;
        val = v;
        left = nullptr;
        right = nullptr;
        height = -1;
        bf = 0;
        total = 1;
    }
};

template <typename K, typename V>
class OrderedMap
{
private:
    Node<K, V> *root;
    int siz;
    vector<K> allkeys;

    int getHeight(Node<K, V> *root)
    {
        if (root == NULL)
            return -1;
        else
            return root->height;
    }

    int setHeight(Node<K, V> *root)
    {
        if (root == NULL)
            return -1;
        else
            return (1 + max(getHeight(root->left), getHeight(root->right)));
    }

    int getCount(Node<K, V> *root)
    {
        if (root == NULL)
            return 0;
        else
            return root->total;
    }

    int setCount(Node<K, V> *root)
    {
        if (root == NULL)
            return 0;
        else
            return (1 + getCount(root->left) + getCount(root->right));
    }

    int setBF(Node<K, V> *root)
    {
        return (getHeight(root->left) - getHeight(root->right));
    }

    // search for key in AVL, iffound => return that node, else => return null
    Node<K, V> *
    search(Node<K, V> *root, K key)
    {
        if (root == NULL || root->key == key)
            return root;

        if (key < root->key)
            return search(root->left, key);
        else
            return search(root->right, key);
    }

public:
    OrderedMap()
    {
        allkeys.clear();
        siz = 0;
        root = NULL;
    }

    void display(Node<K, V> *root)
    {
        if (root != NULL)
        {
            display(root->left);
            printf("\nKey: %d  Val: %d  height : %d  Bf : %d count: %d", root->key, root->val, root->height, root->bf, root->total);
            display(root->right);
        }
    }

    Node<K, V> *insert_rec(Node<K, V> *root, K key, V val)
    {
        if (root == NULL)
        {
            Node<K, V> *temp = new Node<K, V>(key, val);
            temp->height = setHeight(temp);
            temp->total = setCount(temp);
            temp->bf = setBF(temp);
            return temp;
        }
        else
        {
            if (key < root->key)
                root->left = insert_rec(root->left, key, val);
            else
                root->right = insert_rec(root->right, key, val);

            root->height = setHeight(root);
            root->bf = setBF(root);
            root->total = setCount(root);
            // balancetree(root);
            return root; // update later
        }
    }

    bool
    insert(K key, V val)
    {
        if (search(root, key) != NULL)
            return false;

        root = insert_rec(root, key, val);
        siz++;
        display(root);
        return true;
    }

    bool contains(K key){
        if (search(root, key) != NULL)
            return true;
        return false;
    }

    bool empty(){
        if(siz == 0)
            return true;
        
        return false;
    }

    int size(){
        return siz;
    }
};

int main()
{
    int key;
    int val;
    OrderedMap<int, int> myMap;

    int operation = -1;

    while (operation)
    {
        cin >> operation;

        switch (operation)
        {
        case 1:
            cout << boolalpha << myMap.empty() << endl;
            break;
        case 2:
            cout << myMap.size() << endl;
            break;
        case 3:
            cin >> key;
            cout << boolalpha << myMap.contains(key) << endl;
            break;
        case 4:
            cin >> key >> val;
            cout << boolalpha << myMap.insert(key, val) << endl;
            break;
        case 5:
            /* code */
            break;
        case 6:
            /* code */
            break;
        case 7:
            /* code */
            break;
        case 8:
            /* code */
            break;
        case 9:
            /* code */
            break;
        case 10:
            /* code */
            break;
        default:
            break;
        }
    }

    return 0;
}