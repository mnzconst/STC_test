#include "moving_average.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

template<class T>
void print_vector(std::vector<T> const &v) {
    for (T val: v) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

template<class T>
void solve(int lower_bound, int upper_bound, size_t number_of_samples, std::string const &datatype) {
    std::vector<T> vec = generate_random_samples<T>(lower_bound, upper_bound, number_of_samples);

    std::vector<size_t> window_sizes = {4, 8, 16, 32, 64, 128};
    for (size_t size: window_sizes) {
//        std::cout << "size: " << size << std::endl;
        auto start = std::chrono::steady_clock::now();
        std::vector<T> v = simple_moving_average(vec, size);
        auto end = std::chrono::steady_clock::now();
        std::cout
//        << "Performance: "
                  << number_of_samples / std::chrono::duration<double>(end - start).count()
                  << std::endl;
//        print_vector(v);
        std::ofstream outfile("../output_files/output_" + datatype + std::to_string(size) + ".txt");
        for (T it : v) {
            outfile << it << " ";
        }
        outfile.close();
    }
}

int main() {
    size_t number_of_samples = 1000000;
    int lower_bound = -100;
    int upper_bound = 100;

    solve<double>(lower_bound, upper_bound, number_of_samples, "double");
    solve<float>(lower_bound, upper_bound, number_of_samples, "float");
}
