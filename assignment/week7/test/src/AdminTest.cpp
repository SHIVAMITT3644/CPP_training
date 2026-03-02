#include "AdminTest.h"

TEST_F(AdminFixture, WhenUserIsNull_ThenReturnsNull)
{
    AccountHolder* result = admin->getValidAccountHolder(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(AdminFixture, WhenUserIsNotAccountHolder_ThenReturnsNull)
{
    User* user = new Admin("AnotherAdmin", "x", "y");

    AccountHolder* result = admin->getValidAccountHolder(user);
    EXPECT_EQ(result, nullptr);

    delete user;
}

TEST_F(AdminFixture, WhenUserIsAccountHolder_ThenReturnsAccountHolderPointer)
{
    User* user = new AccountHolder("A", "user1", "pass1", 1, 500.0);

    AccountHolder* result = admin->getValidAccountHolder(user);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getUserName(), "user1");

    delete user;
}

TEST_F(AdminFixture, ViewAccountHolderTransactionHistory_WhenUserIsNull_ThenReturnsFalse)
{
    EXPECT_FALSE(admin->viewAccountHolderTransactionHistory(nullptr));
}

TEST_F(AdminFixture, ViewAccountHolderTransactionHistory_WhenUserIsNotAccountHolder_ThenReturnsFalse)
{
    User* user = new Admin("AnotherAdmin", "x", "y");

    bool result = admin->viewAccountHolderTransactionHistory(user);
    EXPECT_FALSE(result);

    delete user;
}

TEST_F(AdminFixture, ViewAccountHolderTransactionHistory_WhenUserIsAccountHolder_ThenReturnsTrue)
{
    User* user = new AccountHolder("A", "user1", "pass1", 1, 500.0);

    bool result = admin->viewAccountHolderTransactionHistory(user);
    EXPECT_TRUE(result);

    delete user;
}
