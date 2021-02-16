#include "logic/MoveValidator.h"

namespace logic {
    MoveValidator::MoveValidator(std::vector<std::shared_ptr<structure::Field>>& fields)
        : fields(fields) {}

    std::vector<int> MoveValidator::getPossibleFieldIds(const structure::Figure &figure) {
        std::vector<int> results;
        auto mov = figure.getPossibleMovement();
        std::for_each(fields.begin(), fields.end(), [&](std::shared_ptr<structure::Field>& f){
            if (mov->up) {
                if (f->getX() == figure.getX())
                if (mov->multipleFields) {

                }
            }
            else if (mov->down) {
                if (mov->multipleFields) {
                    if (f->getY() == figure.getY()) {
                        results.push_back(f.getId());
                    }
                }
                else {

                }

            }
            else if (mov->side) {

            }
            else if (mov->jump) {

            }
            else if (mov->diagonal) {

            }
        });
        if (mov -> up) {
            std::for_each()
        }
        return results;
    }

}

