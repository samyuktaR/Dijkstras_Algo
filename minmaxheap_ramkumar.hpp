#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <stdexcept>
#include <concepts>

struct DistanceVertexPair {
    double distance;
    int vertex;

    // Define operator> for comparing two DistanceVertexPair objects
    bool operator>(const DistanceVertexPair& other) const {
        // Compare based on distance
        return distance > other.distance;
    }
    
     // Define operator> for comparing two DistanceVertexPair objects
    bool operator<(const DistanceVertexPair& other) const {
        // Compare based on distance
        return distance < other.distance;
    }
};


template <typename T>
class MinHeap {
private:
    T *array;
    int capacity;
    int size;

    void swap(int a, int b) {
        T temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }

    void MinHeapify(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && array[left] < array[smallest]) {
            smallest = left;
        }

        if (right < size && array[right] < array[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            std::swap(array[index], array[smallest]);
            MinHeapify(smallest);
        }
    }

public:
    MinHeap(int capacity) : capacity(capacity), size(0) {
        array = new T[capacity];
    }

    ~MinHeap() {
        delete[] array;
    }

    void enqueue(const T& item) {
        if (size >= capacity) {
            throw std::runtime_error("Heap is full");
        }

        int current = size++;
        array[current] = item;
        while (current != 0 && array[(current - 1) / 2] > array[current]) {
            swap((current - 1) / 2, current);
            current = (current - 1) / 2;
        }
    }

    void dequeue() {
        if (size == 0) {
            throw std::runtime_error("Heap is empty");
        }
        array[0] = array[--size];
        MinHeapify(0);
    }

    T peek() {
        if (size == 0) {
            throw std::runtime_error("Heap is empty");
        }
        return array[0];
    }

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    bool isEmpty() {
        return size == 0;
    }
};

#endif /* MINHEAP_HPP */
