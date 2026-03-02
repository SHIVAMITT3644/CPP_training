#ifndef ADMIN_TEST_H
#define ADMIN_TEST_H

#include <gtest/gtest.h>
#include "Admin.h"
#include "AccountHolder.h"

class AdminFixture : public ::testing::Test
{
protected:
    Admin* admin = nullptr;

    void SetUp() override
    {
        admin = new Admin("Admin", "adminUser", "adminPass");
    }

    void TearDown() override
    {
        delete admin;
        admin = nullptr;
    }
};

#endif
