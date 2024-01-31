/**
 * @file utils.h
 * 
 * @brief Miscellaneous & Useful tools.
 * 
 * @author SJTU-XHW
 * @date   Jan 4, 2024
 */

#pragma once
#include "assert.h"

/** @brief The minimum size of the basic containers. */
static constexpr int minimumSize = 10;


/** @brief Simple exception class for self-defined containers. */
class ContainerNoElement {
	const char* message;    /**< Exception message. */
public:
    /** @brief Constructor. */
	ContainerNoElement(const char* msg="No element in the container.") : message(msg) {}
    /** @brief Gets the exception message. */
	const char* what() const { return message; }
};

/** @brief Comparison template for containers. */
template <class comparable>
bool greater(const comparable& a, const comparable& b) { return a > b; }

/** @brief Comparison template for containers. */
template <class comparable>
bool smaller(const comparable& a, const comparable& b) { return a < b; }


/** @brief Stack template based on linear structures. */
template <class elemT>
class seqStack {
private:
	elemT* data;                /**< Data list for the stack. */
	int maxSize;                /**< Maximum size of the inner list. */
	int topIdx;                 /**< Current top index of the inner list. */

    /** @brief Reallocates and expands space when adding element to a full stack. */
	inline void doubleSpace();
public:
    /** 
     * @brief Constructor of the stack.
     * 
     * @param initSize The initial size of the stack.
     */
	seqStack(int initSize = minimumSize) : maxSize(initSize), topIdx(-1) {
		data = new elemT[maxSize];
	}
    seqStack(const seqStack& cp) {
        maxSize = cp.maxSize, topIdx = cp.topIdx;
        data = new elemT[maxSize];
        for (int i = 0; i < maxSize; ++i)
            data[i] = cp.data[i];
    }
    seqStack(seqStack&& cp) {
        maxSize = cp.maxSize, topIdx = cp.topIdx;
        data = cp.data;
        cp.data = nullptr;
    }
	~seqStack() { if (data) delete[] data; }
    inline seqStack& operator=(const seqStack& cp);
    inline seqStack& operator=(seqStack&& cp);

    /** @brief Check if the stack is empty now. */
	bool isempty() const { return topIdx == -1; }
    /** @brief Push an element into the stack. */
	void push(const elemT& dt) {
		if (topIdx >= maxSize - 1) 
			doubleSpace(); 
		data[++topIdx] = dt;
	}
    /** 
     * @brief Retrieve the top element from the stack and remove it from stack.
     * 
     * @exception Raise ContainerNoElement when empty.
     */
	elemT pop() { 
		if (topIdx == -1) throw ContainerNoElement();
		return data[topIdx--];
	}
    /** 
     * @brief Retrieve the top element from the stack.
     * 
     * @exception Raise ContainerNoElement when empty.
     */
	elemT top() const { 
		if (topIdx == -1) throw ContainerNoElement();
		return data[topIdx]; 
	}
    /** @brief Clear the stack. */
    void clear() { topIdx = -1; }
};

template <class elemT>
seqStack<elemT>& seqStack<elemT>::operator=(const seqStack& cp) {
    if (this == &cp) return *this;
    if (data) delete[] data;

    maxSize = cp.maxSize, topIdx = cp.topIdx;
    data = new elemT[maxSize];
    for (int i = 0; i < maxSize; ++i)
        data[i] = cp.data[i];
    
    return *this;
}

template <class elemT>
seqStack<elemT>& seqStack<elemT>::operator=(seqStack&& cp) {
    if (data) delete[] data;

    maxSize = cp.maxSize, topIdx = cp.topIdx;
    data = cp.data;
    cp.data = nullptr;
    
    return *this;
}

template <class elemT>
void seqStack<elemT>::doubleSpace() {
	elemT* tmp = data;
	data = new elemT[maxSize * 2];
	for (int i = 0; i <= topIdx; ++i)
		data[i] = tmp[i];
	delete[] tmp;
	maxSize *= 2;
}


/** @brief Queue template based on linear structures. */
template <class elemT>
class seqQueue {
protected:
    elemT* data;    /**< The data list for the queue. */
    int front;      /**< The head index of the inner list. */
    int rear;       /**< The tail index of the inner list. */
    int maxSize;    /**< The maximum size of the queue. */
    /** 
     * @brief The length of current queue.
     * 
     * @note It helps with distinguish the empty 
     *       situation from the full situation.
     */
    int len;

