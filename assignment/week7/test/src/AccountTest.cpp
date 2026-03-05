#include "AccountTest.h"

TEST_P(AccountDepositInvalidAmountFixture, Deposit_WhenAmountIsZeroOrNegative_ThenOperationFails)
{
    ASSERT_NE(accountZero_, nullptr);

    EXPECT_FALSE(accountZero_->deposit(GetParam()));
    EXPECT_DOUBLE_EQ(accountZero_->getBalance(), zeroBalance_);
}

INSTANTIATE_TEST_SUITE_P(
    AccountInvalidDepositAmounts,
    AccountDepositInvalidAmountFixture,
    ::testing::Values(0.0, -10.0, -5.0)
);

TEST_F(AccountFixture, Deposit_WhenAmountIsPositive_ThenBalanceIsIncreased)
{
    ASSERT_NE(accountZero_, nullptr);

    EXPECT_TRUE(accountZero_->deposit(100.0));
    EXPECT_DOUBLE_EQ(accountZero_->getBalance(), 100.0);
}

TEST_P(AccountWithdrawInvalidAmountFixture, Withdraw_WhenAmountIsZeroNegativeOrExceedsBalance_ThenOperationFails)
{
    ASSERT_NE(accountWithBalance_, nullptr);

    EXPECT_FALSE(accountWithBalance_->withdraw(GetParam()));
    EXPECT_DOUBLE_EQ(accountWithBalance_->getBalance(), initialBalance_);
}

INSTANTIATE_TEST_SUITE_P(
    AccountInvalidWithdrawAmounts,
    AccountWithdrawInvalidAmountFixture,
    ::testing::Values(0.0, -5.0, 60.0)
);

TEST_F(AccountFixture, Withdraw_WhenAmountIsWithinBalance_ThenBalanceIsDecreased)
{
    ASSERT_NE(accountWithBalance_, nullptr);

    EXPECT_TRUE(accountWithBalance_->withdraw(20.0));
    EXPECT_DOUBLE_EQ(accountWithBalance_->getBalance(), 30.0);
}
