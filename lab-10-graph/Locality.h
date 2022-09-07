#pragma once
#include <iostream>
#include <cstring>

/*
 * Населенный пункт.
 */
class Locality {
    char* _city;//Название населенного пункта.
    size_t _count;//Количество жителей.
    static const size_t MAX_COUNT = 24256800;

public:

    /*
     * Конструктор по умолчанию.
     */
    Locality() : _city(nullptr), _count(0) { ; }

    /*
     * Конструктор с параметрами.
     *
     *@param city Название населенного пункта.
     *@param count Количество жителей.
     */
    explicit Locality(const char* city, size_t count);


    /*
     * Запрещенный конструктор копирования.
     */
    Locality(const Locality& rhs) = delete;

    /*
     * Запрешенный оператор присваивания копированием.
     */
    Locality& operator=(const Locality& rhs) = delete;

    /*
     * Узнать имя населенного пункта.
     *
     *@return Название населенного пункта.
     */
    [[nodiscard]] char* getCity() const {
        return _city;
    }

    /*
     * Узнать количество жителей.
     *
     *@return Количество жителей.
     */
    [[nodiscard]] size_t getCount() const {
        return _count;
    }


    /*
     * Деструктор.
     */
    ~Locality();

};
/*
 * Перегруженный оператор вывода.
 */
std::ostream& operator<< (std::ostream&, const Locality*);
/*
 * Перегруженный оператор вывода.
 */
std::ostream& operator<< (std::ostream&, const Locality&);