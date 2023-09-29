#include <gtest/gtest.h>
#include "cpy/transaction.hpp"

using namespace cpy;

TEST(TestTransactionManager, TestRollback) {
    transaction_manager manager;

    EXPECT_EQ(manager.pos(), 0);

    manager.start();

    EXPECT_EQ(manager.pos(), 0);

    manager.pos() = 10;

    EXPECT_EQ(manager.pos(), 10);

    manager.rollback();

    EXPECT_EQ(manager.pos(), 0);
}

TEST(TestTransactionManager, TestRollbackNested) {
    transaction_manager manager;

    EXPECT_EQ(manager.pos(), 0);

    manager.start();

    EXPECT_EQ(manager.pos(), 0);

    manager.pos() = 10;

    EXPECT_EQ(manager.pos(), 10);

    manager.start();

    EXPECT_EQ(manager.pos(), 10);

    manager.pos() = 20;

    EXPECT_EQ(manager.pos(), 20);

    manager.rollback();

    EXPECT_EQ(manager.pos(), 10);

    manager.rollback();

    EXPECT_EQ(manager.pos(), 0);
}

TEST(TestTransactionManager, TestCommit) {
    transaction_manager manager;

    EXPECT_EQ(manager.pos(), 0);

    manager.start();

    EXPECT_EQ(manager.pos(), 0);

    manager.pos() = 10;

    EXPECT_EQ(manager.pos(), 10);

    manager.commit();

    EXPECT_EQ(manager.pos(), 10);
}

TEST(TestTransactionManager, TestCommitNested) {
    transaction_manager manager;

    EXPECT_EQ(manager.pos(), 0);

    manager.start();

    EXPECT_EQ(manager.pos(), 0);

    manager.pos() = 10;

    EXPECT_EQ(manager.pos(), 10);

    manager.start();

    EXPECT_EQ(manager.pos(), 10);

    manager.pos() = 20;

    EXPECT_EQ(manager.pos(), 20);

    manager.commit();

    EXPECT_EQ(manager.pos(), 20);

    manager.commit();

    EXPECT_EQ(manager.pos(), 20);
}

TEST(TestTransactionManager, TestCommitRollback) {
    transaction_manager manager;

    EXPECT_EQ(manager.pos(), 0);

    manager.start();

    EXPECT_EQ(manager.pos(), 0);

    manager.pos() = 10;

    EXPECT_EQ(manager.pos(), 10);

    manager.start();

    EXPECT_EQ(manager.pos(), 10);

    manager.pos() = 20;

    EXPECT_EQ(manager.pos(), 20);

    manager.commit();

    EXPECT_EQ(manager.pos(), 20);

    manager.rollback();

    // should be 0, not 20
    // as the first transaction should be restored
    EXPECT_EQ(manager.pos(), 0);
}

TEST(TestTransactionManager, TestCommitRollbackNested) {
    transaction_manager manager;

    EXPECT_EQ(manager.pos(), 0);

    manager.start();

    EXPECT_EQ(manager.pos(), 0);

    manager.pos() = 10;

    EXPECT_EQ(manager.pos(), 10);

    manager.start();

    EXPECT_EQ(manager.pos(), 10);

    manager.pos() = 20;

    EXPECT_EQ(manager.pos(), 20);

    manager.start();

    EXPECT_EQ(manager.pos(), 20);

    manager.pos() = 30;

    EXPECT_EQ(manager.pos(), 30);

    manager.commit();

    EXPECT_EQ(manager.pos(), 30);

    manager.rollback();

    EXPECT_EQ(manager.pos(), 10);

    manager.rollback();

    EXPECT_EQ(manager.pos(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
