/**
 * @file ScoreboardTest.cpp
 * @author popov
 */
// ScoreboardTest.cpp

#include <pch.h>
#include <gtest/gtest.h>
#include <Scoreboard.h>


class ScoreboardTest : public testing::Test {
protected:
    /// Declare
    Scoreboard scoreboard;
};

TEST_F(ScoreboardTest, DefaultConstructor) {
    // Test the default constructor of the Scoreboard class.
    // You can use ASSERT_EQ to check if the initial elapsed time is 0.
    ASSERT_EQ(0, scoreboard.GetElapsedSeconds());
}

TEST_F(ScoreboardTest, ResetTimer) {
    // Test the ResetTimer function of the Scoreboard class.
    // After resetting the timer, the elapsed time should be 0.
    scoreboard.ResetTimer();
    ASSERT_EQ(0, scoreboard.GetElapsedSeconds());
}

TEST_F(ScoreboardTest, Tick) {
    // Test the Tick function of the Scoreboard class.
    // After ticking for a certain amount of time, the elapsed time should increase accordingly.

    // For example, ticking for 2 seconds.
    double elapsed = 2.0;
    scoreboard.Tick(elapsed);
    ASSERT_EQ(elapsed, scoreboard.GetElapsedSeconds());

    // Ticking for additional 3 seconds.
    elapsed = 5.0;
    scoreboard.Tick(3.0);
    ASSERT_EQ(elapsed, scoreboard.GetElapsedSeconds());
}