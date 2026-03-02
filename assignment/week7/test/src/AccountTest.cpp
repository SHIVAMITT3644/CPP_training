#include "AccountTest.h"

TEST_P(AccountDepositInvalidAmountFixture, Deposit_WhenAmountIsZeroOrNegative_ThenOperationFails)
{
    ASSERT_NE(accountZero, nullptr);

    EXPECT_FALSE(accountZero->deposit(GetParam()));
    EXPECT_DOUBLE_EQ(accountZero->getBalance(), zeroBalance);
}

INSTANTIATE_TEST_SUITE_P(
    AccountInvalidDepositAmounts,
    AccountDepositInvalidAmountFixture,
    ::testing::Values(0.0, -10.0, -5.0)
);

TEST_F(AccountFixture, Deposit_WhenAmountIsPositive_ThenBalanceIsIncreased)
{
    ASSERT_NE(accountZero, nullptr);

    EXPECT_TRUE(accountZero->deposit(100.0));
    EXPECT_DOUBLE_EQ(accountZero->getBalance(), 100.0);
}

TEST_P(AccountWithdrawInvalidAmountFixture, Withdraw_WhenAmountIsZeroNegativeOrExceedsBalance_ThenOperationFails)
{
    ASSERT_NE(accountWithBalance, nullptr);

    EXPECT_FALSE(accountWithBalance->withdraw(GetParam()));
    EXPECT_DOUBLE_EQ(accountWithBalance->getBalance(), initialBalance);
}

INSTANTIATE_TEST_SUITE_P(
    AccountInvalidWithdrawAmounts,
    AccountWithdrawInvalidAmountFixture,
    ::testing::Values(0.0, -5.0, 60.0)
);

TEST_F(AccountFixture, Withdraw_WhenAmountIsWithinBalance_ThenBalanceIsDecreased)
{
    ASSERT_NE(accountWithBalance, nullptr);

    EXPECT_TRUE(accountWithBalance->withdraw(20.0));
    EXPECT_DOUBLE_EQ(accountWithBalance->getBalance(), 30.0);
}
