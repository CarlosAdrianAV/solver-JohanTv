#ifndef SOLVER_JOHANTV_SOLVER_H
#define SOLVER_JOHANTV_SOLVER_H

#include "Use.h"
#include "Node.h"

class Solver {
private:
    string expresion;
    map<char, int> operators;
    map<char, double> variables;
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
        this->operators['-'] = 1;
        this->operators['+'] = 1;
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
            }
            else if(this->expresion[i] == '.'){
                valueNumeric+=(this->expresion[i]);
            }
            else if( (65<=(this->expresion[i]) && (this->expresion[i])<=90) || (97<=(this->expresion[i]) && (this->expresion[i])<=122) ){
                if(this->variables.find(this->expresion[i]) == this->variables.end())
                    getValueOfVariable(this->expresion[i]);

                valueNumeric = to_string(this->variables[this->expresion[i]]);
            }

            else if((this->expresion[i]) == '('){
                Operator = this->expresion[i];
                constructTree.push(new Node(Operator));
            }
            else if((this->expresion[i]) == ')'){
                if(!valueNumeric.empty()){
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

                if(!valueNumeric.empty()){
                    values.push(new Node(valueNumeric));
                    valueNumeric.clear();
                }
                Operator = this->expresion[i]; //char

                if(constructTree.empty()) constructTree.push(new Node(Operator));
                else{
                    valueOperator = this->operators[Operator];

                    auto itMap = this->operators.find(constructTree.top()->getOperator());

                    while(itMap->second >= valueOperator){
                        values.push(constructTree.top());
                        constructTree.pop();
                        if(constructTree.empty()) break;
                        itMap = this->operators.find(constructTree.top()->getOperator());
                    }
                    constructTree.push(new Node(Operator));
                }
            }
        }

        if(!valueNumeric.empty()) values.push(new Node(valueNumeric));

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
        double value;
        cout<<"Valor para la variable "<<variable<<": ";
        cin>>value;
        this->variables.insert(pair<char,double>(variable,value));
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
