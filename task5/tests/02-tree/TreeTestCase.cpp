//
// Created by akhtyamovpavel on 5/1/20.
//


#include "TreeTestCase.h"
#include "Tree.h"
#include <boost/filesystem.hpp>
#include <fstream>

using boost::filesystem::create_directories;
using boost::filesystem::remove_all;
using boost::filesystem::current_path;

void TreeTestCase::SetUp() {
    boost::filesystem::path dir("./temp/inner");
    if (boost::filesystem::create_directories(dir)) {
        std::cout << "Setup temp directories successfully" << "\n";
    }
    std::ofstream file("./temp/TempFile.txt");
    file.close();
}

void TreeTestCase::TearDown() {
    boost::filesystem::path dir("./temp");
    boost::filesystem::remove_all(dir);
}

TEST_F(TreeTestCase, exeptions) {
    ASSERT_THROW(GetTree("", false), std::invalid_argument);
    ASSERT_THROW(GetTree("./temp/TempFile.txt", false), std::invalid_argument);
}

TEST_F(TreeTestCase, FileNode) {
    FileNode src_dirs = GetTree("./temp", true);
    ASSERT_TRUE(src_dirs.is_dir);
    ASSERT_EQ(src_dirs.name, "temp");
    ASSERT_EQ(src_dirs.children[0].name, GetTree("./temp/inner", true).name);
    ASSERT_EQ(src_dirs.children[0], GetTree("./temp/inner", true));
}
