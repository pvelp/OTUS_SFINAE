#include <iostream>
#include <type_traits>
#include <vector>
#include <list>


template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(const T& ip) {
    for (int i = sizeof(T) - 1; i > -1; --i) {
        std::cout << ((ip >> i * 8) & 0xFF);
        if (i != 0){
        std::cout << ".";
        }
    }
    std::cout << std::endl;
}


template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_ip(const T& ip) {
    std::cout << ip << std::endl;
}


template <template<typename, typename...> class Container, typename T, typename... Args>
typename std::enable_if<std::is_same<Container<T, Args...>, std::vector<T, Args...>>::value ||
                        std::is_same<Container<T, Args...>, std::list<T, Args...>>::value, void>::type
print_ip(const Container<T, Args...>& ip) {
    auto it = ip.begin();
    std::cout << *it;
    ++it;
    while (it != ip.end()) {
        std::cout << "." << *it;
        ++it;
    }
    std::cout << std::endl;
}


int main() {
    print_ip(2130706433);  // 127.0.0.1
    std::string tmp = "192.168.1.1";
    print_ip(tmp);
    std::vector<int> v = {192, 168, 1, 1};
    print_ip(v);
    std::list<int> l = {192, 168, 1, 1};
    print_ip(l);
    return 0;
}
