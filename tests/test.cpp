// Copyright 2020 Alexander <scorpy2013@gmail.com>

#include <gtest/gtest.h>

TEST(Json, Example)
{
   Json object("{\"name\" : \"Sidorov Ivan\",\"group\" : 31,\"avg\" : 4,\"debt\" : \"C++\"}");
    EXPECT_EQ(any_cast<std::string>(object["name"]), "Sidorov Ivan");
    EXPECT_EQ(any_cast<int>(object["group"]), 31);
    EXPECT_EQ(any_cast<int>(object["avg"]), 4);
    EXPECT_EQ(any_cast<std::string>(object["debt"]), "C++ ");
}
TEST(Json, ExampleJson)
{
    Json object("{\"lastname\" : \"Ivanov\",\"firstname\" : \"Ivan\",\"age\" : 25,\"islegal\" : false,\"marks\" : [4,5,5,5,2,3],\"address\" : {\"city\" : \"Moscow\",\"street\" : \"Vozdvijenka\"}}");

    EXPECT_EQ(std::any_cast<std::string>(object["lastname"]), "Ivanov");
    EXPECT_EQ(std::any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(std::any_cast<double>(object["age"]), 25);

    Json marks = std::any_cast<Json >(object["marks"]);
    EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
    EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

    Json address = std::any_cast<Json >(object["address"]);
    EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
    EXPECT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");
}
