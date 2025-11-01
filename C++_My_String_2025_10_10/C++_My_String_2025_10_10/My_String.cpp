#include "My_String.h"
#include <assert.h>
My_String::My_String(const char* str)
{
	assert(str);
	_size = strlen(str);
	_capacity = _size + 1;
	_str = new char[_capacity];
	strcpy(_str, str);
}
My_String::My_String(const My_String& s)
{
	_size = s._size;
	_capacity = s._capacity;
	_str = new char[_capacity];
	strcpy(_str, s.c_str());
}
My_String::~My_String()
{
	delete[] _str;
	_str = nullptr;
	_size = 0;
	_capacity = 0;
}
void My_String::Check(const char* str)
{
	int len = strlen(str);
	if (_size + len +1 > _capacity)
	{
		while (_capacity < _size + len + 1)
		{
			_capacity *= 2;
		}
		char* tmp = new char[_capacity];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
	}
}

void My_String::Check(const char str)
{
	if (_size + 2 > _capacity)
	{
		while (_capacity < _size+2)
		{
			_capacity *= 2;
		}
		char* tmp = new char[_capacity];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
	}
}

void My_String::Check(size_t n)
{
	if (n > _capacity)
	{
		while (_capacity < n)
		{
			_capacity *= 2;
		}
		char* tmp = new char[_capacity];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
	}
}

void My_String::push_back(char c)
{
	Check(c);
	_str[_size] = c;
	_size++;
	_str[_size] = '\0';
}
My_String& My_String::operator+=(char c)
{
	My_String::push_back(c);
	return *this;
}

const char* My_String::c_str()const
{
	return _str;
}

My_String& My_String::operator+=(const char* str)
{
	Check(str);
	strcpy(_str + _size, str);
	_size += strlen(str);
	return *this;
}


My_String& My_String::operator=(const My_String& s)
{ 
	if (this != &s) {
		delete[] _str;
		_size = s._size;
		_capacity = s._capacity;
		_str = new char[_capacity];
		strcpy(_str, s.c_str());
		return *this;
	}
}

void My_String::append(const char* str)
{
	My_String::operator+=(str);
}

void My_String::clear()
{
	_size = 0;
	_capacity = 0;
}

void My_String::swap(My_String & s)
{
	_size = s._size;
	_capacity = s._capacity;
	char* tmp = _str;
	_str = s._str;
	s._str = tmp;
}

size_t My_String::size()const
{
	return _size;
}

size_t My_String::capacity()const
{
	return _capacity;
}

bool My_String::empty()const
{
	if (_size == 0)
	{
		return true;
	}
	return false;
}

void My_String::resize(size_t n, char c)
{
	if (n > _size)
	{
		Check(n);
		while (_size != n)
		{
			_str[_size] = c;
			_size++;
		}
		_str[_size] = '\0';
	}
	else if (n < _size)
	{
		_size = n;
	}
}

void My_String::reserve(size_t n)
{
	if (n > _capacity)
	{
		_capacity = n;
		char* tmp = new char[_capacity];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
	}
}

char& My_String::operator[](size_t index)
{
	if (index >= _size)
	{
		cout << "Error" << endl;
	}
	return _str[index];
}

const char& My_String::operator[](size_t index)const
{
	if (index >= _size)
	{
		cout << "Error" << endl;
	}
	return _str[index];
}

bool My_String::operator<(const string& s)
{
	return !strcmp(_str, s.c_str());
}
bool My_String::operator==(const string& s)
{
	if (!strcmp(_str, s.c_str()))
	{
		return true;
	}
	return false;
}

bool My_String::operator<=(const string& s)
{
	return *this < s || *this == s;
}

bool My_String::operator>(const string& s)
{
	return !(*this < s);
}

bool My_String::operator>=(const string& s)
{
	return *this > s || *this == s;
}

bool My_String::operator!=(const string& s)
{
	return !(*this == s);
}

size_t My_String::find(char c, size_t pos) const
{
	int count = pos;
	while (_str[count] != c)
	{
		count++;
	}
	return count;
}

size_t My_String::find(const char* s, size_t pos) const
{
	char* tmp = strstr(_str + pos, s);
	return tmp - _str;
}

My_String& My_String::insert(size_t pos, char c)
{
	char* tmp = new char[_size + 2];
	int count = 0;
	while (count != pos)
	{
		tmp[count] = _str[count];
		count++;
	}
	tmp[count] = c;
	while (count != _size)
	{
		tmp[count + 1] = _str[count];
		count++;
	}
	tmp[_size + 1] = '\0';
	_size++;
	_capacity = _size + 1;
	delete[] _str;
	_str = tmp;
	return *this;
}

My_String& My_String::insert(size_t pos, const char* str)
{
	int len = strlen(str);
	int count = 0;
	char* tmp = new char[_size + len + 1];
	while (count != pos)
	{
		tmp[count] = _str[count];
		count++;
	}
	strcpy(tmp + count, str);
	while (count != _size)
	{
		tmp[count + len] = _str[count];
		count++;
	}
	tmp[count + len] = '\0';
	_size += len;
	_capacity = _size + 1;
	delete[] _str;
	_str = tmp;
	return *this;
}

My_String& My_String::erase(size_t pos, size_t len)
{
	char* tmp = new char[_size];
	int count = 0;
	while (count != pos)
	{
		tmp[count] = _str[count];
		count++;
	}
	while (count != _size)
	{
		tmp[count] = _str[count+len];
		count++;
	}
	_size--;
	_capacity = _size + 1;
	delete[] _str;
	_str = tmp;
	return *this;
}

ostream& operator<<(ostream& _cout, const My_String& s)
{
	_cout << s._str;
	return _cout;
}

istream& operator>>(istream& _cin, My_String& s)
{
	_cin >> s._str;
	return _cin;
}

void My_String::Print()
{
	cout << _str << endl;
	cout << "size:" << _size << endl;
	cout << "capacity:" << _capacity << endl;
}















