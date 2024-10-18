#include <iostream>
using namespace std;
#define x  - '0'

string result;

// stack implementation for expression evaluation
class Stack{
    private:
        string arr[3];
        int top = -1;
    
    public:

        void push(string num){
            arr[++top] = num;
        }

        string pop(){
            if(top != -1){
                return arr[top--];
            }
            return "-1";
        }

        string topp(){
            if(top != -1){
                return arr[top];
            }
            return "-1";
        }

        bool empty(){
            if(top == -1){
                return true;
            }
            return false;
        }
};


// trim initial zeroes
void trim(string &s){
    int i = 0;
    while(i < s.length()){
        if(s[i] != '0'){
            break;
        }
        i++;
    }
    if(i == s.length()) s = "0";
    else s = s.substr(i);
}

// reverse the string
void strrev(string &res){
    int n = res.length();

    char temp;
    int loop = 1;
    while(loop <= n/2){
        temp = res[loop-1];
        res[loop - 1] = res[n - loop];
        res[n-loop] = temp;
        loop++;
    }
}

// function to check whether num1 is smaller than num2
// returns true, if num1 < num2
bool issmall(string num1, string num2){

    trim(num1);
    trim(num2);

    int i = num1.length()-1;
    int j = num2.length()-1;
    if(i < j) return true;

    if(i == j){
        for(int ii = 0; ii <= i; ii++){
            if(num1[ii] > num2[ii]){
                break;
            } else if(num1[ii] < num2[ii]){
                return true;
            }
        }
    }

    return false;
}

// addition of two numbers
string add(string num1, string num2){
    string res = "";

    if(num1 == "" || num1 == "0"){
        if(num2 == "")  return "0";
        else return num2;
    } else if(num2 == "" || num2 == "0"){
        return num1;
    }

    int i = num1.length() - 1;
    int j = num2.length() - 1;

    int carry = 0, sum = 0;

    while((i >= 0) and (j >= 0)){
        sum = (num1[i]x) + num2[j]x + carry;
        carry = sum / 10;
        sum %= 10;
        res = to_string(sum) + res;
        i--;
        j--;
    }
    
    while(i >= 0){
        sum = (num1[i]x) + carry;
        carry = sum / 10;
        sum %= 10;
        res = to_string(sum) + res;
        i--;
    }

    while(j >= 0){
        sum = (num2[j]x) + carry;
        carry = sum / 10;
        sum %= 10;
        res = to_string(sum) + res;
        j--;
    }

    if(carry) res = to_string(carry) + res;

    return res;
}

// subtraction of two numbers
string sub(string num1, string num2){
    string res = "";

    if(num1 == num2)    return "0";

    int i = num1.length() - 1;
    int j = num2.length() - 1;

    int bor = 0, sub = 0;

    while(j >= 0){
        sub = (num1[i]x) - (num2[j]x) - bor;

        if(sub < 0){
            sub += 10;
            bor = 1;
        }
        else bor = 0;

        res = to_string(sub) + res;
        i--;
        j--;
    }
    
    while(i >= 0){
        sub = (num1[i]x) - bor;
        
        if(sub < 0){
            sub += 10;
            bor = 1;
        }
        else bor = 0;

        res = to_string(sub) + res;
        i--;
    }

    trim(res);

    return res;
}


// multiplication of two numbers
string multiply(string num1, string num2){
    string res = "";
    trim(num1);
    trim(num2);

    if(num1 == "0" || num2 == "0" ) return "0";

    if(num1 == "1") return num2;
    if(num2 == "1") return num1;
    
    int i = num1.length() - 1;
    int j = num2.length() - 1;

    int carry = 0, dig = 0;

    int k = 0, shift = 0;
    int temp = 0, tempc = 0;
    string s;
    while(j >= 0){
        k = shift;
        i = num1.length()-1;
        tempc = 0;
        carry = 0;
        while(i >= 0){
            dig = (num1[i]x) * (num2[j]x) + carry;
            carry = dig / 10;
            dig = dig%10;
            if(k >= res.length()){
                temp = dig + tempc;
                tempc = temp/10;
                temp = temp % 10;
                s = to_string(temp);
                res += s[0];
            } else {
                temp = (res[k]x) + dig + tempc;
                tempc = temp/10;
                temp = temp % 10;
                s = to_string(temp);
                res[k] = s[0];
            }
            i--;
            k++;
        }
        if(carry || tempc)   res += to_string(carry+tempc);
        shift++;
        j--;
    }

    strrev(res);
    
    return res;
}

// generate string of zeroes
string zerostring(int n){
    string temp = "";
    if(n <= 0)  return temp;
    while(n--){
        temp += "0";
    }
    return temp;
}

