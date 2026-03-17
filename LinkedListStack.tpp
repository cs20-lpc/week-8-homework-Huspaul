template <typename T>
LinkedListStack<T>::LinkedListStack()
    : top(nullptr)
{ }

template <typename T>
LinkedListStack<T>::LinkedListStack(const LinkedListStack<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedListStack<T>& LinkedListStack<T>::operator=(const LinkedListStack<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedListStack<T>::~LinkedListStack() {
    clear();
}

template <typename T>
void LinkedListStack<T>::clear() {
    while (top != nullptr) {
        Node<T>* nodeToDelete = top;
        top = top->next;
        delete nodeToDelete;
    }

    this->length = 0;
}

template <typename T>
void LinkedListStack<T>::copy(const LinkedListStack<T>& copyObj) {
    top = nullptr;
    this->length = 0;

    if (copyObj.top == nullptr) {
        return;
    }

    Node<T>* srcCurr = copyObj.top;
    Node<T>* newHead = new Node<T>(srcCurr->data);
    Node<T>* destCurr = newHead;
    srcCurr = srcCurr->next;

    while (srcCurr != nullptr) {
        destCurr->next = new Node<T>(srcCurr->data);
        destCurr = destCurr->next;
        srcCurr = srcCurr->next;
    }

    top = newHead;
    this->length = copyObj.length;
}

template <typename T>
int LinkedListStack<T>::getLength() const {
    return this->length;
}


template <typename T>
bool LinkedListStack<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
T LinkedListStack<T>::peek() const {
    if (isEmpty()) {
        throw string("peek: error, stack is empty, cannot access the top");
    }

    return top->data;
}

template <typename T>
void LinkedListStack<T>::pop() {
    if (isEmpty()) {
        throw string("pop: error, stack is empty, avoiding underflow");
    }

    Node<T>* nodeToDelete = top;
    top = top->next;
    delete nodeToDelete;
    this->length--;
}

template <typename T>
void LinkedListStack<T>::push(const T& elem) {
    Node<T>* newNode = new Node<T>(elem);
    newNode->next = top;
    top = newNode;
    this->length++;
}

template <typename T>
void LinkedListStack<T>::rotate(typename Stack<T>::Direction dir) {
    if (isEmpty()) {
        throw string("rotate: error, stack is empty, unable to rotate");
    }
    else if (this->length == 1) {
        return;
    }
    else if (dir == Stack<T>::RIGHT) {
        Node<T>* oldTop = top;
        top = top->next;
        oldTop->next = nullptr;

        Node<T>* curr = top;
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        // Move old top node to bottom.
        curr->next = oldTop;
    }
    else if (dir == Stack<T>::LEFT) {
        Node<T>* prev = nullptr;
        Node<T>* curr = top;

        while (curr->next != nullptr) {
            prev = curr;
            curr = curr->next;
        }

        // Move bottom node to top.
        prev->next = nullptr;
        curr->next = top;
        top = curr;
    }
    else {
        throw string("rotate: error, unknown direction");
    }
}

template <typename T>
void LinkedListStack<T>::print() {
    cout << "LinkedListStack contents: ";
    if (isEmpty()) {
        cout << "Stack is empty, no elements to display.\n";
    }
    else {
        Node<T> *curr = top;
        while (curr != nullptr){
            cout <<  curr->data  << "\t";
            curr = curr->next;
        }
    }

    cout << endl;
}
