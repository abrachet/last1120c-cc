/**
 * @file ASTTags.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Tags for ASTNodes to describe them. Similar to iterator_tags. 
 * These tags may never be useful, they aren't as of now
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

namespace AstTag {

/**
 * @brief Represents a Node which owns more nodes, a function should be
 * marked recursive because it consists of multiple nodes under it.
 * Classes marked recursive should be iterable over the owned nodes.
 */
struct recursive_tag {};

/**
 * @brief Represents a node which is a leaf of the tree. Global variables are leafs
 * because they do not own any nodes.
 */
struct leaf_tag {};

/**
 * @brief Exists *ONLY* for ASTNodeBase, which should be abstract, it should never be 
 * instantiated. It exists for debugging purposes and for assertations to ensure that derived
 * classes overload the using declaration in ASTNodeBase.
 */
struct undefined_tag {};

} // namespace AstTag
