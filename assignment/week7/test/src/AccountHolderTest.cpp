#include "AccountHolderTest.h"

TEST_F(AccountHolderFixture, Constructor_WhenObjectIsCreated_ThenAccountIsNotNull)
{
    ASSERT_NE(accountHolder, nullptr);
    ASSERT_NE(accountHolder->getAccount(), nullptr);
}

TEST_F(AccountHolderFixture, Constructor_WhenObjectIsCreated_ThenAccountNumberIsSetCorrectly)
{
    ASSERT_NE(accountHolder->getAccount(), nullptr);
    EXPECT_EQ(accountHolder->getAccount()->getAccountNumber(), accountNumber);
}

TEST_F(AccountHolderFixture, Constructor_WhenObjectIsCreated_ThenInitialBalanceIsSetCorrectly)
{
    ASSERT_NE(accountHolder->getAccount(), nullptr);
    EXPECT_DOUBLE_EQ(accountHolder->getAccount()->getBalance(), initialBalance);
}

TEST_F(AccountHolderFixture, Deposit_WhenAmountIsPositive_ThenBalanceIsIncreased)
{
    ASSERT_NE(accountHolder->getAccount(), nullptr);

    EXPECT_TRUE(accountHolder->getAccount()->deposit(200.0));
    EXPECT_DOUBLE_EQ(accountHolder->getAccount()->getBalance(), 1200.0);
}

TEST_P(AccountHolderDepositInvalidAmountFixture, Deposit_WhenAmountIsZeroOrNegative_ThenOperationFails)
{
    ASSERT_NE(accountHolder->getAccount(), nullptr);

    EXPECT_FALSE(accountHolder->getAccount()->deposit(GetParam()));
    EXPECT_DOUBLE_EQ(accountHolder->getAccount()->getBalance(), initialBalance);
}

INSTANTIATE_TEST_SUITE_P(
    AccountHolderInvalidDepositAmounts,
    AccountHolderDepositInvalidAmountFixture,
    ::testing::Values(0.0, -5.0, -10.0)
);

TEST_F(AccountHolderFixture, Withdraw_WhenAmountIsWithinBalance_ThenBalanceIsDecreased)
{
    ASSERT_NE(accountHolder->getAccount(), nullptr);

    EXPECT_TRUE(accountHolder->getAccount()->withdraw(300.0));
    EXPECT_DOUBLE_EQ(accountHolder->getAccount()->getBalance(), 700.0);
}

TEST_F(AccountHolderFixture, Withdraw_WhenAmountExceedsBalance_ThenOperationFails)
{
    ASSERT_NE(accountHolder->getAccount(), nullptr);

    EXPECT_FALSE(accountHolder->getAccount()->withdraw(2000.0));
    EXPECT_DOUBLE_EQ(accountHolder->getAccount()->getBalance(), initialBalance);
}

TEST_P(AccountHolderWithdrawInvalidAmountFixture, Withdraw_WhenAmountIsZeroOrNegative_ThenOperationFails)
{
    ASSERT_NE(accountHolder->getAccount(), nullptr);

    EXPECT_FALSE(accountHolder->getAccount()->withdraw(GetParam()));
    EXPECT_DOUBLE_EQ(accountHolder->getAccount()->getBalance(), initialBalance);
}

INSTANTIATE_TEST_SUITE_P(
    AccountHolderInvalidWithdrawAmounts,
    AccountHolderWithdrawInvalidAmountFixture,
    ::testing::Values(0.0, -10.0, -1.0)
);
