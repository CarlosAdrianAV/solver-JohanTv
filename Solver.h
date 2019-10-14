#ifndef SOLVER_JOHANTV_SOLVER_H
#define SOLVER_JOHANTV_SOLVER_H

#include "Use.h"
#include "Node.h"

class Solver {
private:
    string expresion;
    map<char, int> operators;
    map<char, int> variables;
    double result;

    Node* root;

public:
    Solver(){
        this->root = nullptr;
        this->result = 0;
        fillOperators();
    };

    Solver(string expresion){
        this->root = nullptr;
        this->result = 0;

        fillOperators();

        setExpresion(expresion);
    }
    void fillOperators(){
        this->operators['('] = 0;
        this->operators[')'] = 0;
        this->operators['+'] = 1;
        this->operators['-'] = 1;
        this->operators['*'] = 2;
        this->operators['/'] = 2;
        this->operators['^'] = 3;
    }
    void setExpresion(string expresion){
        this->expresion = expresion;
        resolve();
    }

    double getResult(){
        this->variables.clear();
        return this->result;
    }

    void resolve(){
        stack<Node*> constructTree;
        queue<Node*> values;
        int valueOperator;
        string valueNumeric;
        char Operator;
        for (int i = 0; i<this->expresion.size(); ++i) {
            if(isdigit(this->expresion[i])){
                valueNumeric+=(this->expresion[i]);
                if(i == this->expresion.size()-1) values.push(new Node(valueNumeric));
            }
            else if( 65<=(this->expresion[i]) && (this->expresion[i])<=90 ){
                if(this->variables.find((this->expresion[i])) == this->variables.end())
                    getValueOfVariable((this->expresion[i]));

                valueNumeric = to_string(this->variables.find(this->expresion[i])->second);
                if(i == this->expresion.size()-1) values.push(new Node(valueNumeric));

            }

            else if((this->expresion[i]) == '('){
                Operator = this->expresion[i];
                constructTree.push(new Node(Operator));
            }
            else if((this->expresion[i]) == ')'){
                if(valueNumeric != ""){
                    values.push(new Node(valueNumeric));
                    valueNumeric.clear();
                }
                while(constructTree.top()->getOperator() != '('){
                    values.push(constructTree.top());
                    constructTree.pop();
                }
                constructTree.pop(); //delete ')'

            }
            else if(this->operators.find(this->expresion[i]) != this->operators.end()){

                if(valueNumeric != ""){
                    values.push(new Node(valueNumeric));
                    valueNumeric.clear();
                }
                Operator = this->expresion[i];

                if(constructTree.empty()) constructTree.push(new Node(Operator));
                else{
                    valueOperator = this->operators.find(this->expresion[i])->second;

                    auto itMap = operators.find(constructTree.top()->getOperator());

                    if(itMap->second >= valueOperator){
                        values.push(constructTree.top());
                        constructTree.pop();
                        constructTree.push(new Node(Operator));
                    }
                    else constructTree.push(new Node(Operator));
                }
            }
        }
        while(!constructTree.empty()){
            values.push(constructTree.top());
            constructTree.pop();
        }

        this->root = values.front();
        while(!values.empty()){
           if(!values.front()->isOperator()){
               constructTree.push(values.front());
               values.pop();
           }
           else{
               this->root = values.front();
               values.pop();

               this->root->right = constructTree.top();
               constructTree.pop();

               this->root->left = constructTree.top();
               constructTree.pop();

               constructTree.push(this->root);
           }
        }

        this->result = this->root->execute();
        destroy(this->root);
    }

    void getValueOfVariable(char variable){
        int value;
        cout<<"Valor para la variable "<<variable<<": ";
        cin>>value;
        this->variables.insert(pair<char,int>(variable,value));
    }

    void destroy(Node* it) {
        if (it != nullptr) {
            destroy(it->left);
            destroy(it->right);
            delete it;
        }
        this->root = nullptr;
    }
};


#endif //SOLVER_JOHANTV_SOLVER_H
