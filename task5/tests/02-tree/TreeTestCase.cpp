//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"

TEST(TreeTestCase, all) {
    ASSERT_THROW(GetTree("", false), std::invalid_argument);
    ASSERT_THROW(GetTree("./Makefile", false), std::invalid_argument);
    FileNode src_dirs = GetTree("./src", true);
    ASSERT_TRUE(src_dirs.is_dir);
    ASSERT_EQ(src_dirs.name, "src");
    ASSERT_EQ(src_dirs.children[0].name, GetTree("./src/01-simple-library", true).name);
    ASSERT_EQ(src_dirs.children[0], GetTree("./src/01-simple-library", true));
}
