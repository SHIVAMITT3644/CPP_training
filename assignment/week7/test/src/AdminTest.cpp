#include "AdminTest.h"

using ::testing::Return;
using ::testing::_;

TEST_F(AdminFixture, ViewAccountHolderBalance_WhenUserDoesNotExist_ThenReturnsFalse)
{
    EXPECT_FALSE(admin_->viewAccountHolderBalance(nullptr));
}

TEST_F(AdminFixture, ViewAccountHolderBalance_WhenUserIsNotAccountHolder_ThenReturnsFalse)
{
    EXPECT_CALL(*mockUser_, isAccountHolder())
        .WillOnce(Return(false));

    EXPECT_FALSE(admin_->viewAccountHolderBalance(mockUser_));
}

TEST_F(AdminFixture, ViewAccountHolderBalance_WhenUserIsAccountHolder_ThenReturnsTrue)
{
    EXPECT_CALL(*mockUser_, isAccountHolder())
        .WillOnce(Return(true));

    EXPECT_CALL(*mockUser_, getAccount())
        .WillRepeatedly(Return(account_));

    EXPECT_CALL(*mockUser_, getName())
        .WillOnce(Return("user1"));

    EXPECT_TRUE(admin_->viewAccountHolderBalance(mockUser_));
}

TEST_F(AdminFixture, ViewAccountHolderTransactionHistory_WhenUserDoesNotExist_ThenReturnsFalse)
{
    EXPECT_FALSE(admin_->viewAccountHolderTransactionHistory(nullptr));
}

TEST_F(AdminFixture, ViewAccountHolderTransactionHistory_WhenUserIsNotAccountHolder_ThenReturnsFalse)
{
    EXPECT_CALL(*mockUser_, isAccountHolder())
        .WillOnce(Return(false));

    EXPECT_FALSE(admin_->viewAccountHolderTransactionHistory(mockUser_));
}

TEST_F(AdminFixture, ViewAccountHolderTransactionHistory_WhenUserIsAccountHolder_ThenReturnsTrue)
{
    EXPECT_CALL(*mockUser_, isAccountHolder())
        .WillOnce(Return(true));

    EXPECT_CALL(*mockUser_, getAccount())
        .WillRepeatedly(Return(account_));

    EXPECT_CALL(*mockUser_, getUserName())
        .WillOnce(Return("user1"));

    EXPECT_TRUE(admin_->viewAccountHolderTransactionHistory(mockUser_));
}
