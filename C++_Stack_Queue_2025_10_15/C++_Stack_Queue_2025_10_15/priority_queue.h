#pragma once
#include <iostream>
#include <vector>
#include <functional>
using namespace std;
template <class T, class Container = vector<T>, class Compare = less<T>>
class priority_queue
{
public:

    priority_queue()
    {}

    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            push(*first);
            first++;
        }
    }

    bool empty() const
    {
        return c.empty();
    }

    size_t size() const
    {
        return c.size();
    }

    T& top() const
    {
        return c.front();
    }

    void push(const T& x)
    {
        c.push_back(x);
        Adjustup(c.size() - 1);
        for (int i = c.size() - 1; i >= 0; --i)
        {
            Adjustdown(c.size(),i);
        }
        int size = c.size();
        while (size)
        {
            swap(c[0], c[size - 1]);
            size--;
            Adjustdown(size,0);
        }
    }

    void swap(T& x, T& y)
    {
        T tmp = x;
        x = y;
        y = tmp;
    }

    void Adjustup(int child)
    {
        int father = (child - 1) / 2;
        while (child>0)
        {
            if (cmp(c[child], c[father]))
            {
                swap(c[father], c[child]);
                child = father;
                father = (father - 1) / 2;
            }
            else
                break;
        }
    }

    void Adjustdown(int size,int father)
    {
        int child = father * 2 + 1;
        while (child <size)
        {
            if (child != size-1)
            {
                child = cmp(c[child], c[child + 1]) ? child : child+1;
            }
            if (cmp(c[child], c[father]))
            {
                swap(c[father], c[child]);
                father = child;
                child = child * 2 + 1;
            }
            else
                break;
        }
    }

    void pop()
    {
        if (empty()) return;
        swap(c[0], c[c.size() - 1]);
        c.pop_back();
        if (!empty())
        {
            Adjustdown(c.size(),0);
        }
        for (int i = c.size() - 1; i >= 0; --i)
        {
            Adjustdown(c.size(), i);
        }
        int size = c.size();
        while (size)
        {
            swap(c[0], c[size - 1]);
            size--;
            Adjustdown(size, 0);
        }
    }

    void Print()
    {
        for (int i = 0; i < c.size(); i++)
        {
            cout << c[i] << " ";
        }
        cout << endl;
    }

private:

    Container c;
    Compare cmp;

};