#include <gtest/gtest.h>

#include "long_number.hpp"

TEST(get_digits_number, check_positive) {
	IBusko::LongNumber x("141516");
	ASSERT_EQ(6, x.get_digits_number())
		<< "Неправильно подсчитано количество разрядов в числе " << x;
}


TEST(get_digits_number, check_negative) {
	IBusko::LongNumber x("-1");
	ASSERT_EQ(1, x.get_digits_number())
		<< "Неправильно подсчитано количество разрядов в числе " << x;
}

class EqualityFixture : public testing::Test {
	public:
		IBusko::LongNumber one_v1 = IBusko::LongNumber("1");
		IBusko::LongNumber one_v2 = IBusko::LongNumber("1");
		IBusko::LongNumber twelve = IBusko::LongNumber("12");
		IBusko::LongNumber eleven = IBusko::LongNumber("11");
		IBusko::LongNumber negative_one = IBusko::LongNumber("-1");
		IBusko::LongNumber one_hundred_thirty_two = IBusko::LongNumber("132");
		IBusko::LongNumber negative_twelve = IBusko::LongNumber("-12");
		IBusko::LongNumber big_num = IBusko::LongNumber("123456789");
};
//Equality operator
TEST_F(EqualityFixture, equal) {
	ASSERT_TRUE(one_v1 == one_v2) << "Проверка " << one_v1 << " == " << one_v2;
}
TEST_F(EqualityFixture, not_equal) {
	ASSERT_FALSE(one_v1 == twelve) << "Проверка " << one_v1 << " == " << twelve;
}
TEST_F(EqualityFixture,not_equal_negative_var_12){
	ASSERT_FALSE(twelve == negative_twelve)
		<< "Проверка " << twelve << " == " << negative_twelve;

}
TEST_F(EqualityFixture, not_equal_negative_var_1) {
	ASSERT_FALSE(one_v1 == negative_one) 
		<< "Проверка " << one_v1 << " == " << negative_one;
}
//Greater than operator
TEST_F(EqualityFixture, long_num_greater_comparison) {
	ASSERT_TRUE(big_num > one_v1) << "Проверка " << big_num << " > " << one_v2;
}
TEST_F(EqualityFixture, equal_module_different_sign_greater_comparison) {
	ASSERT_TRUE(twelve > negative_twelve) << "Проверка " << twelve << " > " << negative_twelve;
}
//Smaller than operator
TEST_F(EqualityFixture, equal_module_different_sign_smaller_comparison) {
	ASSERT_FALSE(twelve < negative_twelve) << "Проверка " << twelve << " < " << negative_twelve;
}
TEST_F(EqualityFixture, long_num_smaller_comparison) {
	ASSERT_FALSE(big_num < one_v1) << "Проверка " << big_num << " < " << one_v2;
}
//Plus
TEST_F(EqualityFixture, plus_equal_length) {
	IBusko::LongNumber two = one_v1 + one_v2;
	ASSERT_TRUE(two == IBusko::LongNumber("2")) << "Проверка " << one_v1 << " + " << one_v2;
}
TEST_F(EqualityFixture, plus_different_length) {
	IBusko::LongNumber thirteen = twelve + one_v1;
	ASSERT_TRUE(thirteen == IBusko::LongNumber("13")) << "Проверка " << one_v1 << " + " << twelve;
}
TEST_F(EqualityFixture, plus_different_signs) {
	IBusko::LongNumber negative_eleven = negative_twelve + one_v1;
	ASSERT_TRUE(negative_eleven == IBusko::LongNumber("-11")) << "Проверка " << negative_twelve << " + " << one_v1;
}

//Substraction
TEST_F(EqualityFixture, Subtract) {
	IBusko::LongNumber substraction = twelve - eleven;
	ASSERT_EQ(one_v1, substraction);
}
TEST_F(EqualityFixture, Subtract_minus) {
	IBusko::LongNumber substraction = eleven - twelve;
	ASSERT_EQ(negative_one, substraction);
}
//Multiplication
TEST_F(EqualityFixture, multiply) {
	IBusko::LongNumber multiply =  twelve * eleven;
	ASSERT_EQ(one_hundred_thirty_two, multiply);
}

//Division
TEST_F(EqualityFixture, divide) {
	IBusko::LongNumber divide = one_hundred_thirty_two / eleven;
	ASSERT_EQ(twelve, divide);
}

//Modulo
TEST_F(EqualityFixture, modulo) {
	IBusko::LongNumber modulo = twelve % eleven;
	ASSERT_EQ(one_v1, modulo);
}

//friend
TEST_F(EqualityFixture, std_out) {
	testing::internal::CaptureStdout();
	std::cout << twelve;
	std::string out = testing::internal::GetCapturedStdout();
	ASSERT_EQ("12", out);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
