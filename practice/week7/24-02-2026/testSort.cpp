#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include <functional>
#include <map>
#include "sorter.h"

std::map<std::string, std::vector<int>> input_map = {
    {"Empty", {}},
    {"SingleElement", {1}},
    {"Reverse", {5,4,3,2,1}},
    {"SmallVector", {5,3,1,7}}
};


std::map<std::string, std::function<void(std::vector<int>&)>> function_map = {
    {"BubbleSort", bubbleSort},
    {"SelectionSort", selectionSort}
};


class SortTest : public testing::TestWithParam<
    std::tuple<
        std::pair<const std::string, std::function<void(std::vector<int>&)>>,
        std::pair<const std::string, std::vector<int>>
    >> {};


TEST_P(SortTest, WorksForVariousInputs) {
    auto param = GetParam();

    auto sortFunction = std::get<0>(param).second;
    auto input = std::get<1>(param).second;

    auto expected = input;
    std::sort(expected.begin(), expected.end());

    sortFunction(input);

    EXPECT_EQ(input, expected);
}


INSTANTIATE_TEST_SUITE_P(
    SelectionSortBubbleSort,
    SortTest,
    testing::Combine(
        testing::ValuesIn(function_map),
        testing::ValuesIn(input_map)
    ),
    [](const testing::TestParamInfo<SortTest::ParamType>& info) {
        return std::get<0>(info.param).first + "_" +
               std::get<1>(info.param).first;
    }
);
