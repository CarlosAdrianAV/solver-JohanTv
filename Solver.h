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
    Solver(){};

    Solver(string expresion){
        this->root = nullptr;
        this->result = 0;

        this->operators['('] = 0;
        this->operators[')'] = 0;
        this->operators['+'] = 1;
        this->operators['-'] = 1;
        this->operators['*'] = 2;
        this->operators['/'] = 2;
        this->operators['^'] = 3;

        setExpresion(expresion);
    }

    void setExpresion(string expresion){
        this->expresion = expresion;
        resolve();
    }

    double getResult(){ return this->result; }

    void resolve(){
        stack<Node*> constructTree;
        queue<Node*> values;
        int valueOperator;
        Node* tempValue = nullptr;
        Node* tempOperator = nullptr;
        string valueNumeric;

        for (int i = 0; i<this->expresion.size(); ++i) {
            if(isdigit(this->expresion[i])){
                valueNumeric+=(this->expresion[i]);
                if(i == this->expresion.size()-1){
                    tempValue = new Node(valueNumeric);
                    values.push(tempValue);
                }
            }
            else if( 65<=(this->expresion[i]) && (this->expresion[i])<=90 ){
                if(this->variables.find((this->expresion[i])) == this->variables.end()){
                    getValueOfVariable((this->expresion[i]));
                }
                valueNumeric = to_string(this->variables.find(this->expresion[i])->second);
                if(i == this->expresion.size()-1){
                    tempValue = new Node(valueNumeric);
                    values.push(tempValue);
                }

            }

            else if((this->expresion[i]) == '('){
                tempOperator = new Node(this->expresion[i]);
                constructTree.push(tempOperator);
            }
            else if((this->expresion[i]) == ')'){
                if(valueNumeric != ""){
                    tempValue = new Node(valueNumeric);
                    values.push(tempValue);
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
                    tempValue = new Node(valueNumeric);
                    values.push(tempValue);
                    valueNumeric.clear();
                }
                tempOperator = new Node(this->expresion[i]);

                if(constructTree.empty()) constructTree.push(tempOperator);
                else{
                    valueOperator = this->operators.find(this->expresion[i])->second;

                    auto itMap = operators.find(constructTree.top()->getOperator());

                    if(itMap->second >= valueOperator){
                        values.push(constructTree.top());
                        constructTree.pop();
                        constructTree.push(tempOperator);
                    }
                    else constructTree.push(tempOperator);

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

    }

    void getValueOfVariable(char variable){
        int value;
        cout<<"Valor para la variable "<<variable<<": ";
        cin>>value;
        this->variables.insert(pair<char,int>(variable,value));
    }

};


#endif //SOLVER_JOHANTV_SOLVER_H
