#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <iostream>
#include <string>
#include <assert.h>
#include <string.h>
using namespace std;

class My_String {
public:
    friend ostream& operator<<(ostream& _cout, const My_String& s);

    friend istream& operator>>(istream& _cin, My_String& s);
public:
    typedef char* iterator;
public:
    My_String(const char* str = "");
    My_String(const My_String& s);
    My_String& operator=(const My_String& s);
    void Check(const char* str);
    void Check(const char str);
    void Check(size_t n);
    ~My_String();
    void Print();
    //////////////////////////////////////////////////////////////
    // iterator
    iterator begin();
    iterator end();
    /////////////////////////////////////////////////////////////
    // modify
    void push_back(char c);
    My_String& operator+=(char c);
    void append(const char* str);
    My_String& operator+=(const char* str);
    void clear();
    void swap(My_String& s);
    const char* c_str()const;
    /////////////////////////////////////////////////////////////
    // capacity
    size_t size()const;
    size_t capacity()const;
    bool empty()const;
    void resize(size_t n, char c = '\0');
    void reserve(size_t n);
    void replace(size_t pos, const char ch);
    void replace(size_t pos, const char* str);
    /////////////////////////////////////////////////////////////
    // access
    char& operator[](size_t index);
    const char& operator[](size_t index)const;
    /////////////////////////////////////////////////////////////

    //relational operators
    bool operator<(const string& s);
    bool operator<=(const string& s);
    bool operator>(const string& s);
    bool operator>=(const string& s);
    bool operator==(const string& s);
    bool operator!=(const string& s);
    // 返回c在string中第一次出现的位置
    size_t find(char c, size_t pos = 0) const;
    // 返回子串s在string中第一次出现的位置
    size_t find(const char* s, size_t pos = 0) const;
    // 在pos位置上插入字符c/字符串str，并返回该字符的位置
    My_String& insert(size_t pos, char c);
    My_String& insert(size_t pos, const char* str);
    // 删除pos位置上的元素，并返回该元素的下一个位置
    My_String& erase(size_t pos, size_t len);
private:
    char* _str;
    size_t _capacity;
    size_t _size;

};
