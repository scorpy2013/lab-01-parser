//
// Created by alexscorpy on 18.09.2020.
//
#include <myjson.hpp>
#include <algorithm>
// MyJson::MyJson() {};
MyJson::MyJson() = default;
std::string MyJson::get_one_split() const
{
  // получаем строчку типа |---------|---------|---------|---------|
  std::string  split = "|";
  // с помощью циклов добавляем к строчке символы "|" и "-"
  for (size_t i = 0; i < length.length_for_name; ++i)
  {
    split += "-";
  }
  split += "|";
  for (size_t i = 0; i < length.length_for_group; ++i)
  {
    split += "-";
  }
  split += "|";
  for (size_t i = 0; i < length.length_for_avg; ++i)
  {
    split += "-";
  }
  split += "|";
  for (size_t i = 0; i < length.length_for_debt; ++i)
  {
    split += "-";
  }
  split += "|";
  return split;
}
void MyJson::set_lengths_of_fields()
{
  for (const auto &student : students)
  {
    // каждый раз измеряем длину поля, и если оно больше начального
    // значения, то это значение увеличивается на 1
    if (student.getName().size() > length.length_for_name)
    {
      // если длина имени больше длины поля "имя", то увеличиваем длину этого поля
      length.length_for_name = student.getName().size() + 1;
    }
    // проверяем на целочисленный тип
    if (std::any_cast<json>(student.getGroup()).is_number())
    {
      if (std::to_string(std::any_cast<json>(student.getGroup()).get<int>()).size() > length.length_for_group)
      {
        // если длина имени больше длины поля "группа", то увеличиваем длину этого поля
        length.length_for_group = std::to_string(std::any_cast<json>(student.getGroup()).get<int>()).size() + 1;
      }
    } else
    {
      if (std::any_cast<json>(student.getGroup()).get<std::string>().size() > length.length_for_group)
      {
        length.length_for_group = std::any_cast<json>(student.getGroup()).get<std::string>().size() + 1;
      }
    }
    if (std::any_cast<json>(student.getDebt()).is_string() &&
        std::any_cast<json>(student.getDebt()).get<std::string>().size() > length.length_for_debt)
    {
      length.length_for_debt = std::any_cast<json>(student.getDebt()).get<std::string>().size() + 1;
    }
  }
}
//--------------------------------------------------------------------------------
void MyJson::print_one_line(const Student &student) const
{
  // рисуем 1 линию в таблице, например
  // | Sidorov Ivan  | 31     | 4.00 | C++           |
  // с помощью left делаем выравнивание по левому краю
  // с помощью setw устанавливаем дистанцию
  std::cout << std::left << "|" << std::setw(length.length_for_name) << student.getName() << "|";
  // проверяем на целочисленный тип
  if (std::any_cast<json>(student.getGroup()).is_number())
  {
    std::cout << std::setw(length.length_for_group) << std::any_cast<json>(student.getGroup()).get<int>();
  } // проверяем на строковое значение
  else if (std::any_cast<json>(student.getGroup()).is_string())
  {
    std::cout << std::setw(length.length_for_group) << std::any_cast<json>(student.getGroup()).get<std::string>();
  } else
  {
    throw std::invalid_argument("The type of the group is not correct!");
  }
  // setprecision установит кол-во знаков после точки
  std::cout << "|" << std::setprecision(3) << std::setw(length.length_for_avg) << student.getAvg() << "|";
  // если долгов нет, то пишем "null"
  if (std::any_cast<json>(student.getDebt()).is_null())
  {
    std::cout << std::setw(length.length_for_debt) << "null";
  } // если долги являются массивом предметов, то
    // с помощью итератора выводим размер нашего вектора
  else if (std::any_cast<json>(student.getDebt()).is_array())
  {
    std::string it = std::to_string(std::any_cast<json>(student.getDebt()).get<std::vector<std::string>>().size()) + " items";
    std::cout << std::setw(length.length_for_debt) << it;
  } // проверяем на строковое значение
  else if (std::any_cast<json>(student.getDebt()).is_string())
  {
    std::cout << std::setw(length.length_for_debt) << std::any_cast<json>(student.getDebt()).get<std::string>();
  } else
  {
    throw std::invalid_argument("The type of the debt is not correct!");
  }
  std::cout << "|";
}
//------------------------------------------------------------------------------
MyJson::MyJson(const std::string &jsonPath)
{
  if (jsonPath.empty())
  {
    throw std::invalid_argument("The file is empty!");
  }
  std::ifstream json_file(jsonPath);
  if (!json_file.is_open())
  {
    throw std::out_of_range("unable to open json: " + jsonPath);
  }
  json data;
  json_file >> data;
  if (!data.at("items").is_array())
  {
    throw std::invalid_argument("Items are not array!");
  }
  // сравниваем кол-во студентов и "_meta"
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>())
  {
    throw std::invalid_argument("Items length don't equal _meta.count!!!");
  }
  for (auto const &student : data.at("items"))
  {
    students.emplace_back(student);
    // students.push_back(student);
    // emplace_back создает объект непосредственно в конце вектора,
    // т.е. без лишнего копирования (или перемещения)
  }
  set_lengths_of_fields();
}

//------------------------------------------------------------------------------
void MyJson::parser(const std::string &jsonPath)
{ // строим ВСЮ ТАБЛИЦУ вместе со значениями
  if (jsonPath.empty())
  {
    throw std::invalid_argument("The file is empty!");
  }
  std::ifstream json_file(jsonPath);
  if (!json_file.is_open())
  {
    throw std::out_of_range("unable to open json: " + jsonPath);
  }
  json data;
  json_file >> data;
  if (!data.at("items").is_array())
  {
    throw std::invalid_argument("Items are not array!");
  }
  // сравниваем кол-во студентов и "_meta"
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>())
  {
    throw std::invalid_argument("Items length don't equal _meta.count!!!");
  }
  for (auto const &student : data.at("items"))
  {
    students.emplace_back(student);
    // students.push_back(student);
    // emplace_back создает объект непосредственно в конце вектора,
    // т.е. без лишнего копирования (или перемещения)
  }
  set_lengths_of_fields();
  // рисуем | name          | group  | avg  | debt          |
  std::cout << std::left << "|" << std::setw(length.length_for_name) << "name"
            << "|" << std::setw(length.length_for_group) << "group"
            << "|" << std::setw(length.length_for_avg) << "avg"
            << "|" << std::setw(length.length_for_debt) << "debt"
            << "|" << '\n';
  // рисуем |---------------|--------|------|---------------|
  std::string split = get_one_split();
  std::cout << split << "\n";
  for (const auto &student : students)
  { // рисуем | Ivanov Petr   | 1      | 4.25 | null          |
    print_one_line(student);
    std::cout << '\n';
    // рисуем |---------------|--------|------|---------------|
    std::cout << split << "\n";
  }
}
MyJson::~MyJson() {}
