#ifndef CHESS_MESSAGE_H
#define CHESS_MESSAGE_H

#include "structure/chessPoint.h"
#include "structure/FigureData.h"
#include <string>
#include <vector>
#include <variant>
#include <utility>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/variant.hpp>
#include <cereal/types/string.hpp>

namespace comm {

    struct Message {
        std::string type;
        std::vector<std::pair<std::string, std::variant<std::string, int, structure::ChessPoint, structure::FigureData>>> content;

        explicit Message(std::string type) : type(std::move(type)){}

        template<class T>
        void addField(std::string label, T arg) {
            content.template emplace_back(std::make_pair(std::move(label), arg));
        }

        template <class Archive>
        void serialize(Archive& ar) {
            ar(type, content);
        }

        [[nodiscard]] std::string getType() const {
            return type;
        }

        [[nodiscard]] bool hasField(const std::string &identifier) const {
            return std::find_if(content.begin(), content.end(),
                                [&](auto& pair) -> bool {
                                    return identifier == pair.first;
                                }) < content.end();
        }

        [[nodiscard]] int getInt(const std::string &identifier) const noexcept(false) {
            for(auto it = content.begin(); it != content.end(); it++) {
                if (it->first == identifier) {
                    try {
                        return std::get<int>(it->second);
                    }
                    catch(std::bad_variant_access& ex) {
                        throw ex;
                    }
                }
            }
            return 0;
        }

        [[nodiscard]] std::string getString(const std::string &identifier) const noexcept(false) {
            for(auto it = content.begin(); it != content.end(); it++) {
                if (it->first == identifier) {
                    try {
                        return std::get<std::string>(it->second);
                    }
                    catch(std::bad_variant_access& ex) {
                        throw ex;
                    }
                }
            }
            return "";
        }

        [[nodiscard]] std::vector<std::string> getStrings(const std::string &identifier) const noexcept(false) {
            std::vector<std::string> result;
            for(auto it = content.begin(); it != content.end(); it++) {
                if (it->first == identifier) {
                    try {
                        result.emplace_back(std::get<std::string>(it->second));
                    }
                    catch(std::bad_variant_access& ex) {
                        throw ex;
                    }
                }
            }
            return result;
        }

        [[nodiscard]] std::vector<int> getInts(const std::string &identifier) const noexcept(false) {
            std::vector<int> result;
            for(auto it = content.begin(); it != content.end(); it++) {
                if (it->first == identifier) {
                    try {
                        result.emplace_back(std::get<int>(it->second));
                    }
                    catch(std::bad_variant_access& ex) {
                        throw ex;
                    }
                }
            }
            return result;
        }

        [[nodiscard]] std::vector<structure::FigureData> getFigureConfig() const noexcept(false) {
            std::vector<structure::FigureData> result;
            for(auto it = content.begin(); it != content.end(); it++) {
                std::cout << it->first << "\n";
                if (it->first == "figure") {
                    try {
                        result.emplace_back(std::get<structure::FigureData>(it->second));
                    }
                    catch(std::bad_variant_access& ex) {
                        throw ex;
                    }
                }
            }
            return result;
        }

        [[nodiscard]] std::vector<structure::ChessPoint> getPositions() const noexcept(false) {
            std::vector<structure::ChessPoint> result;
            for(auto it = content.begin(); it != content.end(); it++) {
                std::cout << it->first << "\n";
                if (it->first == "position") {
                    try {
                        result.emplace_back(std::get<structure::ChessPoint>(it->second));
                    }
                    catch(std::bad_variant_access& ex) {
                        throw ex;
                    }
                }
            }
            return result;
        }
    };
}

#endif //CHESS_MESSAGE_H
