cmake_minimum_required(VERSION 3.14)
project(last1120c_cc)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/AST)

add_executable(last1120c_cc
        include/AST/ASTContex.h
        include/AST/ASTList.h
        include/AST/ASTNode.h
        include/AST/ASTNodeBase.h
        include/AST/TranslationUnit.h
        include/last-cc.hh
        include/last-cc_assert.hh
        include/ScanFile.hh
        include/Scanner.hh
        include/Token.hh
        include/TokenizedFile.hh
        include/TokenList.hh
        src/ScanFile.cc
        tests/ScanFileTest.cc
        tests/ScannerTest.cc
        tests/TokenizedFileTest.cc
        tests/TokenListTest.cc
        tests/TokenTest.cc
        include/AST/ASTVisitor.h)
