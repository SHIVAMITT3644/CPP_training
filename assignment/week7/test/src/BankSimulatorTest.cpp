#include "BankSimulatorTest.h"

bool performDeposit(AccountHolder* accountHolderUser, double amount);
bool performWithdrawal(AccountHolder* accountHolderUser, double amount);

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

TEST_F(BankSimulatorFixture, PerformDeposit_WhenUserIsValidAndAmountIsPositive_ThenSucceedsAndBalanceIncreases)
{
    ASSERT_NE(user, nullptr);
    ASSERT_NE(user->getAccount(), nullptr);

    EXPECT_TRUE(performDeposit(user, 100));
    EXPECT_DOUBLE_EQ(user->getAccount()->getBalance(), 600);
}

TEST_F(BankSimulatorFixture, PerformDeposit_WhenAmountIsZero_ThenFailsAndBalanceRemainsSame)
{
    ASSERT_NE(user, nullptr);
    ASSERT_NE(user->getAccount(), nullptr);

    EXPECT_FALSE(performDeposit(user, 0));
    EXPECT_DOUBLE_EQ(user->getAccount()->getBalance(), 500);
}

TEST_F(BankSimulatorFixture, PerformDeposit_WhenAmountIsNegative_ThenFailsAndBalanceRemainsSame)
{
    ASSERT_NE(user, nullptr);
    ASSERT_NE(user->getAccount(), nullptr);

    EXPECT_FALSE(performDeposit(user, -10));
    EXPECT_DOUBLE_EQ(user->getAccount()->getBalance(), 500);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountIsWithinBalance_ThenSucceedsAndBalanceDecreases)
{
    ASSERT_NE(user, nullptr);
    ASSERT_NE(user->getAccount(), nullptr);

    EXPECT_TRUE(performWithdrawal(user, 200));
    EXPECT_DOUBLE_EQ(user->getAccount()->getBalance(), 300);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountExceedsBalance_ThenFailsAndBalanceRemainsSame)
{
    ASSERT_NE(user, nullptr);
    ASSERT_NE(user->getAccount(), nullptr);

    EXPECT_FALSE(performWithdrawal(user, 600));
    EXPECT_DOUBLE_EQ(user->getAccount()->getBalance(), 500);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountIsZero_ThenFailsAndBalanceRemainsSame)
{
    ASSERT_NE(user, nullptr);
    ASSERT_NE(user->getAccount(), nullptr);

    EXPECT_FALSE(performWithdrawal(user, 0));
    EXPECT_DOUBLE_EQ(user->getAccount()->getBalance(), 500);
}

TEST_F(BankSimulatorFixture, PerformWithdrawal_WhenAmountIsNegative_ThenFailsAndBalanceRemainsSame)
{
    ASSERT_NE(user, nullptr);
    ASSERT_NE(user->getAccount(), nullptr);

    EXPECT_FALSE(performWithdrawal(user, -10));
    EXPECT_DOUBLE_EQ(user->getAccount()->getBalance(), 500);
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenUserDoesNotExistAndAddUserSucceeds_ThenReturnsTrueAndSetsAccountNumber)
{
    EXPECT_CALL(bank, findUser("u1"))
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_CALL(bank, generateAccountNumber())
        .Times(1)
        .WillOnce(Return(101));

    User* newUser = nullptr;

    EXPECT_CALL(bank, addUser(_))
        .Times(1)
        .WillOnce(Invoke([&](User* user) {
            newUser = user;
            return true;
        }));

    bool result = createAccountHolderInBank(bank, "Name", "u1", "p1", 500, createdAccountNumber);

    EXPECT_TRUE(result);
    EXPECT_EQ(createdAccountNumber, 101);

    delete newUser;
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenUsernameAlreadyExists_ThenReturnsFalseAndDoesNotCreateAccount)
{
    User* existing = new Admin("Admin", "u1", "p1");

    EXPECT_CALL(bank, findUser("u1"))
        .Times(1)
        .WillOnce(Return(existing));

    EXPECT_CALL(bank, generateAccountNumber()).Times(0);
    EXPECT_CALL(bank, addUser(_)).Times(0);

    bool result = createAccountHolderInBank(bank, "Name", "u1", "p1", 500, createdAccountNumber);

    EXPECT_FALSE(result);
    EXPECT_EQ(createdAccountNumber, 0);

    delete existing;
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenInitialDepositIsNegative_ThenReturnsFalseAndDoesNotCreateAccount)
{
    createdAccountNumber = 999;

    EXPECT_CALL(bank, findUser("u1"))
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_CALL(bank, generateAccountNumber()).Times(0);
    EXPECT_CALL(bank, addUser(_)).Times(0);

    bool result = createAccountHolderInBank(bank, "Name", "u1", "p1", -10, createdAccountNumber);

    EXPECT_FALSE(result);
    EXPECT_EQ(createdAccountNumber, 0);
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenAddUserFails_ThenReturnsFalseAndResetsAccountNumber)
{
    EXPECT_CALL(bank, findUser("u1"))
        .Times(1)
        .WillOnce(Return(nullptr));

    EXPECT_CALL(bank, generateAccountNumber())
        .Times(1)
        .WillOnce(Return(101));

    EXPECT_CALL(bank, addUser(_))
        .Times(1)
        .WillOnce(Return(false));

    bool result = createAccountHolderInBank(bank, "Name", "u1", "p1", 500, createdAccountNumber);

    EXPECT_FALSE(result);
    EXPECT_EQ(createdAccountNumber, 0);
}

TEST_F(BankUsecaseFixture, CreateAccountHolderInBank_WhenSuccessful_ThenCreatesAccountHolderWithCorrectData)
{
    EXPECT_CALL(bank, findUser("u1")).Times(1).WillOnce(Return(nullptr));
    EXPECT_CALL(bank, generateAccountNumber()).Times(1).WillOnce(Return(101));

    User* newUser = nullptr;

    EXPECT_CALL(bank, addUser(_)).Times(1).WillOnce(Invoke([&](User* user) {
        newUser = user;
        return true;
    }));

    bool result = createAccountHolderInBank(bank, "Name", "u1", "p1", 500, createdAccountNumber);

    EXPECT_TRUE(result);
    EXPECT_EQ(createdAccountNumber, 101);

    ASSERT_NE(newUser, nullptr);

    AccountHolder* accountHolder = dynamic_cast<AccountHolder*>(newUser);
    ASSERT_NE(accountHolder, nullptr);

    EXPECT_EQ(accountHolder->getUserName(), "u1");
    EXPECT_EQ(accountHolder->getPassword(), "p1");
    EXPECT_EQ(accountHolder->getName(), "Name");

    ASSERT_NE(accountHolder->getAccount(), nullptr);
    EXPECT_EQ(accountHolder->getAccount()->getAccountNumber(), 101);
    EXPECT_DOUBLE_EQ(accountHolder->getAccount()->getBalance(), 500);

    delete newUser;
}

TEST_F(BankUsecaseFixture, DeleteAccount_WhenBankRemoveUserSucceeds_ThenReturnsTrue)
{
    EXPECT_CALL(bank, removeUser(10, IBank::RemovalType::Temporary))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_TRUE(deleteAccount(bank, 10, IBank::RemovalType::Temporary));
}

TEST_F(BankUsecaseFixture,
       DeleteAccount_WhenBankRemoveUserFails_ThenReturnsFalse)
{
    EXPECT_CALL(bank, removeUser(10, IBank::RemovalType::Permanent))
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_FALSE(deleteAccount(bank, 10, IBank::RemovalType::Permanent));
}
