#ifndef SOLVER_JOHANTV_NODE_H
#define SOLVER_JOHANTV_NODE_H

#include "Use.h"

struct Node {
    Node* left;
    Node* right;
    string expresion;

    void null(){
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(string expresion){
        this->expresion = expresion;
        null();
    }
    Node(char symbol){
        this->expresion = "";
        this->expresion+=symbol;
        null();
    }

    string getExpresion(){
        return this->expresion;
    }
    char getOperator(){
        return this->expresion[0];
    }

    bool isOperator(){
        switch(expresion[0]){
            case '+':
            case '-':
            case '*':
            case '/':
            case '^': return true;
            default: return false;
        }
    }

    double execute(){
        double result;
        if(isOperator()){
            switch(expresion[0]){
                case '+': {
                    result = left->execute() + right->execute();
                    break;
                }
                case '-': {
                    result = left->execute() - right->execute();
                    break;
                }
                case '*': {
                    result = left->execute() * right->execute();
                    break;
                }
                case '/': {
                    result = left->execute() / right->execute();
                    break;
                }
                case '^': result = pow(left->execute(),right->execute());
            }
            return result;
        }
        else return stof(expresion);
    };
};


#endif //SOLVER_JOHANTV_NODE_H
