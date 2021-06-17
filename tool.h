#ifndef TOOL_H
#define TOOL_H

#include <sstream>
class Tool
{
public:
    Tool();

    //字符型转数字型
    template <typename T>
    static T String2Num(const std::string& str)
    {
        std::istringstream iss(str);
        T ret;
        iss >> ret;
        return ret;
    }
};


#endif // TOOL_H
