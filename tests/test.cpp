// Copyright 2020 Alexander <scorpy2013@gmail.com>
#include "myjson.hpp"
#include <sstream>
#include <gtest/gtest.h>
#include <fstream>
#include <string>

TEST(MyJson, LengthOfFields)
{
  ASSERT_EQ(MyJson().get_length().length_for_name, 15);
  ASSERT_EQ(MyJson().get_length().length_for_group, 8);
  ASSERT_EQ(MyJson().get_length().length_for_avg, 6);
  ASSERT_EQ(MyJson().get_length().length_for_debt, 15);
  MyJson data;
  data.set_json(R"({
  "items": [
    {
      "name": "Alex Volodin Andreevich",
      "group": "IU8-33 the best group forever",
      "avg": "5.000",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++ Java Python C# Python"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  ASSERT_EQ(data.get_length().length_for_name, 24);
  ASSERT_EQ(data.get_length().length_for_group, 30);
  ASSERT_EQ(data.get_length().length_for_avg, 6);
  ASSERT_EQ(data.get_length().length_for_debt, 26);
}
TEST(MyJson, Null) {
  Student s{json::parse(R"({
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    })")};
  ASSERT_EQ(s.getName(), "Ivanov Petr");
  ASSERT_EQ(std::any_cast<json>(s.getGroup()).get<std::string>(), "1");
  ASSERT_DOUBLE_EQ(s.getAvg(), 4.25);
  ASSERT_TRUE(std::any_cast<json>(s.getDebt()).is_null());
}
TEST(MyJson, OneSubject) {
  Student s{json::parse(R"({
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    })")};
  ASSERT_EQ(s.getName(), "Sidorov Ivan");
  ASSERT_EQ(std::any_cast<json>(s.getGroup()).get<int>(), 31);
  ASSERT_DOUBLE_EQ(s.getAvg(), 4.00);
  ASSERT_TRUE(std::any_cast<json>(s.getDebt()).is_string());
}
TEST(MyJson, Array) {
  Student s{json::parse(R"({
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    })")};
  ASSERT_EQ(s.getName(), "Pertov Nikita");
  ASSERT_EQ(std::any_cast<json>(s.getGroup()).get<std::string>(), "IU8-31");
  ASSERT_DOUBLE_EQ(s.getAvg(), 3.33);
  ASSERT_TRUE(std::any_cast<json>(s.getDebt()).is_array());
}

TEST(MyJson, ExceptionTests)
{
  EXPECT_THROW(MyJson(""), std::invalid_argument);
  EXPECT_THROW(MyJson("Json file which cased an exception!"), std::out_of_range);
  EXPECT_THROW(MyJson().set_json(R"({
  "items":
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    }
}
)"),std::invalid_argument);
  EXPECT_THROW(MyJson().set_json(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 99
  }
})"),std::invalid_argument);
}
TEST(MyJson, OneSplit) {
  std::string s = "|---------------|--------|------|---------------|";
  ASSERT_EQ(MyJson().get_one_split(), s);
}
TEST(MyJson, parser) {
  std::stringstream out;
  MyJson data;
  std::string str(R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})");
  data.set_json(str);
  out << data;
  std::string true(R"(|name           |group     |avg   |debt           |
|---------------|----------|------|---------------|
|Ivanov Petr    |1         |4.25  |null           |
|---------------|----------|------|---------------|
|Sidorov Ivan   |123456789 |4     |C++            |
|---------------|----------|------|---------------|
|Pertov Nikita  |IU8-31    |3.33  |3 items        |
|---------------|----------|------|---------------|
)");
  ASSERT_EQ(out.str(), true);
}

