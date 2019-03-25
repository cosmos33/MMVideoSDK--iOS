/**
 * on 2018/2/8.
 *
 * @author chen.weiwei
 */

#ifndef XESCONVERTSTRING_H
#define XESCONVERTSTRING_H

#include <string>
#include <sstream>

using namespace std;
namespace std {
    template<typename T>
    std::string to_string(const T &n) {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}
#endif /* #end XESCONVERTSTRING_H */
