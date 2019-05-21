#include "include/ScanFile.h"
#include "include/TokenizedFile.h"
#include "include/TokenList.h"

#include <iostream>

int main()
{
    TokenizedFile tf = scan_file("tests/global_var.c.test");

    for (auto i : tf.list)
        std::cout << i.to_string() << std::endl;

    return 0;
}