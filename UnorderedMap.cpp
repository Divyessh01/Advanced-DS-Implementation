#include <iostream>
#include <vector>
#define SIZE 1000
using namespace std;

template <typename K, typename V>
struct Node
{
    K key;
    V val;
    Node *next;

    Node(K k, V v)
    {
        key = k;
        val = v;
        next = nullptr;
    }
};

template <typename K, typename V>
class UnorderedMap
{
private:
    Node<K, V> *hashtable[SIZE];
    int siz;
    vector<int> hashindex;

    int myhash(int key)
    {
        return (key + SIZE) % SIZE;
    }

    int myhash(long key){
        return (key + SIZE) % SIZE;
    }

    int myhash(double key){
        long hash = key;
        return (hash + SIZE) % SIZE;
    }

    int myhash(char key){
        int hash = key;
        return (hash + SIZE) % SIZE;
    }

    int myhash(string key){
        int hash = 0;
        for(int i = 0; i < key.length(); i++){
            hash += key[i]; 
        }
        return (hash + SIZE) % SIZE;
    }

    int myhash(float key){
        long hash = key;
        return (hash + SIZE) % SIZE;
    }



public:
    void display()
    {
        cout << "========================" << endl;
        for (auto index: hashindex)
        {
            cout << index << " ";
            
                Node<K, V> *current = hashtable[index];
                while (current != NULL)
                {
                    cout << current->key << " : ";
                    cout << current->val << " || ";
                    current = current->next;
                }
            
            cout << endl;
        }
        cout << "========================" << endl;
    }

    UnorderedMap()
    {
        hashindex.clear();
        siz = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            hashtable[i] = NULL;
        }
    }

    bool insert(K key, V val)
    {
        int index = myhash(key);

        if (hashtable[index] == NULL)
        {
            hashtable[index] = new Node(key, val);
            siz++;
            hashindex.push_back(index);
            return true;
        }

        Node<K, V> *current = hashtable[index];

        while (current->key != key and current->next != NULL)
            current = current->next;

        if (current->key == key)
            return false;

        current->next = new Node(key, val);
        siz++;

        return true;
    }

    bool erase(K key)
    {
        int index = myhash(key);
        bool success = false;

        if (hashtable[index] == NULL)
            return success;

        Node<K, V> *current = hashtable[index];
        Node<K, V> *temp = current;
        if (current->key == key)
        {
            hashtable[index] = current->next;
            success = true;
        }
        else
        {
            while (temp->key != key and temp->next != NULL)
            {
                current = temp;
                temp = temp->next;
            }
            if (temp->key == key)
            {
                current->next = temp->next;
                success = true;
            }
            else
                return success;
        }

        if (success)
        {
            free(temp);
            siz--;
            if (hashtable[index] == NULL)
            {
                int i;
                for (i = 0; i < hashindex.size(); i++)
                {
                    if (hashindex[i] == index)
                        break;
                }
                hashindex.erase(hashindex.begin() + i);
            }
        }
        return success;
    }

    bool contains(K key)
    {
        int index = myhash(key);

        if (hashtable[index] == NULL)
            return false;

        Node<K, V> *current = hashtable[index];
        while (current->key != key and current->next != NULL)
            current = current->next;

        if (current->key == key)
            return true;

        return false;
    }

    V &operator[](K key)
    {
        int index = myhash(key);

        if (hashtable[index] == NULL)
        {
            hashtable[index] = new Node(key, V{});

            siz++;
            hashindex.push_back(index);
            return hashtable[index]->val;
        }

        Node<K, V> *current = hashtable[index];

        while (current->key != key and current->next != NULL)
            current = current->next;

        if (current->key == key)
            return current->val;

        current->next = new Node(key, V{});
        current = current->next;
        siz++;

        return current->val;
    }

    void clear()
    {
        for (auto index: hashindex)
        {
            Node<K, V> *current = hashtable[index];
            Node<K, V> *temp;

            while (current->next != NULL)
            {
                temp = current;

                temp = current->next;
                current->next = temp->next;
                free(temp);
            }

            temp = hashtable[index];
            hashtable[index] = NULL;
            free(temp);
        }

        hashindex.clear();
        siz = 0;
    }

    int size()
    {
        return siz;
    }

    bool empty()
    {
        if (siz == 0)
            return true;

        return false;
    }

    vector<K> keys()
    {
        vector<K> allkeys;
        for (auto index : hashindex)
        {
            Node<K, V> *current = hashtable[index];

            while (current->next != NULL)
            {
                allkeys.push_back(current->key);
                current = current->next;
            }

            allkeys.push_back(current->key);
        }
        return allkeys;
    }
};

int main()
{
    char key;
    char val;
    vector<char> allkeys;
    UnorderedMap<char, char> myMap;

    int q;
    cin >> q;
    int operation = -1;

    while (q--)
    {
        cin >> operation;

        switch (operation)
        {
        case 1:
            cin >> key >> val;
            cout << boolalpha << myMap.insert(key, val) << endl;
            break;
        case 2:
            cin >> key;
            cout << boolalpha << myMap.erase(key) << endl;
            break;
        case 3:
            cin >> key;
            cout << boolalpha << myMap.contains(key) << endl;
            break;
        case 4:
            cin >> key;
            cout << myMap[key] << endl;
            break;
        case 5:
            myMap.clear();
            break;
        case 6:
            cout << myMap.size() << endl;
            break;
        case 7:
            cout << boolalpha << myMap.empty() << endl;
            break;
        case 8:
            allkeys = myMap.keys();
            for (auto it : allkeys)
                cout << it << endl;
            break;
        default:
            break;
        }
    }

    return 0;
}