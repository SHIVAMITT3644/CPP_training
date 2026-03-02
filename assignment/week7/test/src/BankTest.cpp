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
    NiceMock<MockUser>* user1_ = new NiceMock<MockUser>();
    EXPECT_CALL(*user1_, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*user1_, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*user1_, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_TRUE(bank_->addUser(user1_));

    NiceMock<MockUser>* user2_ = new NiceMock<MockUser>();
    EXPECT_CALL(*user2_, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*user2_, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*user2_, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_FALSE(bank_->addUser(user2_));

    delete user2_;
    user2_ = nullptr;
}

TEST_F(BankFixture, FindUser_WhenUsernameExists_ThenReturnsCorrectUser)
{
    NiceMock<MockUser>* admin_ = new NiceMock<MockUser>();
    EXPECT_CALL(*admin_, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*admin_, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*admin_, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_TRUE(bank_->addUser(admin_));

    User* found_ = bank_->findUser("adminUser");

    ASSERT_NE(found_, nullptr);
    EXPECT_EQ(found_, admin_);
}

TEST_F(BankFixture, AddUser_WhenAccountHolderAdded_ThenCanBeFoundByAccountNumber)
{
    const int accountNumber_ = bank_->generateAccountNumber();

    Account* account_ = new Account(accountNumber_, 0.0, ACTIVE);

    NiceMock<MockUser>* accountHolder_ = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder_, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder_, getPassword()).WillRepeatedly(Return("pass1"));
    EXPECT_CALL(*accountHolder_, getName()).WillRepeatedly(Return("A"));
    EXPECT_CALL(*accountHolder_, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder_, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder_));

    User* found_ = bank_->findUser(accountNumber_);

    ASSERT_NE(found_, nullptr);
    EXPECT_EQ(found_, accountHolder_);
    ASSERT_NE(found_->getAccount(), nullptr);
    EXPECT_EQ(found_->getAccount()->getAccountNumber(), accountNumber_);

    delete account_;
    account_ = nullptr;
}

TEST_F(BankFixture, RemoveUser_WhenRemovalTypeIsTemporary_ThenAccountBecomesInactive)
{
    const int accountNumber_ = bank_->generateAccountNumber();

    Account* account_ = new Account(accountNumber_, 100.0, ACTIVE);

    NiceMock<MockUser>* accountHolder_ = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder_, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder_, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder_, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder_));

    EXPECT_TRUE(bank_->removeUser(accountNumber_, IBank::RemovalType::Temporary));

    User* found_ = bank_->findUser(accountNumber_);

    ASSERT_NE(found_, nullptr);
    ASSERT_NE(found_->getAccount(), nullptr);
    EXPECT_EQ(found_->getAccount()->getStatus(), INACTIVE);

    delete account_;
    account_ = nullptr;
}

TEST_F(BankFixture, RemoveUser_WhenRemovalTypeIsPermanent_ThenAccountHolderIsDeleted)
{
    const int accountNumber_ = bank_->generateAccountNumber();

    Account* account_ = new Account(accountNumber_, 100.0, ACTIVE);

    NiceMock<MockUser>* accountHolder_ = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder_, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder_, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder_, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder_));

    EXPECT_TRUE(bank_->removeUser(accountNumber_, IBank::RemovalType::Permanent));

    EXPECT_EQ(bank_->findUser(accountNumber_), nullptr);

    delete account_;
    account_ = nullptr;
}

TEST_F(BankFixture, Login_WhenAdminCredentialsAreValid_ThenReturnsUser)
{
    NiceMock<MockUser>* admin_ = new NiceMock<MockUser>();

    EXPECT_CALL(*admin_, getUserName())
        .WillRepeatedly(Return("adminUser"));

    EXPECT_CALL(*admin_, isAdmin())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(*admin_, getPassword())
        .WillRepeatedly(Return("adminPass"));

    EXPECT_TRUE(bank_->addUser(admin_));

    User* result_ = bank_->login(IBank::Role::Admin, "adminUser", "adminPass");

    ASSERT_NE(result_, nullptr);
    EXPECT_EQ(result_, admin_);
}

TEST_F(BankFixture, Login_WhenAdminPasswordIsInvalid_ThenReturnsNull)
{
    NiceMock<MockUser>* admin_ = new NiceMock<MockUser>();
    EXPECT_CALL(*admin_, getUserName()).WillRepeatedly(Return("adminUser"));
    EXPECT_CALL(*admin_, getPassword()).WillRepeatedly(Return("adminPass"));
    EXPECT_CALL(*admin_, isAccountHolder()).WillRepeatedly(Return(false));
    EXPECT_CALL(*admin_, getAccount()).WillRepeatedly(Return(nullptr));

    EXPECT_TRUE(bank_->addUser(admin_));

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

    NiceMock<MockUser>* accountHolder_ = new NiceMock<MockUser>();

    EXPECT_CALL(*accountHolder_, getUserName())
        .WillRepeatedly(Return("user1"));

    EXPECT_CALL(*accountHolder_, isAccountHolder())
        .WillRepeatedly(Return(true));

    EXPECT_CALL(*accountHolder_, getPassword())
        .WillRepeatedly(Return("pass1"));

    EXPECT_CALL(*accountHolder_, getAccount())
        .WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder_));

    User* result_ = bank_->login(IBank::Role::AccountHolder,
                                 std::to_string(accountNumber_),
                                 "pass1");

    ASSERT_NE(result_, nullptr);
    EXPECT_EQ(result_, accountHolder_);

    delete account_;
}

TEST_F(BankFixture, Login_WhenAccountHolderPasswordIsInvalid_ThenReturnsNull)
{
    const int accountNumber_ = bank_->generateAccountNumber();

    Account* account_ = new Account(accountNumber_, 100.0, ACTIVE);

    NiceMock<MockUser>* accountHolder_ = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder_, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder_, getPassword()).WillRepeatedly(Return("pass1"));
    EXPECT_CALL(*accountHolder_, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder_, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder_));

    EXPECT_EQ(bank_->login(IBank::Role::AccountHolder, std::to_string(accountNumber_), "wrong"), nullptr);

    delete account_;
    account_ = nullptr;
}

TEST_F(BankFixture, Login_WhenAccountHolderIsInactive_ThenReturnsNull)
{
    const int accountNumber_ = bank_->generateAccountNumber();

    Account* account_ = new Account(accountNumber_, 100.0, INACTIVE);

    NiceMock<MockUser>* accountHolder_ = new NiceMock<MockUser>();
    EXPECT_CALL(*accountHolder_, getUserName()).WillRepeatedly(Return("user1"));
    EXPECT_CALL(*accountHolder_, getPassword()).WillRepeatedly(Return("pass1"));
    EXPECT_CALL(*accountHolder_, isAccountHolder()).WillRepeatedly(Return(true));
    EXPECT_CALL(*accountHolder_, getAccount()).WillRepeatedly(Return(account_));

    EXPECT_TRUE(bank_->addUser(accountHolder_));

    EXPECT_EQ(bank_->login(IBank::Role::AccountHolder, std::to_string(accountNumber_), "pass1"), nullptr);

    delete account_;
    account_ = nullptr;
}
