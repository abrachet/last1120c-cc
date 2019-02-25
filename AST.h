/**
 * @file AST.h
 * @author Alex Brachet-Mialot (abrachet@purdue.edu)
 * @brief internal types for the abstract syntax tree
 * Nodes of the tree use unions to create polymorhic like types
 * 
 * Still a work in progress!
 * 
 * @version 0.1
 * @date 2019-02-20
 * 
 * @copyright Copyright (c) 2019 Alex Brachet-Mialot
 * @license GNU GPLv3 
 */

// Forward declarations for struct AST_node
struct decl;
struct stmt;

typedef enum {
    NT_Decl,
    NT_Stmt    
} NodeType;

/**
 * @brief Nodes for the AST
 * 
 */
struct ast_node {
    union {
        struct decl decl;
        struct stmt stmt;
    };
    
    NodeType type;

    struct ast_node *next;
    struct ast_node *down;
};

// Forward declartions for struct decl
struct data_decl;
struct func_decl;

typedef enum {
    DT_Data,
    DT_Func
} DeclType;


struct decl {
    union {
        struct data_decl data;
        struct func_decl func;
    };
    
    DeclType type;    
};

/**
 * @brief describes a data declaration in the gloabl scope
 * these exist in the form of \code{.c} name value; \endcode
 * comparable to the modern C version on \code{.c} int name = value; \endcode 
 */
struct data_decl {
    struct token *name;
    struct token *value; // NULL if none is provided  
};

/**
 * @brief describes a function declaration. 
 * \code{.c} func(a, b) { \endcode
 */
struct func_decl {
    struct token    *name;

    struct vars_vec *vars; 
};


typedef enum {
    ST_Extern,
    ST_Auto,
    ST_Return,
} StmtType;

struct extern_stmt;
struct auto_stmt;
struct return_stmt;

/**
 * @brief represents a logical statement
 */
struct stmt {
    union {
        struct extern_stmt  extern_;
        struct auto_stmt    auto_;
        struct return_stmt  return_;
    };
    
    StmtType type;
};

struct extern_stmt {
    
};

struct auto_stmt {

};

struct return_stmt {

};
