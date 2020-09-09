// Copyright 2020 Alexander <scorpy2013@gmail.com>

#include <gtest/gtest.h>

TEST(Json, Example)
{
    Json object = Json::parse(R"(
    {
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
}
    )");
   // ?????????????????????????????????????????????????????????????
    EXPECT_EQ(any_cast<std::string>(object["lastname"]), "Ivanov");
    EXPECT_EQ(any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(any_cast<double>(object["age"]), 25);

    Json marks = any_cast<Json>(object["marks"]);
    EXPECT_EQ(any_cast<double>(marks[0]), 4);
    EXPECT_EQ(any_cast<double>(marks[1]), 5);

    Json address = any_cast<Json>(object["address"]);
    EXPECT_EQ(any_cast<std::string>(address["city"]), "Moscow");
    EXPECT_EQ(any_cast<std::string>(address["street"]), "Vozdvijenka");
}
