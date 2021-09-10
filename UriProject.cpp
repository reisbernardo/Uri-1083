/*
NOME: Bernardo Siqueira Esteves dos Reis
TIA: 32019270

NOME: Daniel Aloia Plastina
TIA: 32063539

NOME: Lucas Kenzo Akiyama
TIA: 32025165
*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

int priority(char c) {
    switch(c) {
        case '^': return 6;
        case '*': case '/': return 5;
        case '+': case '-': return 4;
        case '>': case '<': case '=': case '#': return 3;
        case '.': return 2;
        case '|': return 1;
    }
    return -1;
}


int checkError(string str){
    int i, n = str.length(), error = 0;

    for(i=0; i < n; i++){  
        if(!(isalnum(str[i]) || priority(str[i]) != -1)) {
            if(str[i] == '(' || str[i] == ')') error = 1;
            else error = 2;
        }
    }
    return error;
}


string infixToPostfix(string str){
    int i, n = str.length(), errorType;
    char top;
    string post;
    stack <char> st;
    
    for(i = 0; i < n; i++){
        if(isalnum(str[i])){
            post += str[i];
        } 
        else if(str[i] == '(') {
            st.push(str[i]);
        }
        else if(str[i] == ')') {
            top = st.top();
            st.pop();
            while(top != '('){
                post += top;
                top = st.top();
                st.pop();
            }
        } 
        else{
            if(priority(str[i]) == -1) return "Lexical Error!";

            if(priority(str[i+1]) != -1 || priority(str[i-1]) != -1) return "Syntax Error!";
            
            while(!st.empty() && priority(st.top()) >= priority(str[i])){
                top = st.top();
                st.pop();
                post += top;
            }
            st.push(str[i]);
        }
    }

    while(!st.empty()){
        top = st.top();
        st.pop();
        post += top;
    }
    
    errorType = checkError(post);

    if(errorType == 1) return "Syntax Error!";
    if(errorType == 2) return "Lexical Error!";

    return post;
}

int main(){
    string expressao;
    while(getline(cin, expressao) && !cin.eof()){
        cout << infixToPostfix(expressao) << endl;
    }
    return 0;
}