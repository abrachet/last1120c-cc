/**
 * @file TranslationUnit.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "ASTNodeBase.h"
#include "NodeList.h"
#include "last-cc_assert.h"
#include <vector>
#include <memory>
#include <string>
#include <type_traits>

class TranslationUnit {
    const std::string filename;

    NodeList global_declarations;

public:
    TranslationUnit(std::string filename)
    : filename(filename)
    {}

    template <typename T>
    void add_node(T node) {
        if (!std::is_base_of<ASTNodeBase, T>::value)
            cc_assert(false, "Is not a node type");

        global_declarations.push_back(std::make_unique<T>(node));
    }

    using iterator = void;
    using iterator_category = std::bidirectional_iterator_tag;

    const NodeList& get_decls() const
    {
        return this->global_declarations;
    }

};