    /** @brief Reallocates and expands space when adding element to a full queue. */
    inline void doubleSpace();

public:
    /** 
     * @brief Constructor of the queue.
     * 
     * @param initSize The initial size of the queue.
     */
    seqQueue(int initSize = minimumSize) :maxSize(initSize) {
        data = new elemT[initSize];
        front = len = 0; rear = maxSize - 1;
    }
    seqQueue(const seqQueue& cp) {
        front = cp.front, rear = cp.rear;
        maxSize = cp.maxSize; len = cp.len;
        data = new elemT[maxSize];
        for (int i = 0; i < maxSize; ++i)
            data[i] = cp.data[i];
    }
    seqQueue(seqQueue&& cp) {
        front = cp.front, rear = cp.rear;
        maxSize = cp.maxSize; len = cp.len;
        data = cp.data;
        cp.data = nullptr;
    }
    virtual ~seqQueue() {
        if (data) delete[] data;
    }
    inline seqQueue& operator=(const seqQueue& cp);
    inline seqQueue& operator=(seqQueue&& cp);

    /** @brief Check if the queue is empty now. */
    bool isempty() const { return len == 0; }
    /** @brief Gets the length of the current queue. */
    int length() const { return len; }
    /** 
     * @brief Gets the head of the queue.
     * 
     * @exception Raise ContainerNoElement when empty.
     */
    elemT getHead() const {
        if (isempty()) throw ContainerNoElement();
        return data[front];
    }
    /** 
     * @brief Gets the tail of the queue.
     * 
     * @exception Raise ContainerNoElement when empty.
     */
    elemT getTail() const {
        if (isempty()) throw ContainerNoElement();
        return data[rear];
    }
    /** @brief Push the element to the tail of the queue. */
    void enQueue(const elemT& dt) {
        if (len == maxSize) doubleSpace();
        rear = (rear+1) % maxSize;
        data[rear] = dt;
        ++len;
    }
    /** 
     * @brief Gets the head of the queue and remove it from current queue.
     * 
     * @exception Raise ContainerNoElement when empty.
     */
    elemT deQueue() {
        if (isempty()) throw ContainerNoElement();
        elemT ans = data[front];
        front = (front+1) % maxSize;
        --len;
        return ans;
    }
    /** @brief Clear the queue. */
    void clear() {
        front = len = 0; rear = maxSize - 1;
    }
};

template <class elemT>
seqQueue<elemT>& seqQueue<elemT>::operator=(const seqQueue& cp) {
    if (this == &cp) return *this;
    if (data) delete[] data;

    front = cp.front, rear = cp.rear;
    maxSize = cp.maxSize; len = cp.len;
    data = new elemT[maxSize];
    for (int i = 0; i < maxSize; ++i)
        data[i] = cp.data[i];
    
    return *this;
}

template <class elemT>
seqQueue<elemT>& seqQueue<elemT>::operator=(seqQueue&& cp) {
    if (data) delete[] data;

    front = cp.front, rear = cp.rear;
    maxSize = cp.maxSize; len = cp.len;
    data = cp.data;
    cp.data = nullptr;

    return *this;
}

template <class elemT>
void seqQueue<elemT>::doubleSpace() {
    elemT* tmp = data;
    data = new elemT[maxSize*2];
    for (int i = 0; i < len; ++i) {
        data[i] = tmp[(front+i)%maxSize];
    }
    maxSize *= 2;
    front = 0; rear = len - 1;
    delete[] tmp;
}

/**
 * @brief Bidirectional queue template based on linear queue implementation.
 * 
 * @see seqQueue
 */
template <class elemT>
class seqDeque : public seqQueue<elemT> {
public:
    seqDeque(int initSize = minimumSize)
        : seqQueue<elemT>(initSize) {}
    /** @brief Insert an element to the head of the deque. */
    void prepend(const elemT& dt) {
        if (this->len == this->maxSize) this->doubleSpace();
        this->front = (this->front - 1 + this->maxSize) % this->maxSize;
        this->data[this->front] = dt;
        ++this->len;
    }
    /** @brief Retrieve an element from the tail of the deque. */
    elemT pop_back() {
        if (this->isempty()) throw ContainerNoElement();
        elemT res = this->data[this->rear];
        this->rear = (this->rear - 1 + this->maxSize) % this->maxSize;
        --this->len;
        return res;
    }
};

/** @brief Priority queue template based on binary heap. */
template <class elemT, bool (*comp)(const elemT&, const elemT&)=greater>
class priorityQueue {
public:
    /** 
     * @brief Constructor of the priority queue.
     * 
     * @param initSize The initial size of the priority queue.
     */
    priorityQueue(int initSize=minimumSize);
    /**
     * @brief Construct a priority queue from a existing array.
     * 
     * @param initArray Initial element array.
     * @param arrSize   The size of the array.
     * 
     * @note This is superior to the time complexity of 
     *       using the default constructor and then entering the queue one by one.
     *       O(n) for the former and O(n^2) for the latter.
     */
    priorityQueue(const elemT* initArray, int arrSize);
    ~priorityQueue();

    priorityQueue(const priorityQueue& cp);
    priorityQueue(priorityQueue&& cp);
    priorityQueue& operator=(const priorityQueue& cp);
    priorityQueue& operator=(priorityQueue&& cp);

