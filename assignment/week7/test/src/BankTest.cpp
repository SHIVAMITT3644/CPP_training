#include "BankTest.h"

#include <gmock/gmock.h>
#include <string>

#include "MockUser.h"
#include "Account.h"
#include "Constants.h"
#include "IBank.h"

using ::testing::NiceMock;
using ::testing::Return;

TEST(BankTests, GenerateAccountNumber_WhenCalledOnNewBankInstances_ThenStartsFromOneIndependently)
{
    Bank bankA("A");
    Bank bankB("B");

    EXPECT_EQ(bankA.generateAccountNumber(), 1);
    EXPECT_EQ(bankA.generateAccountNumber(), 2);
    EXPECT_EQ(bankB.generateAccountNumber(), 1);
}

TEST_F(BankFixture, AddUser_WhenUsernameAlreadyExists_ThenReturnsFalse)
{
    NiceMock<MockUser>* user1 = new NiceMock<MockUser>();
    EXPECT_CALL(*user1, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*user1, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*user1, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_TRUE(bank_->addUser(user1));

    NiceMock<MockUser>* user2 = new NiceMock<MockUser>();
    EXPECT_CALL(*user2, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*user2, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*user2, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_FALSE(bank_->addUser(user2));

    delete user2;
    user2 = nullptr;
}

TEST_F(BankFixture, FindUser_WhenUsernameExists_ThenReturnsCorrectUser)
{
    NiceMock<MockUser>* admin = new NiceMock<MockUser>();
    EXPECT_CALL(*admin, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*admin, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*admin, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_TRUE(bank_->addUser(admin));

    User* found = bank_->findUser("adminUser");

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, admin);
}

TEST_F(BankFixture, AddUser_WhenAccountHolderAdded_ThenCanBeFoundByAccountNumber)
{
    const int accountNumber = bank_->generateAccountNumber();

    Account* account = new Account(accountNumber, 0.0, ACTIVE);

    NiceMock<MockUser>* accountHolder = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder, getPassword()).WillRepeatedly(Return("pass1"));
    EXPECT_CALL(*accountHolder, getName()).WillRepeatedly(Return("A"));
    EXPECT_CALL(*accountHolder, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder, getAccount()).WillRepeatedly(Return(account));

    EXPECT_TRUE(bank_->addUser(accountHolder));

    User* found = bank_->findUser(accountNumber);

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, accountHolder);
    ASSERT_NE(found->getAccount(), nullptr);
    EXPECT_EQ(found->getAccount()->getAccountNumber(), accountNumber);

    delete account;
    account = nullptr;
}

TEST_F(BankFixture, RemoveUser_WhenRemovalTypeIsTemporary_ThenAccountBecomesInactive)
{
    const int accountNumber = bank_->generateAccountNumber();

    Account* account = new Account(accountNumber, 100.0, ACTIVE);

    NiceMock<MockUser>* accountHolder = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder, getAccount()).WillRepeatedly(Return(account));

    EXPECT_TRUE(bank_->addUser(accountHolder));

    EXPECT_TRUE(bank_->removeUser(accountNumber, IBank::RemovalType::Temporary));

    User* found = bank_->findUser(accountNumber);

    ASSERT_NE(found, nullptr);
    ASSERT_NE(found->getAccount(), nullptr);
    EXPECT_EQ(found->getAccount()->getStatus(), INACTIVE);

    delete account;
    account = nullptr;
}

TEST_F(BankFixture, RemoveUser_WhenRemovalTypeIsPermanent_ThenAccountHolderIsDeleted)
{
    const int accountNumber = bank_->generateAccountNumber();

    Account* account = new Account(accountNumber, 100.0, ACTIVE);

    NiceMock<MockUser>* accountHolder = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder, getAccount()).WillRepeatedly(Return(account));

    EXPECT_TRUE(bank_->addUser(accountHolder));

    EXPECT_TRUE(bank_->removeUser(accountNumber, IBank::RemovalType::Permanent));

    EXPECT_EQ(bank_->findUser(accountNumber), nullptr);

    delete account;
    account = nullptr;
}

TEST_F(BankFixture, Login_WhenAdminCredentialsAreValid_ThenReturnsUser)
{
    NiceMock<MockUser>* admin = new NiceMock<MockUser>();

    EXPECT_CALL(*admin, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*admin, isAdmin()).WillRepeatedly(Return(true));
    EXPECT_CALL(*admin, getPassword()).WillRepeatedly(Return("adminPass"));

    EXPECT_TRUE(bank_->addUser(admin));

    User* result_ = bank_->login(IBank::Role::Admin, "adminUser", "adminPass");

    ASSERT_NE(result_, nullptr);
    EXPECT_EQ(result_, admin);
}

TEST_F(BankFixture, Login_WhenAdminPasswordIsInvalid_ThenReturnsNull)
{
    NiceMock<MockUser>* admin = new NiceMock<MockUser>();
    EXPECT_CALL(*admin, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*admin, getPassword()).WillRepeatedly(Return("adminPass"));
    EXPECT_CALL(*admin, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*admin, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_TRUE(bank_->addUser(admin));

    EXPECT_EQ(bank_->login(IBank::Role::Admin, "adminUser", "wrong"), nullptr);
}

TEST_F(BankFixture, Login_WhenAdminUsernameDoesNotExist_ThenReturnsNull)
{
    EXPECT_EQ(bank_->login(IBank::Role::Admin, "missing", "adminPass"), nullptr);
}

TEST_F(BankFixture, Login_WhenAccountHolderCredentialsAreValidAndActive_ThenReturnsUser)
{
    const int accountNumber_ = bank_->generateAccountNumber();
    Account* account_ = new Account(accountNumber_, 100.0, ACTIVE);

    NiceMock<MockUser>* accountHolder = new NiceMock<MockUser>();

    EXPECT_CALL(*accountHolder, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder, getPassword()).WillRepeatedly(Return("pass1"));
    EXPECT_CALL(*accountHolder, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder));

    User* result_ = bank_->login(IBank::Role::AccountHolder, std::to_string(accountNumber_), "pass1");

    ASSERT_NE(result_, nullptr);
    EXPECT_EQ(result_, accountHolder);

    delete account_;
}

TEST_F(BankFixture, Login_WhenAccountHolderPasswordIsInvalid_ThenReturnsNull)
{
    const int accountNumber_ = bank_->generateAccountNumber();

    Account* account_ = new Account(accountNumber_, 100.0, ACTIVE);

    NiceMock<MockUser>* accountHolder = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder, getPassword()).WillRepeatedly(Return("pass1"));
    EXPECT_CALL(*accountHolder, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder));

    EXPECT_EQ(bank_->login(IBank::Role::AccountHolder, std::to_string(accountNumber_), "wrong"), nullptr);

    delete account_;
    account_ = nullptr;
}

TEST_F(BankFixture, Login_WhenAccountHolderIsInactive_ThenReturnsNull)
{
    const int accountNumber_ = bank_->generateAccountNumber();

    Account* account_ = new Account(accountNumber_, 100.0, INACTIVE);

    NiceMock<MockUser>* accountHolder = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder, getPassword()).WillRepeatedly(Return("pass1"));
    EXPECT_CALL(*accountHolder, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder));

    EXPECT_EQ(bank_->login(IBank::Role::AccountHolder, std::to_string(accountNumber_), "pass1"), nullptr);

    delete account_;
    account_ = nullptr;
}
