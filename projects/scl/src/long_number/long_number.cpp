#include "long_number.hpp"

namespace IBusko {
	LongNumber::LongNumber() {
		numbers = new int [1]{0};
		sign = POSITIVE;
		length = 1;
	}
	
	LongNumber::LongNumber(const char* const str) {
		if (str[0] == MINUS) {
			length = get_length(str);
			numbers = new int[length];
			sign = NEGATIVE;
			for (int i = 1; i < length; i++) {
				numbers[i - 1] = str[i];
			}
		}
		else {
			length = get_length(str);
			numbers = new int[length];
			sign = POSITIVE;
			for (int i = 0; i < length; i++) {
				numbers[i] = str[i];
			}
		}
		

	}
	
	LongNumber::LongNumber(const LongNumber& x) {
		length = x.length;
		sign = x.sign;
		numbers = x.numbers;
	}
	
	LongNumber::LongNumber(LongNumber&& x) {
		length = x.length;
		sign = x.sign;
		numbers = x.numbers;
	{
		x.numbers = nullptr;
		x.sign = x.length = 0;
	}
	}
	
	LongNumber::~LongNumber() {
		delete[] numbers;
	}
	
	LongNumber& LongNumber::operator = (const char* const str) {
		if (this->numbers == LongNumber(str).numbers && sign == LongNumber(str).sign) {
			if (str[0] == MINUS) {
				length = get_length(str);
				numbers = new int[length];
				sign = NEGATIVE;
				for (int i = 1; i < length; i++) {
					numbers[i - 1] = str[i];
				}
			}
			else {
				length = get_length(str);
				numbers = new int[length];
				sign = POSITIVE;
				for (int i = 0; i < length; i++) {
					numbers[i] = str[i];
				}
			}

		}
		return *this;
	}
	
	LongNumber& LongNumber::operator = (const LongNumber& x) {
		if (&x != this) {
			length = x.length;
			sign = x.sign;
			numbers = x.numbers;
		}
		return *this;
	}
	
	LongNumber& LongNumber::operator = (LongNumber&& x) {
		if (&x != this) {
			delete numbers;
			numbers = x.numbers;
			length = x.length;
			sign = x.sign;
			x.length = 0;
			x.sign = 0;
		}
		return *this;
	}
	
	bool LongNumber::operator == (const LongNumber& x) const {
		if (sign == x.sign) {
			if (length == x.length) {
				for (int i = 0; i < length; i++) {
					if (numbers[i] != x.numbers[i]) {
						return false;
					}
				}return true;
			}
			else
				return false;
				
		}
		else  
			return false;
	}
	
