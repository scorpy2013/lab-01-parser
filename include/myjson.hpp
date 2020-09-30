//
// Created by alexscorpy on 18.09.2020.
//
/*
| name          | group  | avg  | debt          |
|---------------|--------|------|---------------|
| Ivanov Petr   | 1      | 4.25 | null          |
|---------------|--------|------|---------------|
| Sidorov Ivan  | 31     | 4.00 | C++           |
|---------------|--------|------|---------------|
| Pertov Nikita | IU8-31 | 3.33 | 3 items       |
|---------------|--------|------|---------------|
 */
#ifndef TEMPLATE_MYJSON_HPP
#define TEMPLATE_MYJSON_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "student.hpp"

struct lengths_of_fields
{
  size_t length_for_name; // длина строчки для name
  size_t length_for_group; // длина строчки для group
  size_t length_for_avg; // длина строчки для avg
  size_t length_for_debt; // длина строчки для debt
};
class MyJson
{
 private:
 void set_lengths_of_fields(); // установка длин полей
 public:
  std::vector<Student> students; // вектор студентов
  // изначальная длина полей для имени, группы, среднего балла и долгов
  lengths_of_fields length{15, 8, 6, 15};
  MyJson();
  // конструктор для строки объекта json файла
  explicit MyJson(const std::string &jsonPath);
  ~MyJson(); // деструктор
  // выводим длины полей
  [[nodiscard]] const lengths_of_fields &get_length() const;
  void print_one_line(const Student &student) const; // рисуем 1 строчку в таблице
  [[nodiscard]] std::string get_one_split() const; // создаем универсальный разделитель в таблице
  void parser(const std::string &jsonPath); // функция "парсинга"
  void set_json(const std::string &JSON); // "сеттер" для строки json файла
};
#endif  // TEMPLATE_MYJSON_HPP

