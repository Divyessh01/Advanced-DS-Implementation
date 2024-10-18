#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
using namespace std;

void print_vector(vector<int> vec)
{
    for (auto some : vec)
        cout << some << " ";

    cout << endl;
}

template <typename T>
struct Node
{
    T value;
    int priority;
    int size;
    int index;
    Node *left;
    Node *right;

    Node(T val)
    {
        value = val;
        priority = rand() % 100;
        size = 1;
        index = 0;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class Treap
{
public:
    Node<T> *root;

    Treap()
    {
        root = nullptr;
    }

    bool empty()
    {
        if (root)
            return true;

        return false;
    }

    int size()
    {
        if (root)
            return root->size;

        return 0;
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    int insert(T val)
    {
        Node<T> *new_treap = new Node(val);
        pair<Node<T> *, Node<T> *> temp = split(root, val);
        root = merge(merge(temp.first, new_treap), temp.second);
        return indexOf(val);
    }

    bool erase(int index)
    {
        if (index < 0 or index >= size())
            return false;

        Node<T> *node = get_node_by_index(root, index);
        if (node == NULL)
            return false;

        return erase(node);
    }

    int indexOf(T val)
    {
        return indexOf(root, val);
    }

    T atIndex(int index)
    {
        if (index < 0 || index >= size())
            return T{};

        return atIndex(root, index);
    }

    Treap<T> *merge(Treap<T> *t2)
    {
        Node<T> *new_treap = merge(root, t2->root);
        root = nullptr;
        t2->root = nullptr;
        Treap<T> *result = new Treap<T>();
        result->root = new_treap;
        return result;
    }

    pair<Treap<T> *, Treap<T> *> split(int index)
    {
        pair<Node<T> *, Node<T> *> splitPair = split(root, atIndex(index));
        Treap<T> *leftTreap = new Treap<T>();
        Treap<T> *rightTreap = new Treap<T>();
        leftTreap->root = splitPair.first;
        rightTreap->root = splitPair.second;
        return make_pair(leftTreap, rightTreap);
    }

    bool erase(int first, int last)
    {
        // yet to complete
    }

    // Treap<T> *slice(int first, int last)
    // {
    //     if (first < 0 || first >= size() || last < 0 || last >= size() || first > last)
    //         return nullptr;

    //     pair<Node<T> *, Node<T> *> slicePair = split(root, first);
    //     pair<Node<T> *, Node<T> *> secondSplit = split(slicePair.second, last - first + 1);

    //     Treap<T> *resultTreap = new Treap<T>();
    //     resultTreap->root = secondSplit.first;

    //     root = merge(slicePair.first, secondSplit.second);

    //     return resultTreap;
    // }

    int lower_bound(T val)
    {
        return lower_bound(root, val);
    }

    int upper_bound(T val)
    {
        return upper_bound(root, val);
    }

    int count(T val)
    {
        return count(root, val);
    }

    vector<T> to_array()
    {
        vector<T> values;

        int index = 0;
        inorder(root, index, values);

        return values;
    }

    // extra
    void display()
    {
        int index = 0;
        cout << "============================================" << endl;
        display_inorder(root, index);
        cout << "============================================" << endl;
    }

private:
    void inorder(Node<T> *node, int &index, vector<T> &values)
    {
        if (node)
        {
            inorder(node->left, index, values);

            values.push_back(node->value);
            index++;

            inorder(node->right, index, values);
        }
    }

    void display_inorder(Node<T> *node, int &index)
    {
        if (node)
        {
            display_inorder(node->left, index);

            // Print node information
            cout << "Index: " << index << "| Value: " << node->value
                 << "| Size: " << node->size << "| Priority: " << node->priority << endl;

            index++;

            display_inorder(node->right, index);
        }
    }

    int get_size(Node<T> *node)
    {
        if (node == NULL)
            return 0;

        return node->size;
    }

    Node<T> *get_node_by_index(Node<T> *node, int index)
    {
        if (index <= get_size(node->left))
            return get_node_by_index(node->left, index);
        if (index == get_size(node->left) + 1)
            return node;
        return get_node_by_index(node->right, index - 1 - get_size(node->left));
    }

    void clear(Node<T> *&node);
    Node<T> *merge(Node<T> *t1, Node<T> *t2);
    pair<Node<T> *, Node<T> *> split(Node<T> *node, int target);
    bool erase(Node<T> *node);
    int indexOf(Node<T> *node, T val);
    T atIndex(Node<T> *node, int index);
    int lower_bound(Node<T> *node, T val);
    int upper_bound(Node<T> *node, T val);
    int count(Node<T> *node, T val);
};

template <typename T>
void Treap<T>::clear(Node<T> *&node)
{
    if (node == nullptr)
        return;

    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
}

template <typename T>
Node<T> *Treap<T>::merge(Node<T> *t1, Node<T> *t2)
{
    if (t1 == NULL)
        return t2;
    if (t2 == NULL)
        return t1;

    Node<T> *temp;
    if (t1->priority > t2->priority)
    {
        t1->size -= get_size(t1->right);
        temp = merge(t1->right, t2);
        t1->right = temp;
        t1->size += get_size(temp);
        return t1;
    }
    else
    {
        t2->size -= get_size(t2->left);
        temp = merge(t1, t2->left);
        t2->left = temp;
        t2->size += get_size(temp);
        return t2;
    }
}

template <typename T>
pair<Node<T> *, Node<T> *> Treap<T>::split(Node<T> *node, int target)
{
    if (node == NULL)
        return {NULL, NULL};

    pair<Node<T> *, Node<T> *> temp;
    if (node->value <= target)
    {
        node->size -= get_size(node->right);
        temp = split(node->right, target);
        node->right = temp.first;
        node->size += get_size(temp.first);
        return {node, temp.second};
    }
    else
    {
        node->size -= get_size(node->left);
        temp = split(node->left, target);
        node->left = temp.second;
        node->size += get_size(temp.second);
        return {temp.first, node};
    }
}

template <typename T>
bool Treap<T>::erase(Node<T> *node)
{
    if (node == root)
    {
        root = merge(node->left, node->right);
        return true;
    }

    Node<T> *temp = root;
    while (temp->left != node and temp->right != node)
    {
        temp->size -= 1;
        if (node->value <= temp->value)
            temp = temp->left;
        else
            temp = temp->right;
    }
    temp->size -= 1;

    if (temp->left == node or temp->right == node)
        return false;

    if (temp->left == node)
        temp->left = merge(node->left, node->right);
    else
        temp->right = merge(node->left, node->right);

    return true;
}

template <typename T>
int Treap<T>::indexOf(Node<T> *node, T val)
{
    if (!node)
        return -1;

    int leftSize = node->left ? node->left->size : 0;
    if (val < node->value)
    {
        return indexOf(node->left, val);
    }
    else if (val > node->value)
    {
        int rightIndex = indexOf(node->right, val);
        return (rightIndex == -1) ? -1 : leftSize + 1 + rightIndex;
    }

    return leftSize;
}

template <typename T>
T Treap<T>::atIndex(Node<T> *node, int index)
{
    int leftSize = node->left ? node->left->size : 0;

    if (index < leftSize)
        return atIndex(node->left, index);
    else if (index > leftSize)
        return atIndex(node->right, index - leftSize - 1);

    return node->value;
}

template <typename T>
int Treap<T>::count(Node<T> *node, T val)
{
    if (!node)
        return 0;

    int ct = (node->value == val) ? 1 : 0;
    if (val <= node->value)
    {
        return ct + count(node->left, val);
    }
    else
    {
        return ct + count(node->right, val);
    }
}

template <typename T>
int Treap<T>::lower_bound(Node<T> *node, T val)
{
    if (!node)
        return 0;

    int leftCount = (node->left && node->left->value < val) ? (1 + node->left->size) : 0;

    if (val <= node->value)
        return leftCount + lower_bound(node->left, val);
    else
        return leftCount + 1 + lower_bound(node->right, val);
}

template <typename T>
int Treap<T>::upper_bound(Node<T> *node, T val)
{
    if (!node)
        return 0;

    int leftCount = (node->left && node->left->value <= val) ? (1 + node->left->size) : 0;

    if (val < node->value)
        return leftCount + upper_bound(node->left, val);
    else
        return leftCount + 1 + upper_bound(node->right, val);
}

int main()
{
    Treap<int> Mytreap;
    int value;
    vector<int> vec;

    int first, last;

    int operation = -1;

    while (operation)
    {
        cin >> operation;

        switch (operation)
        {
        case 0:
            break;
        case 1:
            cout << boolalpha << Mytreap.empty() << endl;
            break;
        case 2:
            cout << Mytreap.size() << endl;
            break;
        case 3:
            Mytreap.clear();
            break;
        case 4:
            cin >> value;
            cout << Mytreap.insert(value) << endl;
            break;
        case 5:
            cin >> first;
            Mytreap.erase(first);
            break;
        case 6:
            cout << Mytreap.indexOf(value) << endl;
            break;
        case 7:
            cin >> first;
            cout << Mytreap.atIndex(first) << endl;
            break;
        case 10:
            cin >> first >> last;
            // cout << boolalpha << Mytreap.erase(first, last) << endl;
            break;
        case 11:
            cin >> first >> last;
            // Mytreap.slice(first, last);
            break;
        case 12:
            cin >> value;
            cout << Mytreap.lower_bound(value) << endl;
            break;
        case 13:
            cin >> value;
            cout << Mytreap.lower_bound(value) << endl;
            break;
        case 14:
            cin >> value;
            cout << Mytreap.count(value) << endl;
            break;
        case 15:
            vec = Mytreap.to_array();
            print_vector(vec);
            break;

        default:
            break;
        }
    }

    return 0;
}
