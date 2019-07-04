#pragma once

template<typename T>
void print_info(const int rank, const T message) {
    std::cout << "[\033[36mINFO\033[0m] : " << rank << " -> " << message << std::endl;
}

template<typename T>
void print_error(const int rank, const T message) {
    std::cerr << "[\033[31mERROR\033[0m] : " << rank << " -> " << message << std::endl;
}

template<typename T>
void print_warning(const int rank, const T message) {
    std::cout << "[\033[35mWARNING\033[0m] : " << rank << " -> " << message << std::endl;
}
