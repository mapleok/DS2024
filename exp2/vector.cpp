template<typename T>
class Stack {
private:
    T* elements;
    int top;
    int capacity;

    void resize() {
        T* newElements = new T[capacity * 2];
        for (int i = 0; i < capacity; i++) {
            newElements[i] = elements[i];
        }
        capacity *= 2;
        delete[] elements;
        elements = newElements;
    }

public:
    Stack() {
        capacity = 10;
        elements = new T[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] elements;
    }

    void push(T element) {
        if (top == capacity - 1) {
            resize();
        }
        elements[++top] = element;
    }

    T pop() {
        if (top >= 0) {
            return elements[top--];
        }
        throw std::runtime_error("Stack is empty.");
    }

    T peek() {
        if (top >= 0) {
            return elements[top];
        }
        throw std::runtime_error("Stack is empty.");
    }

    bool empty() {
        return top == -1;
    }
};
