// Copyright [year] <Copyright Owner>
#include "student.hpp"

#include <iostream>
using nlohmann::json;
// Student::Student() {};
Student::Student() = default;
Student::Student(const json &object) {
  // проверка объекта на наличие
  if (object.empty()) {
    throw std::invalid_argument("Object is empty!");
  }
  // возвращаем строку по индексу "имя"
  Name = object.at("name").get<std::string>();
  // возвращаем "группу"
  Group = std::any{object.at("group")};
  // строка/целое число/вещественное число ???
  // проверяем на строчный тип
  if (object.at("avg").is_string()) {
    Avg = std::stod(object.at("avg").get<std::string>());
  }
  // проверяем на целочисленный или вещественный тип
  else if (object.at("avg").is_number()) {
    Avg = object.at("avg").get<double>();
  } else {
    throw std::invalid_argument("The type of the avg is not correct!");
  }
  Debt = std::any{object.at("debt")};
}
// создаем "геттеры"
// возвращаем "имя", "группу", "средний балл" и "долги"
const std::string &Student::getName() const { return Name; }
const std::any &Student::getGroup() const { return Group; }
double Student::getAvg() const { return Avg; }
const std::any &Student::getDebt() const { return Debt; }
// создаем "сеттеры", разбивая тело
// конструктора Student::Student(const json &object)
// устанавливаем "имя", "группу", "средний балл" и "долги"
void Student::setName(const json &name) { Name = name.get<std::string>(); }
void Student::setGroup(const json &group) { Group = std::any{group}; }
void Student::setAvg(const json &avg) {
  // строка/целое число/вещественное число ???
  // проверяем на строчный тип
  if (avg.at("avg").is_string()) {
    Avg = std::stod(avg.at("avg").get<std::string>());
  }
  // проверяем на целочисленный или вещественный тип
  else if (avg.at("avg").is_number()) {
    Avg = avg.at("avg").get<double>();
  } else {
    throw std::invalid_argument("The type of the avg is not correct!");
  }
}
void Student::setDebt(const json &debt) { Debt = std::any{debt}; }
void from_json(const json &j, Student &s) {
  s.setName(j.at("name"));
  s.setGroup(j.at("group"));
  s.setAvg(j.at("avg"));
  s.setDebt(j.at("debt"));
}
