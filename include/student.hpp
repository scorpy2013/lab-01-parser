//
// Created by alexscorpy on 18.09.2020.
//


#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <any>
#include <exception>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
class Student
{
 private:
  std::string Name; // фамилия и имя студента (строчный тип)
  std::any Group; // номер группы (строчный/целочисленный тип)
  double Avg = 0; // средний балл (строчный/целочисленный/вещественный тип)
  std::any Debt; // список задолженностей (строчный/перечислительный тип)
 public:
  Student(); // конструктор по умолчанию
  explicit Student(const json &object); // конструктор для инициализации полей
  // "геттеры" для реализации инкапсуляции
  [[nodiscard]]const std::string &getName() const;
  [[nodiscard]]const std::any &getGroup() const;
  [[nodiscard]]double getAvg() const;
  [[nodiscard]]const std::any &getDebt() const;
  // "сеттеры" для реализации икапсуляции
  void setName(const json &name);
  void setGroup(const json &group);
  void setAvg(const json &avg);
  void setDebt(const json &debt);
  // собственная реализация функции,
  // переводящей текст из json файла в нормальный вид
};
// реализация функции, предложенной в задании
void from_json(const json& j, Student& s);
#endif  // INCLUDE_STUDENT_HPP_