    /** @brief Push the element to the priority queue. */
    inline void enQueue(const elemT& element);
    /** 
     * @brief Gets the head of the priority queue and remove it from current queue.
     * 
     * @exception Raise ContainerNoElement when empty.
     */
    inline elemT deQueue();
    /** 
     * @brief Gets the head of the priority queue.
     * 
     * @exception Raise ContainerNoElement when empty.
     */
    elemT front() const { return pHeap[0]; }
    /** @brief Check if the priority queue is empty now. */
    bool empty() const { return length == 0; }
    /** @brief Gets the current length of the priority queue. */
    int size() const { return length; }

    /**
     * @brief Decrease the value of a certain key.
     * 
     * @warning Please ensure that `lowerValInHeap` is smaller than the original ones.
     */
    void decreaseKeyTo(int idx, const elemT& lowerValInHeap);

private:
    elemT*  pHeap;      /**< Binary heap. */
    int     length;     /**< Current length. */
    int     maxSize;    /**< The maximum size of the priority queue. */

    /** @brief Reallocates and expands space when adding element to a full queue. */
    void expand();
    /**
     * @brief Adjusting the ordering of a binary heap.
     * 
     * @param i Adjusting from i node.
     */
    void percolateDown(int i);
};

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
priorityQueue<elemT, comp>::priorityQueue(int initSize) {
    assert(initSize > 0);

    pHeap = new elemT[initSize];
    length = 0; maxSize = initSize;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
priorityQueue<elemT, comp>::priorityQueue(const elemT* initArr, int arrSize) {
    length = arrSize; maxSize = arrSize + minimumSize;
    pHeap = new elemT[maxSize];
    for (int i = 0; i < arrSize; ++i)
        pHeap[i] = initArr[i];
    for (int i = arrSize / 2 - 1; i >= 0; --i)
        percolateDown(i);
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
priorityQueue<elemT, comp>::~priorityQueue() { if (pHeap) delete[] pHeap; }

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
priorityQueue<elemT, comp>::priorityQueue(const priorityQueue& cp) {
    length = cp.length;
    maxSize = cp.maxSize;
    pHeap = new elemT[maxSize];
    for (int i = 0; i < maxSize; ++i)
        pHeap[i] = cp.pHeap[i];
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
priorityQueue<elemT, comp>::priorityQueue(priorityQueue&& cp) {
    length = cp.length;
    maxSize = cp.maxSize;
    pHeap = cp.pHeap;
    cp.pHeap = nullptr;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
priorityQueue<elemT, comp>& priorityQueue<elemT, comp>::operator=(const priorityQueue& cp) {
    if (this == &cp) return *this;

    length = cp.length;
    maxSize = cp.maxSize;
    delete[] pHeap;
    pHeap = new elemT[maxSize];
    for (int i = 0; i < maxSize; ++i)
        pHeap[i] = cp.pHeap[i];
    
    return *this;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
priorityQueue<elemT, comp>& priorityQueue<elemT, comp>::operator=(priorityQueue&& cp) {
    length = cp.length;
    maxSize = cp.maxSize;
    pHeap = cp.pHeap;
    cp.pHeap = nullptr;
    return *this;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
void priorityQueue<elemT, comp>::percolateDown(int i) {
    elemT elementI = pHeap[i];
    int nextIdx = 2 * i + 1;
    while (nextIdx < length) {
        if (nextIdx + 1 < length && comp(pHeap[nextIdx + 1], pHeap[nextIdx]))
            ++nextIdx;
        if (comp(elementI, pHeap[nextIdx])) break;
        pHeap[i] = pHeap[nextIdx];
        i = nextIdx;
        nextIdx = 2 * i + 1;
    }
    pHeap[i] = elementI;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
void priorityQueue<elemT, comp>::expand() {
    elemT* newHeap = new elemT[maxSize * 2];
    for (int i = 0; i < length; ++i)
        newHeap[i] = pHeap[i];
    delete[] pHeap;
    pHeap = newHeap;
    maxSize *= 2;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
void priorityQueue<elemT, comp>::enQueue(const elemT& element) {
    if (length == maxSize) expand();
    int i = length, nextIdx = (i - 1) / 2;
    ++length;
    while (i > 0) {
        if (comp(pHeap[nextIdx], element)) break;
        pHeap[i] = pHeap[nextIdx];
        i = nextIdx;
        nextIdx = (i - 1) / 2;
    }
    pHeap[i] = element;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
elemT priorityQueue<elemT, comp>::deQueue() {
    if (length < 1) throw ContainerNoElement();
    
    elemT ans = pHeap[0];
    pHeap[0] = pHeap[length - 1];
    --length;
    percolateDown(0);
    return ans;
}

template <class elemT, bool (*comp)(const elemT&, const elemT&)>
void priorityQueue<elemT, comp>::decreaseKeyTo(int idx, const elemT& lowerValInHeap) {
    pHeap[idx] = lowerValInHeap;
    percolateDown(idx);
}
