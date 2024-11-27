#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    redirect_output_wrapper(std::ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    { 
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }

    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }

    bool GetCondition()
    {
        if (stream.rdbuf() == old_buf)
            return true;
        return false;
    }
};

template <typename T1, typename T2>
using Filter = bool(*)(T1& object, T2 param);

template <typename T1, typename T2>
std::unordered_set<int> FindByFilter(std::unordered_map<int,
    T1>& map, Filter<const T1&, T2> f, T2 param)
{
    std::unordered_set<int> result_set;
    for (auto& [key, object] : map)
    {
        if (f(object, param))
            result_set.insert(key);
    }
    return result_set;
}

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Enter correct number: ";
    }
    std::cerr << x << '\n';
    return x;
}

template <typename T>
std::unordered_set<int> SelectByIDs(const T& objects)
{
    std::unordered_set<int> id_set;
    int id;
    do {
        std::cout << "Enter the id (\"0\" - end): ";
        id = GetCorrectNumber(0, INT_MAX);
        if (objects.contains(id))
            id_set.insert(id);
    } while (id != 0);
    return id_set;
}

template <typename T>
bool ObjectsExist(const T& objects)
{
    if (objects.size() == 0) {
        return false;
    }
    return true;
}

template <typename T>
T Min(T A, T B)
{
    if (A <= B)
        return A;
    else
        return B;
}

std::string EnterLine();
int ChooseActionMenu(std::vector<std::string>& menu, bool with_exit);
