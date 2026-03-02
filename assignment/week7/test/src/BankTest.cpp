#include "BankTest.h"

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
    EXPECT_FALSE(bank->addUser(new Admin("AnotherAdmin", "adminUser", "pass2")));
}

TEST_F(BankFixture, FindUser_WhenUsernameExists_ThenReturnsCorrectUser)
{
    User* foundAdmin = bank->findUser("adminUser");

    ASSERT_NE(foundAdmin, nullptr);
    EXPECT_EQ(foundAdmin->getUserName(), "adminUser");
}

TEST_F(BankFixture, AddUser_WhenAccountHolderAdded_ThenCanBeFoundByAccountNumber)
{
    const int accountNumber = bank->generateAccountNumber();

    EXPECT_TRUE(bank->addUser(new AccountHolder("A", "user1", "pass1", accountNumber, 0)));

    User* foundUser = bank->findUser(accountNumber);
    AccountHolder* foundAccountHolder = dynamic_cast<AccountHolder*>(foundUser);

    ASSERT_NE(foundAccountHolder, nullptr);
    ASSERT_NE(foundAccountHolder->getAccount(), nullptr);

    EXPECT_EQ(foundAccountHolder->getAccount()->getAccountNumber(), accountNumber);
}

TEST_F(BankFixture, RemoveUser_WhenRemovalTypeIsTemporary_ThenAccountBecomesInactive)
{
    const int accountNumber = bank->generateAccountNumber();

    EXPECT_TRUE(bank->addUser(new AccountHolder("A", "user1", "pass1", accountNumber, 100)));

    EXPECT_TRUE(bank->removeUser(accountNumber, IBank::RemovalType::Temporary));

    User* foundUser = bank->findUser(accountNumber);
    AccountHolder* foundAccountHolder = dynamic_cast<AccountHolder*>(foundUser);

    ASSERT_NE(foundAccountHolder, nullptr);
    EXPECT_EQ(foundAccountHolder->getAccount()->getStatus(), INACTIVE);
}

TEST_F(BankFixture, RemoveUser_WhenRemovalTypeIsPermanent_ThenAccountHolderIsDeleted)
{
    const int accountNumber = bank->generateAccountNumber();

    EXPECT_TRUE(bank->addUser(new AccountHolder("A", "user1", "pass1", accountNumber, 100)));

    EXPECT_TRUE(bank->removeUser(accountNumber, IBank::RemovalType::Permanent));

    EXPECT_EQ(bank->findUser(accountNumber), nullptr);
}

TEST_F(BankFixture, Login_WhenAdminCredentialsAreValid_ThenReturnsUser)
{
    EXPECT_NE(bank->login(IBank::Role::Admin, "adminUser", "adminPass"), nullptr);
}

TEST_F(BankFixture, Login_WhenAdminPasswordIsInvalid_ThenReturnsNull)
{
    EXPECT_EQ(bank->login(IBank::Role::Admin, "adminUser", "wrong"), nullptr);
}

TEST_F(BankFixture, Login_WhenAdminUsernameDoesNotExist_ThenReturnsNull)
{
    EXPECT_EQ(bank->login(IBank::Role::Admin, "missing", "adminPass"), nullptr);
}

TEST_F(BankFixture, Login_WhenAccountHolderCredentialsAreValidAndActive_ThenReturnsUser)
{
    const int accountNumber = bank->generateAccountNumber();

    EXPECT_TRUE(bank->addUser(new AccountHolder("A", "user1", "pass1", accountNumber, 100)));

    EXPECT_NE(bank->login(IBank::Role::AccountHolder, std::to_string(accountNumber), "pass1"), nullptr);
}

TEST_F(BankFixture, Login_WhenAccountHolderPasswordIsInvalid_ThenReturnsNull)
{
    const int accountNumber = bank->generateAccountNumber();

    EXPECT_TRUE(bank->addUser( new AccountHolder("A", "user1", "pass1", accountNumber, 100)));

    EXPECT_EQ(bank->login( IBank::Role::AccountHolder, std::to_string(accountNumber), "wrong"), nullptr);
}

TEST_F(BankFixture, Login_WhenAccountHolderIsInactive_ThenReturnsNull)
{
    const int accountNumber = bank->generateAccountNumber();

    EXPECT_TRUE(bank->addUser(new AccountHolder("A", "user1", "pass1", accountNumber, 100)));

    EXPECT_TRUE(bank->removeUser(accountNumber, IBank::RemovalType::Temporary));

    EXPECT_EQ(bank->login(IBank::Role::AccountHolder, std::to_string(accountNumber), "pass1"), nullptr);
}