	bool LongNumber::operator > (const LongNumber& x) const {
		if (sign == x.sign) {
			if (sign == POSITIVE) {
				if (length == x.length) {
					for (int i = 0; i < length; i++) {
						if (numbers[i] < x.numbers[i]) {
							return false;
						}
						return true;
					}
				}
				else {
					if (length > x.length) {
						return true;
					}
					else {
						return false;
					}
				}
			}
			else {
				if (length == x.length) {
					for (int i = 0; i < length; i++) {
						if (numbers[i] > x.numbers[i]) {
							return false;
						}
						return true;
					}
				}
				else {
					if (length > x.length) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
		else {
			if (sign > x.sign) {
				return true;
			}
			else {
				return false;
			}
		}

	}
	
	bool LongNumber::operator < (const LongNumber& x) const{
		return !LongNumber::operator > (x);
	}


	LongNumber LongNumber::operator + (const LongNumber& x) const {
		LongNumber result;
		if (sign != x.sign) {
			if (sign == NEGATIVE) {
				LongNumber y = LongNumber(*this);
				y.sign = POSITIVE;
				return x - y;
			}
			else {
				LongNumber y = LongNumber(x);
				y.sign = POSITIVE;
				return *this - y;
			}
		}
		
		else {
			LongNumber result;
			int max_length = length > x.length ? length : x.length;
			int min_length = length < x.length ? length : x.length;
			int length_dif = max_length - min_length;
			result.length = max_length + 1;
			result.numbers = new int[result.length];
			int* temp = new int[result.length];
			int next = 0;
			if (length_dif == 0) {
				for (int i = min_length - 1; i >= 0; i--) {
					int num_tmp = numbers[i] + x.numbers[i];

					temp[length_dif + i] = num_tmp % 10 + next;
					if ((num_tmp / 10) == 0) {
						next = 0;
					}
					else {
						next = 1;
						num_tmp -= 10;

					}
				}
				result.numbers = temp;
			}
			else {
				if (max_length == length) {
					for (int i = min_length - 1; i >= 0; i--) {
						int num_tmp = numbers[i + length_dif] + x.numbers[i];

						temp[length_dif + i] = num_tmp % 10 + next;
						if ((num_tmp / 10) == 0) {
							next = 0;
						}
						else {
							next = 1;

						}
					}
				}
				else {
					for (int i = min_length - 1; i >= 0; i--) {
						int num_tmp = numbers[i] + x.numbers[i + length_dif];

						temp[length_dif + i] = num_tmp % 10 + next;
						if ((num_tmp / 10) == 0) {
							next = 0;
						}
						else {
							next = 1;

						}
					}
				}
				result.numbers = temp;
				result.sign = sign;
			}
		}
		


		
		return result;
	}
	
	LongNumber LongNumber::operator - (const LongNumber& x) const {
		LongNumber result;

		if (sign != x.sign) {
			if (sign == POSITIVE) {
				x.sign = POSITIVE;
				return *this + LongNumber(x);
			}
			else {
				x.sign = NEGATIVE;
				return *this + LongNumber(x);
			}
		}
		else {
			if (*this == x) {
				return LongNumber("0");
			}
			if (*this < x) {
				result = (LongNumber(x) - LongNumber(*this));
				result.sign = NEGATIVE;
				return result;
			}

			
			int max_length = length > x.length ? length : x.length;
			int min_length = length < x.length ? length : x.length;
			int dif_length = max_length - min_length;
			result.length = max_length;
			int* temp = new int[result.length];
			int take = 0;
			
			if (length == x.length) {
				for (int i = length - 1; i >= 0; i--) {
					int dif = 0;
					if (take == 1) {
						dif--;
					}
					if (numbers[i] > x.numbers[i]) {
						dif += numbers[i] - x.numbers[i] - take;
						take = 0;
					}
					if (numbers[i] < x.numbers[i]) {
						dif += numbers[i] - x.numbers[i] + 10 - take;
						take = 1;
						if (numbers[i] == x.numbers[i]) {
							if (take == 1) {
								dif = 9;
							}
							else {
								dif = 0;
							}
						}
					}
				}
			}
			else {
				if (max_length == length) {
					for (int i = min_length - 1; i >= dif_length; i--) {
						int dif = 0;
						if (take == 1) {
							dif--;
						}
						if (numbers[i + dif_length] > x.numbers[i]) {
							dif += numbers[i] - x.numbers[i] - take;
							take = 0;
						}
						if (numbers[i + dif_length] < x.numbers[i]) {
							dif += numbers[i+dif_length] - x.numbers[i] + 10 - take;
							take = 1;
							if (numbers[i + dif_length] == x.numbers[i]) {
								if (take == 1) {
									dif = 9;
								}
								else {
									dif = 0;
								}
							}
						}
					}
				}
				else {
					for (int i = min_length - 1; i >= dif_length; i--) {
						int dif = 0;
						if (take == 1) {
							dif--;
						}
						if (numbers[i] > x.numbers[i + dif_length]) {
							dif += numbers[i] - x.numbers[i] - take;
							take = 0;
						}
						if (numbers[i] < x.numbers[i + dif_length]) {
							dif += numbers[i] - x.numbers[i + dif_length] + 10 - take;
							take = 1;
							if (numbers[i] == x.numbers[i + dif_length]) {
								if (take == 1) {
									dif = 9;
								}
								else {
									dif = 0;
								}
							}
						}
					}
				}
				result.numbers = temp;
				return result;
			}
		}
		
	}
	
	LongNumber LongNumber::operator * (const LongNumber& x) const{
		LongNumber result;
		if (*this == LongNumber("0") || x == LongNumber("0")) {
			return LongNumber();
		}
		result.length = length + x.length;
		int* temp = new int[result.length];
		
		for (int i = length - 1; i >= 0; i--) {
			int save = 0;
			for (int j = x.length - 1; j >= 0; j--) {
				int multiply = numbers[i] * x.numbers[j] + temp[i + j + 1] + save;
				temp[i + j + 1] = multiply % 10;
				save = multiply / 10;
			}
			temp[i] += save;
		}
		
		result.numbers = temp;
		if (sign != x.sign) {
			result.sign = NEGATIVE;
		}
		else {
			result.sign = POSITIVE;
		}
		return result;
	}
	
	LongNumber LongNumber::operator / (const LongNumber& x) const{
		if (*this == LongNumber("0")) {
			return LongNumber();
		}
		if (x == LongNumber("0")) {
			throw std::runtime_error("Division by zero is prohibited!");
		}
		LongNumber result;

		LongNumber dividend(*this);
		LongNumber divisor(x);
		int quotient = 0;
		if (dividend == divisor) {
			result = LongNumber("1");
		}
		while (dividend > divisor) {
			dividend = dividend - divisor;
			result = result + LongNumber("1");
		}
		if (sign == x.sign) {
			result.sign = POSITIVE;
		}
		else {
			result.sign = NEGATIVE;
		}
		return result;
	}
	
	LongNumber LongNumber::operator % (const LongNumber& x) const{
		if (x == LongNumber("0")) {
			throw std::runtime_error("Division by zero is prohibited!");
		}
		if (x == LongNumber("1") || x == LongNumber("-1")) {
			return LongNumber("0");
		}

		LongNumber dividend(*this);
		LongNumber divisor(x);

		if (sign == x.sign) {
			if (sign == POSITIVE) {
				while (dividend > divisor) {
					dividend = dividend - divisor;
				}
				dividend.sign = POSITIVE;

			}
			else {
				dividend.sign = POSITIVE;
				divisor.sign = POSITIVE;
				while (dividend > divisor) {
					dividend = dividend - divisor;
				}
				dividend.sign = NEGATIVE;
			}
		}
		else {
			if (sign == POSITIVE) {
				dividend.sign = NEGATIVE;
				divisor.sign = POSITIVE;

				while (dividend < divisor) {
					dividend = dividend + divisor;
				}
				dividend.sign = NEGATIVE;
			}

			else {
				

				while (dividend < divisor) {
					dividend = dividend + divisor;
				}
			}
		}
		LongNumber result = dividend;
		return result;
	}
	
	int LongNumber::get_digits_number() const {
		return length;
	}
	
	bool LongNumber::is_positive() const {
		return sign == POSITIVE;
	}
	
	
	
	// ----------------------------------------------------------
	// PRIVATE
	// ----------------------------------------------------------
	int LongNumber::get_length(const char* const str) {
		length = 0;
		while (str[length] != END) length++;
		if (str[0] == MINUS) {
			length--;
		};
		return length;
	}

	
	// ----------------------------------------------------------
	// FRIENDLY
	// ----------------------------------------------------------
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.NEGATIVE) {
			os << '-';
		}
		for (int i = 0; i < x.length; ++i) {
			os << x.numbers[i];
		}
		return os;
	}
}
