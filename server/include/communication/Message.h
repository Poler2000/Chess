#ifndef CHESS_MESSAGE_H
#define CHESS_MESSAGE_H

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
        std::vector<std::pair<std::string, std::variant<std::string, int>>> content;

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
    };
}

#endif //CHESS_MESSAGE_H
