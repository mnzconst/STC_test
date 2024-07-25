#pragma once

#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <concepts>

/*
 * Функция, вычисляющая простое скользящее среднее
 * samples - входные отсчеты
 * window_width - ширина окна
 */
template<std::floating_point T>
std::vector<T> simple_moving_average(std::vector<T> const &samples, size_t window_width) {
    size_t N = 0;
    if (window_width < samples.size()) {
        N = samples.size() - window_width + 1;
    } else {
        N = 1;
    }

    std::vector<T> result(N);
    for (size_t i = 0; i < N; ++i) {
        T value = 0;
        for (size_t j = i; j < i + window_width; ++j) {
            value += samples[j];
        }
        result[i] = value / window_width;
    }
    return result;
}

/*
 * Функция, генерирующая случайные отсчеты
 * T - тип данных
 * Distribution - тип распределения
 * lower_bound - наименьшее значение
 * upper_bound - наибольшее значение
 * size - размер выборки
 */
template<class T,
        class Distribution = std::uniform_real_distribution<T>>
std::vector<T> generate_random_samples(T lower_bound, T upper_bound, size_t size) {
    std::random_device rnd_device;
    std::mt19937 mt {rnd_device()};
    Distribution distribution {lower_bound, upper_bound};

    auto gen = [&]() {
        return distribution(mt);
    };
    std::vector<T> vec(size);
    std::generate(vec.begin(), vec.end(), gen);
    return vec;
}

