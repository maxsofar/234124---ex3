#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

template <class T>
class Queue {
public:
    /*
     * C'tor of Queue class
     *
     * @return
     *      A new instance of Queue
    */
    Queue();

    /*
     * D'tor, Copy C'tor, Assignment operator overloading
     *
    */
    ~Queue();
    Queue& operator=(const Queue<T>& queue);
    Queue(const Queue<T>& queue);

    /*
     * pushback - adds an entity to the end of the queue
     *
     * @param entity - the item to be added
     *
    */
    void pushBack(const T& entity);

    /*
     * front
     *
     * @return
     *      The first entity in the queue
    */
    T& front() const;

    /*
     * popFront - removes the first entity in the queue
    */
    void popFront();

    /*
     * size
     *
     * @return
     *      Current number of entities in the queue
    */
    int size() const;

    /*
     * The iterator of the queue
    */
    class Iterator;

    /*
     * begin
     *
     * @return
     *      An instance of Iterator which points to the first entity in the queue
    */
    Iterator begin();

    /*
     * end returns a pointer to the beginning of the queue
     *
     * @return
     *      An instance of Iterator which points to the last entity in the queue
    */
    Iterator end();

    /*
     * The constant iterator of the queue
    */
    class ConstIterator;

    /*
     * begin
     *
     * @return
     *      An instance of ConstIterator which points to the first entity in the queue
    */
    ConstIterator begin() const;

    /*
     * end
     *
     * @return
     *      An instance of ConstIterator which points to the last entity in the queue
    */
    ConstIterator end() const;

    /*
     * EmptyQueue class declaration/empty implementation
     *
     * It is used to be thrown as exception in case of illegal operation on empty queue
    */
    class EmptyQueue{};

private:
    static const int INITIAL_SIZE = 5;
    static const int EXPAND_RATE = 2;

    int m_capacity;
    int m_size;
    int m_front;
    int m_back;
    T* m_queue;

    /*
     * expand - expands the capacity of queue
    */
    void expand();

    /*
     * shrink - reduces the capacity of queue
    */
    void shrink();

};

template <class T>
Queue<T>::Queue() :
        m_capacity(INITIAL_SIZE), m_size(0), m_front(0),
        m_back(-1), m_queue(new T[INITIAL_SIZE])
{}

template <class T>
Queue<T>::~Queue()
{
    delete[] m_queue;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
    if (&queue == this) {
        return *this;
    }
    T* toBeDeleted = m_queue;
    m_queue = new T[queue.m_capacity];
    m_size = queue.size();
    m_capacity = queue.m_capacity;
    m_front = queue.m_front;
    m_back = queue.m_back;
    for (int i = queue.m_front; i <= queue.m_back; ++i) {
        m_queue[i] = queue.m_queue[i];
    }
    delete[] toBeDeleted;
    return *this;
}

template <class T>
Queue<T>::Queue(const Queue<T>& queue) :
    m_capacity(queue.m_capacity), m_size(queue.size()), m_front(queue.m_front),
    m_back(queue.m_back), m_queue(new T[queue.m_capacity])
{
    for (int i = queue.m_front; i <= queue.m_back; ++i) {
    m_queue[i] = queue.m_queue[i];
    }
}

template <class T>
void Queue<T>::expand()
{
    m_capacity *= EXPAND_RATE;
    T* newQueue = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        newQueue[i] = m_queue[m_front + i];
    }
    delete[] m_queue;
    m_queue = newQueue;
    m_front = 0;
    m_back = m_size - 1;
}

template <class T>
void Queue<T>::pushBack(const T& entity)
{
    if (m_front + m_size == m_capacity) {
        T backup = entity;
        expand();
        ++m_back;
        m_queue[m_back] = backup;
        ++m_size;
    } else {
        ++m_back;
        m_queue[m_back] = entity;
        ++m_size;
    }
}

template <class T>
T& Queue<T>::front() const
{
    if (this->size() == 0) {
        throw EmptyQueue();
    }
    return m_queue[m_front];
}

