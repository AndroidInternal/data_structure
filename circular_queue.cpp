// =====================================================================================
// 
//       Filename:  circular_queue.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/23/2016 05:36:33 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  李锐, root@lirui.in
//        License:  Copyright © 2016 李锐. All Rights Reserved.
// 
// =====================================================================================
#include <stdio.h>
#include <stdlib.h>

template<class T>
class circular_queue
{
private:
    int member_size; //now member count size
    int memory_block_size; //queue memory member size, default is 1024
    T *memory_front; //memory node front
    int front_pos, tail_pos;//position of front and tail
public:
    circular_queue();
    circular_queue(int memory_block_size);
    ~circular_queue();
    bool push(T t);
    T pop();
    bool isEmpty();
    bool isFull();
    int getSize();
};

template<class T>
circular_queue<T>::circular_queue()
{
    circular_queue(1024);
}

template<class T>
circular_queue<T>::circular_queue(int memory_block_size)
{
    this->memory_block_size = memory_block_size;
    this->front_pos = 0;
    this->tail_pos = 0;
    this->member_size = 0;
    this->memory_front = (T *)malloc(memory_block_size * sizeof(T));
}

template<class T>
circular_queue<T>::~circular_queue()
{
    free(memory_front);
}

template<class T>
bool circular_queue<T>::push(T t)
{
    if(isFull())
    {
        printf("the queue is full, can't push anymore!\n");
        return false;
    }
    memory_front[tail_pos++] = t;
    tail_pos = tail_pos % memory_block_size;
    member_size++;
    return true;
}

template<class T>
T circular_queue<T>::pop()
{
    if(isEmpty())
    {
        printf("the queue is empty, can't pop anymore!\n");
        return NULL;
    }
    T *front = &memory_front[front_pos++];
    front_pos = front_pos % memory_block_size;
    member_size--;
    return *front;
}

template<class T>
bool circular_queue<T>::isFull()
{
    return member_size  >= memory_block_size;
}

template<class T>
bool circular_queue<T>::isEmpty()
{
    return member_size == 0;
}

template<class T>
int circular_queue<T>::getSize()
{
    return member_size;
}

template<class T>
void push_some(circular_queue<T> &test_queue, int count)
{
    for(int i = 0; i < count; i++)
    {
        printf("pushing %d\n", i);
        test_queue.push(i);
    }
}

template<class T>
void pop_some(circular_queue<T> &test_queue, int count)
{
    for(int i = 0; i < count; i++)
    {
        printf("poping %d\n", test_queue.pop());
    }
}

template<class T>
void test_push_pop(circular_queue<T> &test_queue, int count)
{
    push_some(test_queue, count);
    printf("--------------\n");
    pop_some(test_queue, count);
    printf("--------------\n\n");
}

int main()
{
    circular_queue<int> test_queue(5);
    for(int i = 0; i < 6; i++)
    {
        printf("%d time push and pop\n", i);
        test_push_pop(test_queue, 2);
    }
    return 0;
}
