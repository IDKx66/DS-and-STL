#include <iostream>
#include "string.hpp"

using namespace idk;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    // 1. 构造与赋值
    idk::string s1("Hello");
    idk::string s2;
    s2 = "World"; // 隐式转换 + 赋值

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    // 2. 拼接
    idk::string s3 = s1 + ", " + s2;
    cout << "s3 (+): " << s3 << endl;

    s1 += " C++";
    cout << "s1 (+=): " << s1 << endl;

    // 3. 扩容测试 (Push Back)
    cout << "Current capacity: " << s1.capacity() << endl;
    for (int i = 0; i < 10; ++i)
        s1.push_back('!');
    cout << "s1 (expanded): " << s1 << endl;
    cout << "New capacity: " << s1.capacity() << endl;

    // 4. 插入与删除
    s3.insert(5, " Beautiful");
    cout << "Insert: " << s3 << endl; // Hello Beautiful, World

    size_t pos = s3.find("Beautiful");
    if (pos != idk::string::npos)
    {
        s3.erase(pos, 10); // 删除 "Beautiful "
        cout << "Erase:  " << s3 << endl;
    }

    // 5. 比较
    if (s1 != s2)
        cout << "s1 is not equal to s2" << endl;

    // 6. Substr
    idk::string sub = s3.substr(0, 5);
    cout << "Substr: " << sub << endl;

    // 7. 迭代器遍历
    cout << "Iterator: ";
    for (auto ch : sub)
    {
        cout << ch << ".";
    }
    cout << endl;

    // 8. 调整大小
    sub.resize(10, 'x');
    cout << "Resize(10, x): " << sub << endl;

    return 0;
}