// divides two numbers and returns integer value
string divide(string num1, string num2){
    string res = "", modulo = num1;

    trim(num1);
    trim(num2);

    if(issmall(num1, num2)) return "0";

    int digdiff = 0;
    string temp = "";
    while (!issmall(num1, num2)){

        digdiff = num1.length() - num2.length() - 1;
        temp = zerostring(digdiff);
    
        while(!issmall(num1, num2+temp)){
            num1 = sub(num1, num2+temp);
            res = add(res,"1"+temp);
        }

    }

    return res;
}

// remainder of division of two numbers
string modulo(string num1, string num2){
    trim(num1);
    trim(num2);
    string res = "", modulo = num1;

    if(issmall(num1, num2)) return modulo;

    int digdiff = 0;
    string temp = "";
    while (!issmall(num1, num2)){

        digdiff = num1.length() - num2.length() - 1;
        temp = zerostring(digdiff);
    
        while(!issmall(num1, num2+temp)){
            num1 = sub(num1, num2+temp);
        }

    }

    modulo = num1;
    trim(modulo);

    return modulo;
}

// set precedency
int prec(char c){
    if(c == '+' || c == '-'){
        return 1;
    } else if(c == 'x' || c == '/'){
        return 2;
    }
    return -1;
}

// operation 1: evaluate the given expression
string evaluate(string init){
    string res = "";
    string num = "";
    Stack st;
    Stack op;
    string temp = "";

    string num1, num2;

    for(int i = 0; i < init.length(); i++){
        if(init[i] >= '0' and init[i] <= '9'){
            num += init[i];
        } else {
            st.push(num);
            num = "";

            if(op.empty() || prec(init[i]) > prec(op.topp()[0])){
                temp = init[i];
                op.push(temp);
            } else{
                while(!op.empty() || (init[i]) <= prec(op.topp()[0])){
                    num2 = st.pop();
                    num1 = st.pop();
                    temp = op.pop();
                    switch(temp[0]){
                        case '+':
                            res = add(num1, num2);
                            break;
                        case '-':
                            res = sub(num1, num2);
                            break;
                        case 'x':
                            res = multiply(num1, num2);
                            break;
                        case '/':
                            res = divide(num1, num2);
                            break;
                        default:
                            break;
                    }
                    st.push(res);
                }
                temp = init[i];
                op.push(temp);
            }
        }
    }
    st.push(num);

    // evaluate remainings till stack is empty
    while(!op.empty()){
        num2 = st.pop();
        num1 = st.pop();
        temp = op.pop();
        switch(temp[0]){
            case '+':
                res = add(num1, num2);
                break;
            case '-':
                res = sub(num1, num2);
                break;
            case 'x':
                res = multiply(num1, num2);
                break;
            case '/':
                res = divide(num1, num2);
                break;
            default:
                break;
        }
        st.push(res);
    }

    res = st.pop();
    return res;
}

// operation 2: find the exponent | ie num1^num2 | constraint: num2 < 2^63
string exponent(string num1, long long num2){
    string res;

    // base
    trim(num1);
    if(num1 == "0")   return "1";
    if(num2 == 0)   return "1";
    if(num2 == 1)   return num1;

    // recursion
    if(num2 % 2 == 0){
        string temp = exponent(num1, num2/2);
        res = multiply(temp, temp);
    } else {
        string temp = exponent(num1, num2-1);
        res = multiply(temp, num1);
    }

    return res;
}

// operation 3: find the GCD of given two numbers
string GCD(string num1, string num2){
    trim(num1);
    trim(num2);

    if(num2 == "0") return num1;    // base
    
    return GCD(num2, modulo(num1, num2));   // recursion
}

// operation 4: find the factorial of given number
string factorial(string num){
    string res = "1";
    string i = "1";

    trim(num);

    if(num == "0" || num == "1") return "1";
    
    while(issmall(i, num)){
        res = multiply(res, i);
        i = add(i, "1");
    }

    res = multiply(res, num);
    
    return res;
}

// main function
int main(){

    int operation;
    cin >> operation;

    string num1, num2;

    switch (operation)
    {
    case 1:
        // Basic expression evaluation
            // addition / subtraction / multiplication / division
        cin >> num1;
        result = evaluate(num1);
        break;

    case 2:
        // exponent
        cin >> num1 >> num2;
        result = exponent(num1, atoll(num2.c_str()));
        break;

    case 3:
        // GCD
        cin >> num1 >> num2;
        result = GCD(num1, num2);
        break;

    case 4:
        // Factorial
        cin >> num1;
        result = factorial(num1);
        break;

    default:
        cout << "Invalid operation!" << endl;
        break;
    }

    cout << result << endl;

    return 0;
}