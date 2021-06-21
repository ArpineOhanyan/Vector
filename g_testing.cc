include "vector.hpp"
#include "gtest/gtest.h"
#include <memory>

namespace {

    TEST(vectortest, def) {
        Vector<float*> vec;
        EXPECT_EQ(0, vec.Size());
        EXPECT_TRUE(vec.Empty());
    }

    TEST(vectortest, with_size) {
        Vector<double> v(12);
        EXPECT_EQ(0, v.Size());
        EXPECT_EQ(12, v.Capacity());
        v.PushBack(0.89);
        v.PushBack(12.9);
        const Vector<double> cv(v);
        EXPECT_EQ(0.89, cv[0]);
    }

    TEST(vectortest, with_value) {
        Vector<int> v(4, 7);
        EXPECT_EQ(4, v.Size());
        EXPECT_LT(4, v.Capacity());
        v.PopBack();
        bool is_out_of_range = false;
        try {
             int k = v[3];
        }
        catch(const std::exception& ex) {
             is_out_of_range = true;
        }
        EXPECT_TRUE(is_out_of_range);
    }

    TEST(vectortest, with_reserve) {
        Vector<int> v(4, 7);
        Vector<int> vec(v);
        EXPECT_EQ(v.Size(), vec.Size());
        v.PushBack(45);
        v.PushBack(5);
        v.PushBack(13);
        const int k = 77;
        for(int i = 0; i < 12; ++i) {
            v.PushBack(k);
        }
        v.PushBack(12);
        EXPECT_EQ(20, v.Size());
        EXPECT_LT(20, v.Capacity());
        EXPECT_GT(v.Size(), vec.Size());
        EXPECT_EQ(77, v[7]);
        v.Reserve(5);
        EXPECT_EQ(5, v.Size());
        EXPECT_EQ(5, v.Capacity());
        EXPECT_EQ(7, v[3]);
        vec.Reserve(15);
        EXPECT_EQ(15, vec.Capacity());
    }

    TEST(vectortest, with_string) {
        Vector<std::string> vstr;
        vstr.Reserve(18);
        for(int i = 0; i < 8; ++i) {
            vstr.PushBack("hello");
        }
        EXPECT_EQ(8, vstr.Size());
        EXPECT_EQ(18, vstr.Capacity());
        Vector<std::string> vstring;
        vstring = vstr;
        EXPECT_EQ(vstring.Capacity(), vstr.Capacity());
    }
    
    TEST(vectortest, with_move) {
        Vector<std::unique_ptr<int>> uvec(3);
        EXPECT_EQ(0, uvec.Size());
        EXPECT_TRUE(uvec.Empty());
        uvec.PushBack(std::unique_ptr<int> (new int(23)));
        uvec.PushBack(std::unique_ptr<int> (new int(239)));
        uvec.PushBack(std::unique_ptr<int> (new int(399)));
        uvec.PushBack(std::unique_ptr<int> (new int(2367)));
        EXPECT_EQ(4, uvec.Size());
        EXPECT_FALSE(uvec.Empty());
        Vector<std::unique_ptr<int>> uv(std::move(uvec));
        EXPECT_EQ(0, uvec.Size());
        EXPECT_TRUE(uvec.Empty());
        EXPECT_EQ(4, uv.Size());
        EXPECT_FALSE(uv.Empty());
        Vector<std::unique_ptr<int>> unic;
        unic = std::move(uv);
        unic.PopBack();
        EXPECT_TRUE(uv.Empty());
        EXPECT_LT(uv.Size(), unic.Size());
    }

    TEST(vectortest, with_shrinktofit) {
        Vector<int> v(1000000, 2300000);
        EXPECT_EQ(1000000, v.Size());
        EXPECT_EQ(1500000, v.Capacity());
        EXPECT_GT(v.Capacity(), v.Size());
        v.ShrinkToFit();
        EXPECT_EQ(1000000, v.Size());
        EXPECT_EQ(v.Capacity(), v.Size());
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

