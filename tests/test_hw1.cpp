#include <gtest/gtest.h>

#include <string>

#include "analysis.h"
#include "grid.h"
#include "station.h"

TEST(GridIndexTest, ComputesRowMajorIndexWithoutBoundsChecking) {
    EXPECT_EQ(grid_index(1, 2, 3), 5);
    EXPECT_EQ(grid_index(2, 0, 3), 6);
}

TEST(InBoundsTest, AcceptsLastValidCell) {
    EXPECT_TRUE(in_bounds(1, 2, 2, 3));
}

TEST(InBoundsTest, RejectsNegativeAndFirstInvalidIndices) {
    EXPECT_FALSE(in_bounds(-1, 0, 2, 3));
    EXPECT_FALSE(in_bounds(0, -1, 2, 3));
    EXPECT_FALSE(in_bounds(2, 0, 2, 3));
    EXPECT_FALSE(in_bounds(0, 3, 2, 3));
}

TEST(InBoundsTest, RejectsEmptyDimensions) {
    EXPECT_FALSE(in_bounds(0, 0, 0, 3));
    EXPECT_FALSE(in_bounds(0, 0, 2, 0));
}

TEST(StationAverageTest, AveragesOneRow) {
    const double temps[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double average = -1.0;

    ASSERT_TRUE(station_average(temps, 2, 3, 1, average));
    EXPECT_DOUBLE_EQ(average, 5.0);
}

TEST(StationAverageTest, FailureLeavesAverageUnchanged) {
    const double temps[] = {1.0, 2.0, 3.0, 4.0};
    double average = 42.0;

    EXPECT_FALSE(station_average(temps, 2, 2, -1, average));
    EXPECT_DOUBLE_EQ(average, 42.0);
    EXPECT_FALSE(station_average(temps, 2, 2, 2, average));
    EXPECT_DOUBLE_EQ(average, 42.0);
    EXPECT_FALSE(station_average(temps, 2, 0, 0, average));
    EXPECT_DOUBLE_EQ(average, 42.0);
}

TEST(DayAverageTest, AveragesOneColumn) {
    const double temps[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    double average = -1.0;

    ASSERT_TRUE(day_average(temps, 2, 3, 1, average));
    EXPECT_DOUBLE_EQ(average, 3.5);
}

TEST(DayAverageTest, FailureLeavesAverageUnchanged) {
    const double temps[] = {1.0, 2.0, 3.0, 4.0};
    double average = 42.0;

    EXPECT_FALSE(day_average(temps, 2, 2, -1, average));
    EXPECT_DOUBLE_EQ(average, 42.0);
    EXPECT_FALSE(day_average(temps, 2, 2, 2, average));
    EXPECT_DOUBLE_EQ(average, 42.0);
    EXPECT_FALSE(day_average(temps, 0, 2, 0, average));
    EXPECT_DOUBLE_EQ(average, 42.0);
}

TEST(FindHottestTest, KeepsFirstRowMajorCellWhenValuesTie) {
    const double temps[] = {1.0, 9.0, 2.0, 9.0, 0.0, 9.0};
    int hot_row = -1;
    int hot_col = -1;

    ASSERT_TRUE(find_hottest(temps, 2, 3, hot_row, hot_col));
    EXPECT_EQ(hot_row, 0);
    EXPECT_EQ(hot_col, 1);
}

TEST(FindHottestTest, FailureLeavesCoordinatesUnchanged) {
    const double temps[] = {1.0, 2.0, 3.0, 4.0};
    int hot_row = 7;
    int hot_col = 8;

    EXPECT_FALSE(find_hottest(temps, 0, 2, hot_row, hot_col));
    EXPECT_EQ(hot_row, 7);
    EXPECT_EQ(hot_col, 8);
    EXPECT_FALSE(find_hottest(temps, 2, 0, hot_row, hot_col));
    EXPECT_EQ(hot_row, 7);
    EXPECT_EQ(hot_col, 8);
}

TEST(CountAboveTest, CountsStrictlyGreaterValues) {
    const double temps[] = {95.0, 95.1, 96.0, 94.9};

    EXPECT_EQ(count_above(temps, 2, 2, 95.0), 2);
    EXPECT_EQ(count_above(temps, 2, 2, 96.0), 0);
}

TEST(FindStationTest, ReturnsFirstExactCaseSensitiveMatch) {
    const Station stations[] = {
        {"Denton", 642.0},
        {"Waco", 470.0},
        {"Denton", 700.0},
    };

    EXPECT_EQ(find_station(stations, 3, "Denton"), &stations[0]);
    EXPECT_EQ(find_station(stations, 3, "denton"), nullptr);
    EXPECT_EQ(find_station(stations, 3, "Missing"), nullptr);
    EXPECT_EQ(find_station(stations, 0, "Denton"), nullptr);
}
