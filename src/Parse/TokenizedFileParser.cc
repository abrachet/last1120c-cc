/**
 * @file TokenizedFileParser.cc
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief A recursive descent parser which walks down the TokenList attempting
 * to create the AST from the source tokens.
 * 
 * @version 0.1
 * @date 2019-05-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "ParseUtil.h"
#include "ParseCommon.h"
#include "TopLevel.h"

TranslationUnit parse_tokenized_file(TokenizedFile& tf)
{
    TranslationUnit tu(tf.filename);

    TokenList& tl = tf.list;

    TokenList::iterator potential;

    for (auto it = tl.cbegin(), end = tl.cend(); it != end; )
    {   
    
        if ( (potential = global_var(it, tu)) ) {
            it = potential;
            continue;
        }

        if ( (potential = function(it, tu)) ) {
            it = potential;
            continue;
        }
        
        // An emtpy semicolon is valid at the top level
        // Note: this doesn't match after global_var matches 
        // because after the match it returns an iterator past the semi colon
        if ( (potential = semi_colon(it)) ) {
            it = potential;
            continue;
        }

        std::cout << "On token: " << it->to_string() << '\n';

        if (it != end)
            throw "invalid source file";
    }

    return tu;

}

