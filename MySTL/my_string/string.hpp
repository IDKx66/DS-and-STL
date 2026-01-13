#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm> // for std::swap
#include <cctype>    // for isspace

namespace idk
{

    class string
    {
    public:
        // 迭代器定义
        typedef char *iterator;
        typedef const char *const_iterator;

        // 常量定义
        static const size_t npos = -1;

    public:
        // ==========================================
        // 1. 构造、析构与赋值
        // ==========================================

        // 构造函数 (支持无参和C字符串)
        string(const char *str = "")
        {
            _size = strlen(str);
            _capacity = _size;
            _str = new char[_capacity + 1];
            strcpy(_str, str);
        }

        // 拷贝构造 (深拷贝)
        string(const string &s)
        {
            _size = s._size;
            _capacity = s._capacity;
            _str = new char[_capacity + 1];
            strcpy(_str, s._str);
        }

        // 赋值重载 (深拷贝)
        string &operator=(const string &s)
        {
            if (this != &s)
            {
                char *tmp = new char[s._capacity + 1];
                strcpy(tmp, s._str);
                delete[] _str;
                _str = tmp;
                _size = s._size;
                _capacity = s._capacity;
            }
            return *this;
        }

        // 析构函数
        ~string()
        {
            if (_str)
            {
                delete[] _str;
                _str = nullptr;
                _size = _capacity = 0;
            }
        }

        // ==========================================
        // 2. 迭代器
        // ==========================================
        iterator begin() { return _str; }
        iterator end() { return _str + _size; }
        const_iterator begin() const { return _str; }
        const_iterator end() const { return _str + _size; }

        // ==========================================
        // 3. 容量与状态
        // ==========================================
        size_t size() const { return _size; }
        size_t length() const { return _size; } // 兼容标准库
        size_t capacity() const { return _capacity; }
        bool empty() const { return _size == 0; }

        // 清空内容但不释放空间
        void clear()
        {
            _size = 0;
            _str[0] = '\0';
        }

        // 预留空间 (扩容)
        void reserve(size_t n)
        {
            if (n > _capacity)
            {
                char *tmp = new char[n + 1];
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;
                _capacity = n;
            }
        }

        // 调整大小
        void resize(size_t n, char ch = '\0')
        {
            if (n <= _size)
            {
                _size = n;
                _str[_size] = '\0';
            }
            else
            {
                reserve(n);
                for (size_t i = _size; i < n; ++i)
                {
                    _str[i] = ch;
                }
                _size = n;
                _str[_size] = '\0';
            }
        }

        // ==========================================
        // 4. 数据访问
        // ==========================================
        const char *c_str() const { return _str; }

        char &operator[](size_t pos)
        {
            assert(pos < _size);
            return _str[pos];
        }
        const char &operator[](size_t pos) const
        {
            assert(pos < _size);
            return _str[pos];
        }

        // ==========================================
        // 5. 修改操作 (增删)
        // ==========================================

        // Push Back
        void push_back(char ch)
        {
            if (_size == _capacity)
            {
                reserve(_capacity == 0 ? 4 : _capacity * 2);
            }
            _str[_size] = ch;
            _size++;
            _str[_size] = '\0';
        }

        // Append
        void append(const char *str)
        {
            size_t len = strlen(str);
            if (_size + len > _capacity)
            {
                reserve(_size + len);
            }
            strcpy(_str + _size, str);
            _size += len;
        }

        // += 重载
        string &operator+=(const string &s)
        {
            append(s.c_str());
            return *this;
        }
        string &operator+=(const char *str)
        {
            append(str);
            return *this;
        }
        string &operator+=(char ch)
        {
            push_back(ch);
            return *this;
        }

        // Insert (字符串)
        void insert(size_t pos, const char *str)
        {
            assert(pos <= _size);
            size_t len = strlen(str);
            if (_size + len > _capacity)
            {
                reserve(_size + len);
            }
            // 从后向前搬移数据
            size_t end = _size;
            while (end >= pos && end != npos)
            {
                _str[end + len] = _str[end];
                if (end == 0)
                    break;
                end--;
            }
            strncpy(_str + pos, str, len);
            _size += len;
        }

