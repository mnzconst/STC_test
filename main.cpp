#include "moving_average.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

/*
 * Функция проверки производительности простого скользящего среднего
 * lower_bound - наибольшее значение отсчета
 * upper_bound - наименьшее значение отсчета
 * number_of_samples - количество отсчетов
 * window_width - список размеров окон
 * datatype - литерал для обозначения используемого типа данных
 * logging - флаг, отвечающий за запись данных в файлы, по умолчанию true
 */
template<class T>
void test_performance(int lower_bound,
                      int upper_bound,
                      size_t number_of_samples,
                      std::vector<size_t> const &window_width,
                      std::string const &datatype,
                      bool logging = true) {
    // Генерируем отсчеты
    std::vector<T> vec = generate_random_samples<T, std::normal_distribution<T>>(lower_bound, upper_bound,
                                                                                 number_of_samples);
    // Записываем сгенерированные отсчеты в файл для дальнейшего анализа
    if (logging) {
        std::ofstream file("../output_files/input_" + datatype + ".txt");
        for (T it: vec) {
            file << it << " ";
        }
        file.close();
    }

    for (size_t width: window_width) {
        auto start = std::chrono::steady_clock::now();
        // Вычисляем скользящее среднее
        std::vector<T> v = simple_moving_average(vec, width);
        auto end = std::chrono::steady_clock::now();
        std::cout << "Performance for type " << datatype << ", window width " << width << ": "
                  << std::setprecision(10) << number_of_samples / std::chrono::duration<double>(end - start).count()
                  << std::endl;

        // Записываем скользящее среднее в файл для дальнейшего анализа
        if (logging) {
            std::ofstream file{"../output_files/output_" + datatype + std::to_string(width) + ".txt"};
            for (T it: v) {
                file << it << " ";
            }
            file.close();
        }
    }
}

int main() {
    // Задаем параметры для генерации отсчетов
    size_t number_of_samples = 1000000; // Количество отсчетов
    int lower_bound = -100; // Наименьшее значение отсчета
    int upper_bound = 100; // Наибольшее значение отсчета
    std::vector<size_t> window_width = {4, 8, 16, 32, 64, 128}; // Размеры окон

    test_performance<double>(lower_bound, upper_bound, number_of_samples, window_width, "double");
    test_performance<float>(lower_bound, upper_bound, number_of_samples, window_width, "float");
}
