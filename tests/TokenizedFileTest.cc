#include <gtest/gtest.h>

#include "TokenList.hh"
#include "TokenizedFile.hh"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

struct TokenizedFileTest : public ::testing::Test {
    void SetUp() override {
        int fd = open(__FILE__, O_RDONLY);
        if (fd == -1)
            throw "open failed";

        struct stat stat_buf;
        if ( fstat(fd, &stat_buf) == -1)
            throw "fstat failed";

        file = mmap(0, stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        length = stat_buf.st_size;

        if (file == MAP_FAILED)
            throw "mmap failed";
    }

    void TearDown() override {
        // this should fail because dtor of TokenizedFile 
        // should have already unmapped
        (void) munmap(file, length);
    }

    void* file;
    std::size_t length;
};


TEST_F(TokenizedFileTest, Ctor)
{
    TokenList fake;

    TokenizedFile tf(fake, file, length);

    ASSERT_TRUE(tf.unmap);
}


TEST_F(TokenizedFileTest, DtorUnmaps)
{
    TokenList fake;

    TokenizedFile tf(fake, file, length);

    tf.~TokenizedFile();

    // the mapping should have already been unmapped by this point

    int should_fail = mlock(tf.mapping, length);

    EXPECT_EQ(should_fail, -1);
    EXPECT_EQ(errno, ENOMEM);
}