        // Insert (字符)
        void insert(size_t pos, char ch)
        {
            insert(pos, 1, ch);
        }

        // Insert (n个字符)
        void insert(size_t pos, size_t count, char ch)
        {
            assert(pos <= _size);
            if (_size + count > _capacity)
            {
                reserve(_size + count);
            }
            size_t end = _size;
            while (end >= pos && end != npos)
            {
                _str[end + count] = _str[end];
                if (end == 0)
                    break;
                end--;
            }
            for (size_t i = 0; i < count; ++i)
            {
                _str[pos + i] = ch;
            }
            _size += count;
        }

        // Erase
        void erase(size_t pos, size_t len = npos)
        {
            assert(pos < _size);
            if (len == npos || pos + len >= _size)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                strcpy(_str + pos, _str + pos + len);
                _size -= len;
            }
        }

        // Swap
        void swap(string &s)
        {
            std::swap(_str, s._str);
            std::swap(_size, s._size);
            std::swap(_capacity, s._capacity);
        }

        // ==========================================
        // 6. 查找与子串
        // ==========================================

        // Find (子串)
        size_t find(const char *str, size_t pos = 0) const
        {
            assert(pos <= _size);
            const char *ptr = strstr(_str + pos, str);
            if (ptr)
            {
                return ptr - _str;
            }
            return npos;
        }

        // Find (字符)
        size_t find(char ch, size_t pos = 0) const
        {
            assert(pos <= _size);
            for (size_t i = pos; i < _size; ++i)
            {
                if (_str[i] == ch)
                    return i;
            }
            return npos;
        }

        // Substr (截取子串)
        string substr(size_t pos = 0, size_t len = npos) const
        {
            assert(pos <= _size);
            size_t real_len = len;
            if (len == npos || pos + len > _size)
            {
                real_len = _size - pos;
            }

            string sub;
            sub.reserve(real_len);
            strncpy(sub._str, _str + pos, real_len);
            sub._size = real_len;
            sub._str[sub._size] = '\0';

            return sub;
        }

        // ==========================================
        // 7. 比较运算符重载
        // ==========================================
        bool operator<(const string &s) const { return strcmp(_str, s._str) < 0; }
        bool operator>(const string &s) const { return strcmp(_str, s._str) > 0; }
        bool operator==(const string &s) const { return strcmp(_str, s._str) == 0; }
        bool operator>=(const string &s) const { return !(*this < s); }
        bool operator<=(const string &s) const { return !(*this > s); }
        bool operator!=(const string &s) const { return !(*this == s); }

    private:
        char *_str;
        size_t _size;
        size_t _capacity;
    };

    // ==========================================
    // 8. 全局运算符重载 (非成员函数)
    // ==========================================

    // operator+
    string operator+(const string &s1, const string &s2)
    {
        string ret(s1);
        ret += s2;
        return ret;
    }

    // operator<< (流输出)
    std::ostream &operator<<(std::ostream &out, const string &s)
    {
        for (auto ch : s)
        {
            out << ch;
        }
        return out;
    }

    // operator>> (流提取)
    std::istream &operator>>(std::istream &in, string &s)
    {
        s.clear();
        char ch;
        // 跳过前导空白
        while ((ch = in.get()) && isspace(ch))
        {
        }

        if (in)
        {
            char buff[128];
            size_t i = 0;
            buff[i++] = ch;

            while ((ch = in.get()) && !isspace(ch))
            {
                buff[i++] = ch;
                if (i == 127)
                {
                    buff[i] = '\0';
                    s += buff;
                    i = 0;
                }
            }
            if (i > 0)
            {
                buff[i] = '\0';
                s += buff;
            }
        }
        return in;
    }
}