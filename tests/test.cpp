// Copyright 2020 Alexander <scorpy2013@gmail.com>

#include <gtest/gtest.h>

TEST(Json, Example1)
{
   Json object("{\"name\" : \"Sidorov Ivan\",\"group\" : 31,\"avg\" : 4,\"debt\" : \"C++\"}");
    EXPECT_EQ(any_cast<std::string>(object["name"]), "Sidorov Ivan");
    EXPECT_EQ(any_cast<int>(object["group"]), 31);
    EXPECT_EQ(any_cast<int>(object["avg"]), 4);
    EXPECT_EQ(any_cast<std::string>(object["debt"]), "C++ ");
}
TEST(Json, Example2)
{
    Json object("{\"name\": \"Ivanov Petr\", \"group\": 1, \"avg\": 4.25, \"debt\": \"null\"}");
    EXPECT_EQ(std::any_cast<std::string>(object["name"]), "Ivanov Petr");
    EXPECT_EQ(any_cast<int>(object["group"]), 1);
    EXPECT_EQ(any_cast<int>(object["avg"]), 4.25);
    EXPECT_EQ(any_cast<std::string>(object["debt"]), "null");
} 
TEST(Json, Example3)
{
   Json object("{\"name\" : \"Pertov Nikita\",\"group\" : \"IU8-31\",\"avg\" : 3.33,\"debt\" :  [\"C++\", \"Linux\", \"Network\"]}");
    EXPECT_EQ(any_cast<std::string>(object["name"]), "Pertov Nikita");
    EXPECT_EQ(any_cast<std::string>(object["group"]), "IU8-31");
    EXPECT_EQ(any_cast<int>(object["avg"]), 3.33
    Json debts = std::any_cast<Json >(object["debt"]);
    EXPECT_EQ(std::any_cast<std::string>(debts[0]), "C++");
    EXPECT_EQ(std::any_cast<std::string>(debts[1]), "Linux");
    EXPECT_EQ(std::any_cast<std::string>(debts[2]), "Network");
}
