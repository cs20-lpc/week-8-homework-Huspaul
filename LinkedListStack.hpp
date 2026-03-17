#ifndef LINKEDLIST_STACK_HPP
#define LINKEDLIST_STACK_HPP
#include <iostream>
#include "Stack.hpp"

using namespace std;

// Node structure for linked list
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

// Stack class using linked list
template <typename T>
class LinkedListStack : public Stack<T> {
private:
    Node<T> * top; // points to the top node of stack

    // copy the state of the argument stack to `this`
    void copy(const LinkedListStack<T>&);
public:
        // constructor with the maximum size as the argument
        LinkedListStack();

        // copy constructor
        LinkedListStack(const LinkedListStack<T>&);

        // overloaded assignment operator
        LinkedListStack<T>& operator=(const LinkedListStack<T>&);

        // destructor
        virtual ~LinkedListStack();

        // remove all elements in the stack, resetting to the initial state
        virtual void clear() override;

        // return the current length of the stack
        virtual int getLength() const override;

        // determine if the stack currently empty
        virtual bool isEmpty() const override;

        // return the element at the top of the stack
        virtual T peek() const override;

        // remove the top element from the stack
        virtual void pop() override;

        // add the argument to the top of the stack
        virtual void push(const T&) override;

        // rearranges the elements in the stack according to the argument
        virtual void rotate(typename Stack<T>::Direction) override;

        // overloaded stream insertion operator to make printing easier
        virtual void print() override;
  
};
#include "LinkedListStack.tpp"
#endif
