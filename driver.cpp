#include <iostream>
#include <string>
#include "StackFactory.hpp"

using namespace std;

template <typename T>
void expectEqual(const T& actual, const T& expected, const string& msg) {
    if (actual != expected) {
        throw string("Assertion failed: ") + msg;
    }
}

void testIntStacks() {
    Stack<int>* listStack = StackFactory<int>::GetStack();
    Stack<int>* arrayStack = StackFactory<int>::GetStack(20);

    for (int i = 1; i <= 5; i++) {
        listStack->push(i);
        arrayStack->push(i);
    }

    expectEqual(listStack->getLength(), 5, "LinkedListStack int length after push");
    expectEqual(arrayStack->getLength(), 5, "ArrayStack int length after push");
    expectEqual(listStack->peek(), arrayStack->peek(), "peek should match");

    listStack->rotate(Stack<int>::RIGHT);
    arrayStack->rotate(Stack<int>::RIGHT);
    expectEqual(listStack->peek(), arrayStack->peek(), "peek after RIGHT rotate");

    listStack->rotate(Stack<int>::LEFT);
    arrayStack->rotate(Stack<int>::LEFT);
    expectEqual(listStack->peek(), arrayStack->peek(), "peek after LEFT rotate");

    while (!listStack->isEmpty() && !arrayStack->isEmpty()) {
        expectEqual(listStack->peek(), arrayStack->peek(), "top should match before pop");
        listStack->pop();
        arrayStack->pop();
    }

    expectEqual(listStack->isEmpty(), true, "linked stack empty");
    expectEqual(arrayStack->isEmpty(), true, "array stack empty");

    delete listStack;
    delete arrayStack;
}

void testStringStack() {
    LinkedListStack<string> stack;
    stack.push("CS");
    stack.push("20");
    stack.push("Rocks");
    expectEqual(stack.peek(), string("Rocks"), "string peek");

    stack.rotate(Stack<string>::RIGHT);
    expectEqual(stack.peek(), string("20"), "string peek after RIGHT");

    stack.rotate(Stack<string>::LEFT);
    expectEqual(stack.peek(), string("Rocks"), "string peek after LEFT");

    stack.clear();
    expectEqual(stack.getLength(), 0, "length after clear");
}

void testExceptions() {
    LinkedListStack<int> stack;
    bool threwPeek = false;
    bool threwPop = false;
    bool threwRotate = false;

    try { stack.peek(); } catch (const string&) { threwPeek = true; }
    try { stack.pop(); } catch (const string&) { threwPop = true; }
    try { stack.rotate(Stack<int>::LEFT); } catch (const string&) { threwRotate = true; }

    expectEqual(threwPeek, true, "peek throws on empty stack");
    expectEqual(threwPop, true, "pop throws on empty stack");
    expectEqual(threwRotate, true, "rotate throws on empty stack");
}

int main() {
    try {
        testIntStacks();
        testStringStack();
        testExceptions();
        cout << "All stack tests passed." << endl;
    } catch (const string& err) {
        cerr << err << endl;
        return 1;
    }

    return 0;
}
