#include "include/ScanFile.h"
#include "include/TokenizedFile.h"
#include "include/TokenList.h"

#include <iostream>

int main()
{
    TokenizedFile tf = scan_file("c01_test.c");

    for (auto i : tf.list)
        std::cout << i.to_string() << std::endl;

    return 0;
}