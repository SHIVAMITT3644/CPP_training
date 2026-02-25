#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace testing;

// Custom struct
struct Person {
    std::string name;
    int age;

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

TEST(ContainerMatchersTest, CompleteExample)
{

    std::vector<int> v1 = {1, 2, 3};
    EXPECT_THAT(v1, ElementsAre(1, 2, 3));

    std::vector<int> v2 = {3, 1, 2};
    EXPECT_THAT(v2, UnorderedElementsAre(1, 2, 3));


    std::vector<int> v3 = {5, 2, 4, 1, 3};
    EXPECT_THAT(v3, WhenSorted(ElementsAre(1, 2, 3, 4, 5)));


    EXPECT_THAT(v3,
        WhenSortedBy(std::greater<int>(),
            ElementsAre(5, 4, 3, 2, 1)));


    std::map<int, std::string> m = {
        {2, "two"},
        {1, "one"}
    };

    EXPECT_THAT(m, ElementsAre(
        Pair(1, "one"),
        Pair(2, "two")
    ));


    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 20},
        {"Charlie", 25}
    };

    EXPECT_THAT(people,
        WhenSortedBy(
            [](const Person& a, const Person& b) {
                return a.age < b.age;
            },
            ElementsAre(
                Person{"Bob", 20},
                Person{"Charlie", 25},
                Person{"Alice", 30}
            )
        ));
}