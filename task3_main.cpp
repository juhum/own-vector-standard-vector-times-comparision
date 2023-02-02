#include <iostream>
#include <stdexcept>
#include <ctime>
#include <windows.h>
#include <vector>
#include <cmath>


class Vector {
    int capacity;
    int elements;
    int *mem;
public:
    Vector():
            capacity(10),
            elements(0),
            mem(new int[capacity])
    {}


    void push_back(int x) {
        if (capacity == elements) {
            int *tmp = new int[capacity * 2];


            for (int i = 0 ; i < capacity ; i++) {
                tmp[i] = mem[i];
            }

            delete [] mem;
            mem = tmp;
            capacity *= 2;
        }

        mem[elements] = x;
        elements++;
    }

    Vector(int cap) {
        capacity=cap;
        elements=0;
        mem=new int[capacity];
    }

    bool empty(){
        if(elements==0)
            return true;
        return false;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("pop() called on an empty stack");
        }
        int *tmp = new int[capacity];
        for(int i=0;i<elements-1;i++){
            tmp[i]=mem[i];
        }
        delete [] mem;
        mem = tmp;
        elements--;
    }

    int back() {
        if (empty()) {
            throw std::runtime_error("top() called on an empty stack");
        }
        return mem[elements - 1];
    }

    ~Vector() {
        delete [] mem;
    }

    int size() {
        return capacity;
    }

    int elemento(){
        return elements;
    }

    int &operator[](int x) {
        if(x>=0 && x<capacity) {
            return mem[x];
        }
        else {
            throw std::runtime_error("out_of_range");
        }
    }

    void resize(int x){
        int *tmp = new int[x];
        if(x>capacity) {
            for (int i = 0; i < capacity; i++) {
                tmp[i] = mem[i];
            }
        }
        else if(x<capacity) {
            for (int i = 0; i < x; i++) {
                tmp[i] = mem[i];
            }
            elements = x;
        }
        else {
            throw std::runtime_error("resizing_into_same_size");
        }

        delete [] mem;
        capacity = x;
        mem = tmp;
    }

    void erase(int x){
        if(x>elements){
            throw std::runtime_error("invalid index");
        }
        else {
            int *tmp = new int[capacity];
            for (int i = x + 1; i < elements; i++) {
                mem[i - 1] = mem[i];
            }
            elements--;
            for (int i = 0; i < elements; i++)
                tmp[i] = mem[i];

            delete[] mem;
            mem = tmp;
        }
    }

    void erase(int x,int y){
        if(x>elements || y>elements){
            throw std::runtime_error("invalid index");
        }
        else {


            int *tmp = new int[capacity];
            for (int i = 0; i < x; i++) {
                tmp[i] = mem[i];
            }
            int j = y + 1;
            for (int i = x; i < elements; i++) {
                tmp[i] = mem[j];
                if (j < elements)
                    j++;
            }

            elements = elements - (y - x + 1);
            delete[] mem;
            mem = tmp;

        }
    }


};
std::ostream &operator<<(std::ostream &os, Vector &a){
    for(int i=0;i<a.size();i++){
        os << a[i] << " ";
    }
    return os;
}


int main() {

    LARGE_INTEGER t1, t2, f, diff;
  srand(time(NULL));
    int size = 1000000;
    Vector my;
    Vector tmp;

    std::vector<int>other,temp;

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<size;i++)
        my.push_back(rand());
    QueryPerformanceCounter(&t2);

    std::cout << "Own Vector time for pushing back random values " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<size;i++)
        other.push_back(rand());
    QueryPerformanceCounter(&t2);

    std::cout << "Standard Vector time for pushing back random values " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;


    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<size;i++)
        tmp.push_back(my[i]);
    QueryPerformanceCounter(&t2);

    std::cout << "Own Vector time for reading values and pushing back to another vector " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;


    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<size;i++)
        temp.push_back(other[i]);
    QueryPerformanceCounter(&t2);
    std::cout << "Standard Vector time for reading values and pushing back to another vector " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<1000;i++)
        tmp.erase(i);
    QueryPerformanceCounter(&t2);
    std::cout << "Own Vector time for erasing first 1000 values " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=0;i<1000;i++)
        temp.erase(temp.begin()+i);
    QueryPerformanceCounter(&t2);
    std::cout << "Standard Vector time for erasing first 1000 values " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;


    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=1;i<5000;i++)
        my.resize(size-i);
    QueryPerformanceCounter(&t2);
    std::cout << "Own Vector time for resizing 1000 times " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;

    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t1);
    for(int i=1;i<5000;i++)
        other.resize(size-i);
    QueryPerformanceCounter(&t2);
    std::cout << "Standard Vector time for resizing 1000 times " << ((t2.QuadPart - t1.QuadPart) / (double)f.QuadPart) << " seconds" << std::endl;



    return 0;
}
