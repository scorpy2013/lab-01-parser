//
// Created by alexscorpy on 28.09.2020.
//
#include "myjson.hpp"
#include <iostream>
using namespace std;
int main()
{
  MyJson data;
  std::string JSONFILE(R"({
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
  data.parser(JSONFILE);
  return 0;
}
