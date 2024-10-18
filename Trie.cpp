#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define gg (s[i] - 'a')

struct Node
{
public:
    Node *child[26];
    bool eos;

    Node()
    {
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;

        eos = false;
    }
};

class Trie
{
public:
    Node *root;

    Trie()
    {
        root = new Node();
    }

    void insert(string s);
    bool spellcheck(string s);
    vector<string> autocomplete(string s);
    vector<string> autocorrect(string s);

private:
    void display();
    void find_distance(string current, string given, vector<string>& res);
    void traverse(Node *temp, string s, vector<string> &words);
};

void Trie::traverse(Node *temp, string s, vector<string> &words)
{
    if (temp->eos)
    {
        words.push_back(s);
        return;
    }

    for (int i = 0; i < 26; i++)
    {
        if (temp->child[i])
        {
            char c = i + 'a';
            traverse(temp->child[i], s + c, words);
        }
    }
}

void shout(vector<string> &words)
{
    cout << words.size() << endl;
    cout << "============" << endl;
    for (auto it : words)
    {
        cout << it << endl;
    }
    cout << "============" << endl;
}

// display entire trie
void Trie::display()
{
    vector<string> words;
    string s = "";
    traverse(root, s, words);
    shout(words);
}

// push string in trie
void Trie::insert(string s)
{
    Node *temp = root;

    for (int i = 0; i < s.length(); i++)
    {
        if (!temp->child[gg])
            temp->child[gg] = new Node();

        temp = temp->child[gg];
    }

    temp->eos = true;
}

// case 1: search string in trie
bool Trie::spellcheck(string s)
{
    Node *temp = root;

    for (int i = 0; i < s.length(); i++)
    {
        if (!temp->child[gg])
        {
            return false;
        }
        temp = temp->child[gg];
    }

    return temp->eos;
}

// case 2: autocomplete string
vector<string> Trie::autocomplete(string s)
{
    vector<string> words;
    Node *temp = root;

    for (int i = 0; i < s.length(); i++)
    {
        if (!temp->child[gg]) // no match
            return words;
        temp = temp->child[gg];
    }

    traverse(temp, s, words);
    return words;
}

void Trie::find_distance(string current, string given, vector<string>& res){
    int m = current.length();
    int n = given.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i) {

        for (int j = 0; j <= n; ++j) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (current[i - 1] == given[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
        }
    }

    if(dp[m][n] <= 3){
        res.push_back(current);
    }

}


vector<string> Trie::autocorrect(string s){
    vector<string> words;
    vector<string> res;
    
    traverse(root, "", words);

    for(auto word: words){
        find_distance(word, s, res);
    }
    return res;
}

int main()
{
    int n, q;
    cin >> n >> q;

    Trie t;
    string s;

    while (n--)
    {
        cin >> s;
        t.insert(s);
    }

    vector<string> ans;
    while (q--)
    {
        ans.clear();
        cin >> n >> s;
        switch (n)
        {
        case 1:
            cout << t.spellcheck(s) << endl;
            break;
        case 2:
            ans = t.autocomplete(s);
            cout << ans.size() << endl;
            for (auto words : ans)
            {
                cout << words << endl;
            }
            break;
        case 3:
            ans = t.autocorrect(s);
            cout << ans.size() << endl;
            for (auto words : ans)
            {
                cout << words << endl;
            }
            break;
        default:
            break;
        }
    }

    return 0;
}