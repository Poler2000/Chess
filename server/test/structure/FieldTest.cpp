#include <gtest/gtest.h>
#include "structure/Field.h"
#include "structure/PieceFactory.h"

TEST (FieldTest, occupiedTest) {
    structure::Field f{1,2};
    ASSERT_EQ (0,  f.isOccupiedBy());
    f.setOccupied(structure::PieceFactory::getRedId());
    ASSERT_EQ (7, f.isOccupiedBy());
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}