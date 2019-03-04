/**
 * @file AST_visitor.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-02-25
 * 
 * @copyright Copyright (c) 2019
 * @license GNU GPLv3 
 */
#include "AST.h"

typedef enum {
    Visitor_break, ///< Do not walk down the tree any further
    Visitor_down,  ///< Recurse into the tree
    Visitor_next,  ///< Go to the next statment, ignore the body of the current node
} Visitor_Result ;

typedef Visitor_Result (*visitor_func_t)
    (struct ast_node* current, struct ast_node* parent, void* opt_arg);

/**
 * @brief api to walk down the tree
 * 
 * @param head the start of the translation unit, or anywhere else to start
 * @param visitor_func function to be called on each node, returns the next action
 * @param opt_arg optional argument to be passed to the visitor function
 * @return int returns 0 on succes EINVAL on error happens when either head or 
 * visitor_func are NULL, or -1 if the visitor_func returned Visitor_down when there
 * was nowhere to go but next
 */
int AST_visit_children(struct ast_node* head, 
                       visitor_func_t visitor_func, void* opt_arg);

