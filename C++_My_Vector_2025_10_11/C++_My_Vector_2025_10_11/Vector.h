#pragma once
#include <assert.h>
#include <iostream>
#include <string.h>
#include <string>
#include <windows.h>
#include <vector>
using namespace std;

template<class T>
class My_Vector {
public:

    // Vector的迭代器是一个原生指针

    typedef T* iterator;

    typedef const T* const_iterator;

    iterator begin()
    {
        return _start;
    }

    iterator end()
    {
        return _finish;
    }

    const_iterator cbegin()
    {
        return _start;
    }

    const_iterator cend() const
    {
        return _finish;
    }
    // construct and destroy

    My_Vector()
    {}

    My_Vector(int n, const T& value = T())
    {
        reserve(n);
        for (int i = 0; i < n; i++)
        {
            _start[i] = value;
        }
        _finish = _start + n;
    }

        template<class InputIterator>
        My_Vector(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }

        My_Vector(const My_Vector<T>& v)
        {
            reserve(v.capacity());
            for (size_t i = 0; i < v.size(); i++)
            {
                _start[i] = v._start[i];
            }
            _finish = _start + v.size();
            _endofstorage = _start + v.capacity();
        }

        My_Vector<T>& operator= (My_Vector<T> v)
        {
            reserve(v.capacity());
            for (int i = 0; i < v.size(); i++)
            {
                _start[i] = v._start[i];
            }
            _finish = _start + v.size();
            _endofstorage = _start + v.capacity();
            return *this;
        }

        ~My_Vector()
        {
            delete[] _start;
        }

        // capacity

        size_t size() const
        {
            return _finish - _start;
        }

        size_t capacity() const
        {
            return _endofstorage - _start;
        }

        void reserve(size_t n)
        {
            if (capacity() > n)
            {
                return;
            }
            iterator tmp = new T[n]();
            size_t oldsize = size();
            for (int i = 0; i < oldsize; i++)
            {
                tmp[i] = _start[i];
            }
            delete[] _start;
            _start = tmp;
            _finish = _start + oldsize;
            _endofstorage = _start + n;
        }

        void resize(size_t n, const T& value = T())
        {
            if (n > size())
            {
                if (n > capacity())
                {
                    reserve(n);
                }
                iterator is = _finish;
                while (is - _start != n)
                {
                    *is = value;
                    is++;
                }
            }
            else
            {
                _finish = _endofstorage = _start + n;
            }
        }


        ///////////////access///////////////////////////////

        T& operator[](size_t pos)
        {
            return *(_start + pos);
        }

        const T& operator[](size_t pos)const
        {
            return *(_start + pos);
        }



        ///////////////modify/////////////////////////////

        void push_back(const T& x)
        {
            if (size() == capacity())
            {
                reserve(capacity() + 1);
            }
            *_finish = x;
            _finish++;
        }

        void pop_back()
        {
            assert(!size());
            _finish--;
        }

        void swap(My_Vector<T>& v)
        {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_endofstorage, v._endofstorage);
        }

        iterator insert(iterator pos, const T& x)
        {
            assert(pos >= _start && pos < _finish);
            int len = pos - _start;
            if (size() == capacity())
            {
                reserve(capacity() + 1);
            }
            pos = _start + len;
            iterator end = _finish;
            while (end != pos - 1)
            {
                *end = *(end-1);
                end--;
            }
            *pos = x;
            _finish++;
            return pos;
        }

        iterator erase(iterator pos)
        {
            assert(pos >= _start && pos < _finish);
            iterator begin = pos;
            while (begin != _finish - 1)
            {
                *begin = *(begin + 1);
                begin++;
            }
            _finish--;
            return pos;
        }

        void Print()
        {
            iterator it = begin();
            while (it!=_finish)
            {
                cout << *it << " ";
                it++;
            }
            cout << endl << "size:" << size() << " " << "capacity:" << capacity() << endl;
        }

        void clear()
        {
            _finish = _start;
        }

        void replace(iterator pos,const T& n)
        {
            *pos = n;
        }

private:

    iterator _start = nullptr;// 指向数据块的开始

    iterator _finish = nullptr;// 指向有效数据的尾

    iterator _endofstorage = nullptr; // 指向存储容量的尾
};