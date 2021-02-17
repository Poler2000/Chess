#include <gtest/gtest.h>
#include "structure/Field.h"
#include "structure/PieceFactory.h"

TEST (FieldTest, occupiedTest) {
    structure::Field f{1,2};
    ASSERT_EQ (0,  f.isOccupiedBy());
    f.setOccupied(structure::PieceFactory::getRedId());
    ASSERT_EQ (structure::PieceFactory::getRedId(), f.isOccupiedBy());
    ASSERT_NE(structure::PieceFactory::getBlueId(), f.isOccupiedBy());
}

