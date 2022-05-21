#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

template <class T>
class Queue {
public:
    Queue();
    ~Queue();
    Queue(const Queue<T>& queue1);
    Queue& operator=(const Queue<T>& queue1);

    class Iterator;
    Iterator begin();
    Iterator end();

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    void pushBack(T x);
    T& front(int x = 0);
    void popFront();
    int size();

    class EmptyQueue{};

private:
    int m_capacity;
    int m_size;
    int m_front;
    int m_back;
    T* m_queue;

    static const int INITIAL_SIZE = 5;
    static const int EXPAND_RATE = 2;
    void expand();
    void shrink();

};

template <class T>
Queue<T>::Queue() {
    m_capacity = INITIAL_SIZE;
    m_size = m_front = 0;
    m_back = -1;
    m_queue = new T[INITIAL_SIZE];
}

template <class T>
Queue<T>::~Queue() {
    delete[] m_queue;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue) {
    if (this == &queue) {
        return *this;
    }
    delete[] m_queue;
    m_queue = new T[queue.m_sizesize];
    m_size = queue.size;
    m_capacity = queue.m_capacity;
    m_front = queue.m_front;
    m_back = queue.m_back;
    for (int i = 0; i < m_size; ++i) {
        m_queue[i] = queue.m_queue[i];
    }
    return *this;
}

template <class T>
Queue<T>::Queue(const Queue<T>& queue1) {
    m_capacity = queue1.m_capacity;
    m_size = queue1.m_size;
    m_front = queue1.m_front;
    m_back = queue1.m_back;
    m_queue = new T[queue1.m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_queue[i] = queue1.m_queue[i];
    }
}

template <class T>
void Queue<T>::expand() {
    m_capacity *= EXPAND_RATE;
    T* newQueue = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        newQueue[i] = m_queue[m_front + i];
    }
    delete[] m_queue;
    m_queue = newQueue;
}

template <class T>
void Queue<T>::pushBack(T x) {
    if (m_size == m_capacity - 1) {
        expand();
    }

    ++m_back;
    m_queue[m_back] = x;
    ++m_size;
}

template <class T>
T& Queue<T>::front(int x) {
    if (m_size == 0) {
        throw EmptyQueue();
    }
    return m_queue[m_front];
}

template <class T>
void Queue<T>::shrink() {
    m_capacity /= EXPAND_RATE;
    T* newQueue = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        newQueue[i] = m_queue[m_front + i];
    }
    delete m_queue;
    m_queue = newQueue;
    m_front = 0;
    m_back = m_size;
}

template <class T>
void Queue<T>::popFront() {
    if (m_size < m_capacity / EXPAND_RATE) {
        shrink();
    }

    ++m_front;
    --m_size;
}

template <class T>
int Queue<T>::size() {
    return m_size;
}

template <class T, class Condition>
Queue<T> filter(const Queue<T>& queue1, Condition c) {
    Queue<T> result;

    for (const T& element : queue1) {
        if (c(element)) {
            result.pushBack(element);
        }
    }
    return result;
}

template <class T, class Function>
void transform(Queue<T>& queue1, Function f) {
    for (T& element : queue1) {
        f(element);
    }
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() {
    return Iterator(this, m_front);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() {
    return Iterator(this, m_back+1);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const{
    return ConstIterator(this, m_front);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const{
    return ConstIterator(this, m_back+1);
}

//---------------------Iterator---------------------//
template <class T>
class Queue<T>::Iterator {
public:
    //const removed
    T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation{};

private:
    const Queue<T>* queue;
    int index;
    Iterator(const Queue<T>* queue, int index);
    friend class Queue<T>;
    friend class Queue<T>::ConstIterator;
};

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int index) :
    queue(queue), index(index) {
}

template <class T>
//const removed
T& Queue<T>::Iterator::operator*() const {
    return queue->m_queue[index];
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
    if (this->index == queue->m_back+1) {
        throw InvalidOperation();
    }
    ++index;
    return *this;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int) {
    Iterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& i) const {
    return index == i.index;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const {
    return !(*this == i);
}

//--------------------ConstIterator-------------------//
template <class T>
class Queue<T>::ConstIterator {
public:
    //const removed
    T& operator*() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator==(const ConstIterator& iterator) const;
    bool operator!=(const ConstIterator& iterator) const;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    class InvalidOperation{};

private:
    const Queue<T>* queue;
    int index;
    ConstIterator(const Queue<T>* queue, int index);
    friend class Queue<T>;
};

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index) :
        queue(queue), index(index) {
}

template <class T>
T& Queue<T>::ConstIterator::operator*() const {
    return queue->m_queue[index];
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++() {
    if (this->index == queue->m_back+1) {
        throw InvalidOperation();
    }
    ++index;
    return *this;
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int) {
    ConstIterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& i) const {
    return index == i.index;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& i) const {
    return !(*this == i);
}

#endif //EX3_QUEUE_H
