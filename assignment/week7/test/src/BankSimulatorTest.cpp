#include "BankSimulatorTest.h"

bool performDeposit(User* accountHolderUser, double amount);
bool performWithdrawal(User* accountHolderUser, double amount);

bool createAccountHolderInBank(IBank& bank,
                               const std::string& name,
                               const std::string& userName,
                               const std::string& password,
                               double initialDeposit,
                               int& createdAccountNumber);

bool deleteAccount(IBank& bank, int accountNumber, IBank::RemovalType type);

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

TEST(BankSimulatorUsecaseTests, PerformDeposit_WhenUserIsNull_ThenReturnsFalse)
{
    EXPECT_FALSE(performDeposit(nullptr, 100));
}

TEST(BankSimulatorUsecaseTests, PerformWithdrawal_WhenUserIsNull_ThenReturnsFalse)
{
    EXPECT_FALSE(performWithdrawal(nullptr, 100));
}

TEST_F(BankSimulatorFixture, PerformDeposit_WhenUserIsNotAccountHolder_ThenReturnsFalse)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(0);

    EXPECT_FALSE(performDeposit(&mockUser_, 100));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformDeposit_WhenAccountIsNull_ThenReturnsFalse)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_FALSE(performDeposit(&mockUser_, 100));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformDeposit_WhenUserIsValidAndAmountIsPositive_ThenSucceedsAndBalanceIncreases)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(&account_));

    EXPECT_TRUE(performDeposit(&mockUser_, 100));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 600.0);
}

TEST_F(BankSimulatorFixture, PerformDeposit_WhenAmountIsZero_ThenFailsAndBalanceRemainsSame)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(&account_));

    EXPECT_FALSE(performDeposit(&mockUser_, 0));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformDeposit_WhenAmountIsNegative_ThenFailsAndBalanceRemainsSame)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(&account_));

    EXPECT_FALSE(performDeposit(&mockUser_, -10));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenUserIsNotAccountHolder_ThenReturnsFalse)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(0);

    EXPECT_FALSE(performWithdrawal(&mockUser_, 100));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAccountIsNull_ThenReturnsFalse)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_FALSE(performWithdrawal(&mockUser_, 100));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountIsWithinBalance_ThenSucceedsAndBalanceDecreases)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(&account_));

    EXPECT_TRUE(performWithdrawal(&mockUser_, 200));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 300.0);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountExceedsBalance_ThenFailsAndBalanceRemainsSame)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(&account_));

    EXPECT_FALSE(performWithdrawal(&mockUser_, 600));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountIsZero_ThenFailsAndBalanceRemainsSame)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(&account_));

    EXPECT_FALSE(performWithdrawal(&mockUser_, 0));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountIsNegative_ThenFailsAndBalanceRemainsSame)
{
    EXPECT_CALL(mockUser_, isAccountHolder())
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(mockUser_, getAccount())
        .Times(1)
        .WillOnce(Return(&account_));

    EXPECT_FALSE(performWithdrawal(&mockUser_, -10));
    EXPECT_DOUBLE_EQ(account_.getBalance(), 500.0);
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenUserDoesNotExistAndAddUserSucceeds_ThenReturnsTrueAndSetsAccountNumber)
{
    EXPECT_CALL(mockBank_, findUser("u1"))
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_CALL(mockBank_, generateAccountNumber())
        .Times(1)
        .WillOnce(Return(101));

    User* newUser = nullptr;

    EXPECT_CALL(mockBank_, addUser(_))
        .Times(1)
        .WillOnce(Invoke([&](User* user) {
            newUser = user;
            return true;
        }));

    bool result = createAccountHolderInBank(mockBank_, "Name", "u1", "p1", 500, createdAccountNumber_);

    EXPECT_TRUE(result);
    EXPECT_EQ(createdAccountNumber_, 101);

    delete newUser;
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenUsernameAlreadyExists_ThenReturnsFalseAndDoesNotCreateAccount)
{
    MockUser existingUser;

    EXPECT_CALL(mockBank_, findUser("u1"))
        .Times(1)
        .WillOnce(Return(&existingUser));

    EXPECT_CALL(mockBank_, generateAccountNumber()).Times(0);
    EXPECT_CALL(mockBank_, addUser(_)).Times(0);

    bool result = createAccountHolderInBank(mockBank_, "Name", "u1", "p1", 500, createdAccountNumber_);

    EXPECT_FALSE(result);
    EXPECT_EQ(createdAccountNumber_, 0);
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenInitialDepositIsNegative_ThenReturnsFalseAndDoesNotCreateAccount)
{
    createdAccountNumber_ = 999;

    EXPECT_CALL(mockBank_, findUser("u1"))
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_CALL(mockBank_, generateAccountNumber()).Times(0);
    EXPECT_CALL(mockBank_, addUser(_)).Times(0);

    bool result = createAccountHolderInBank(mockBank_, "Name", "u1", "p1", -10, createdAccountNumber_);

    EXPECT_FALSE(result);
    EXPECT_EQ(createdAccountNumber_, 0);
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenAddUserFails_ThenReturnsFalseAndResetsAccountNumber)
{
    EXPECT_CALL(mockBank_, findUser("u1"))
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_CALL(mockBank_, generateAccountNumber())
        .Times(1)
        .WillOnce(Return(101));

    EXPECT_CALL(mockBank_, addUser(_))
        .Times(1)
        .WillOnce(Return(false));

    bool result = createAccountHolderInBank(mockBank_, "Name", "u1", "p1", 500, createdAccountNumber_);

    EXPECT_FALSE(result);
    EXPECT_EQ(createdAccountNumber_, 0);
}

TEST_F(BankUsecaseFixture, DeleteAccount_WhenBankRemoveUserSucceeds_ThenReturnsTrue)
{
    EXPECT_CALL(mockBank_, removeUser(10, IBank::RemovalType::Temporary))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_TRUE(deleteAccount(mockBank_, 10, IBank::RemovalType::Temporary));
}

TEST_F(BankUsecaseFixture, DeleteAccount_WhenBankRemoveUserFails_ThenReturnsFalse)
{
    EXPECT_CALL(mockBank_, removeUser(10, IBank::RemovalType::Permanent))
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_FALSE(deleteAccount(mockBank_, 10, IBank::RemovalType::Permanent));
}