template <class T>
void Queue<T>::shrink()
{
    m_capacity /= EXPAND_RATE;
    T* newQueue = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        newQueue[i] = m_queue[m_front + i];
    }
    delete[] m_queue;
    m_queue = newQueue;
    m_front = 0;
    m_back = m_size - 1;
}

template <class T>
void Queue<T>::popFront()
{
    if (this->size() == 0) {
        throw EmptyQueue();
    }

    ++m_front;
    --m_size;

    if (m_size < m_capacity / EXPAND_RATE) {
        shrink();
    }
}

template <class T>
int Queue<T>::size() const
{
    return m_size;
}

template <class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition condition)
{
    if (queue.size() == 0) {
        throw (typename Queue<T>::EmptyQueue());
    }
    Queue<T> result;

    for (const T& element : queue) {
        if (condition(element)) {
            result.pushBack(element);
        }
    }
    return result;
}

template <class T, class Function>
void transform(Queue<T>& queue, Function func)
{
    if (queue.size() == 0) {
        throw (typename Queue<T>::EmptyQueue());
    }
    for (T& element : queue) {
        func(element);
    }
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, m_front);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this, m_back+1);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this, m_front);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this, m_back+1);
}

//---------------------Iterator---------------------//
template <class T>
class Queue<T>::Iterator {
public:
    /*
     * Default Copy C'tor, D'tor and Assignment operator overloading
    */
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    ~Iterator() = default;

    /*
     * *() operator overloading
     *
     * @return
     *      A reference to the queue instance at current index
    */
    T& operator*() const;

    /*
     * ++ operator overloading
     *
     * @return
     *      An Iterator reference with index value increased  by one
    */
    Iterator& operator++();

    /*
     * != operator overloading
     *
     * @return
     *      True if iterators NOT equal
     *      False else
    */
    bool operator!=(const Iterator& iterator) const;

    /*
     * InvalidOperation class declaration/empty implementation
     *
     * It is used be thrown as exception in case illegal operation made to Iterator
    */
    class InvalidOperation{};

private:
    const Queue<T>* m_queuePtr;
    int m_index;

    /*
     * C'tor of Iterator class
     *
     * @return
     *      A new instance of Iterator
    */
    Iterator(const Queue<T>* queue, int index);
    friend class Queue<T>;
};

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int index) :
    m_queuePtr(queue), m_index(index)
{}

template <class T>

T& Queue<T>::Iterator::operator*() const
{
    return m_queuePtr->m_queue[m_index];
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (this->m_index == m_queuePtr->m_back+1) {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    return m_index != i.m_index;
}

//--------------------ConstIterator-------------------//
template <class T>
class Queue<T>::ConstIterator {
public:
    /*
     * Default Copy C'tor, D'tor and Assignment operator overloading
    */
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
    ~ConstIterator() = default;

    /*
     * *() operator overloading
     *
     * @return
     *      A reference to the queue instance at current index
    */
    const T& operator*() const;

    /*
     * ++ operator overloading
     *
     * @return
     *      An Iterator reference with index value increased  by one
    */
    ConstIterator& operator++();

    /*
     * != operator overloading
     *
     * @return
     *      True if iterators NOT equal
     *      False else
    */
    bool operator!=(const ConstIterator& iterator) const;

    /*
     * InvalidOperation class declaration/empty implementation
     *
     * It is used be thrown as exception in case illegal operation made to Iterator
    */
    class InvalidOperation{};

private:
    const Queue<T>* m_queuePtr;
    int m_index;

    /*
     * C'tor of Iterator class
     *
     * @return
     *      A new instance of Iterator
    */
    ConstIterator(const Queue<T>* queue, int index);
    friend class Queue<T>;
};

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index) :
        m_queuePtr(queue), m_index(index)
{}

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    return m_queuePtr->m_queue[m_index];
}


template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (this->m_index == m_queuePtr->m_back+1) {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& i) const
{
    return m_index != i.m_index;
}

#endif //EX3_QUEUE_H
