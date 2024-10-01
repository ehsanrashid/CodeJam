class BigInt final {
   public:
    using Digits = std::vector<std::uint8_t>;

    // Constructor to initialize BigInt from an integer
    BigInt(int64_t n) {
        sign = (n < 0);   // Set the sign
        n = std::abs(n);  // Work with the absolute value of n

        // Store digits in reverse order
        do {
            push(n % 10);
            n /= 10;
        } while (n != 0);
    }

    BigInt() : BigInt(0) {}

    BigInt(const std::string& str) {
        if (str.empty())
        {
            push(0);
            return;
        }

        auto end = str.rend() - 1;
        while (*end == ' ') --end;
        sign = false;
        if (!std::isdigit(*end)) sign = *(end--) == '-';

        auto beg = str.rbegin();
        while (*beg == ' ') ++beg;
        for (auto itr = beg; itr <= end; ++itr)
        {
            assert(std::isdigit(*itr));
            push(*itr - '0');
        }
    }
    // Constructor to initialize BigInt from a vector of digits and a sign
    BigInt(const Digits& d, bool s) : digits(d), sign(s) {}

    auto begin() const noexcept { return digits.begin(); }
    auto end() const noexcept { return digits.end(); }
    auto rbegin() const noexcept { return digits.rbegin(); }
    auto rend() const noexcept { return digits.rend(); }

    auto begin() noexcept { return digits.begin(); }
    auto end() noexcept { return digits.end(); }
    auto rbegin() noexcept { return digits.rbegin(); }
    auto rend() noexcept { return digits.rend(); }

    auto size() const noexcept { return digits.size(); }
    bool empty() const noexcept { return digits.empty(); }

    auto front() const noexcept { return digits.front(); }
    auto back() const noexcept { return digits.back(); }

    auto& front() noexcept { return digits.front(); }
    auto& back() noexcept { return digits.back(); }

    auto operator[](std::size_t idx) const noexcept { return digits[idx]; }
    auto& operator[](std::size_t idx) noexcept { return digits[idx]; }

    void insert(uint8_t d) noexcept { digits.insert(digits.begin(), d); }
    void push(uint8_t d) noexcept { digits.push_back(d); }
    void pop() noexcept { digits.pop_back(); }
    void clear() noexcept { digits.clear(); }

    void read(const string &s) {
        sign = false;
        clear();
        int base_digits = 9;
        int pos = 0;
        while (pos < int(s.size()) && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = true;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits)
        {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            push(x);
        }
        trim();
    }

    std::int64_t longValue() const {
        int64_t value = 0;
        for (auto itr = rbegin(); itr != rend(); ++itr)
            value = value * 10 + *itr;
        return sign ? -value : +value;
    }
    // Value operator
    explicit operator std::int64_t() const noexcept {
        return longValue();
    }

    bool isZero() const noexcept {
        return empty() || (size() == 1 && digits[0] == 0);
    }

    BigInt operator-() const noexcept {
        BigInt res = *this;
        res.sign = -sign;
        return res;
    }
    
    BigInt abs() const {
        BigInt res = *this;
        res.sign = false;
        return res;
    }

    // Comparison for equality (needed for division)
    bool operator==(const BigInt& big) const noexcept {
        //return !(*this < big) && !(big < *this);
        return sign == big.sign && digits == big.digits;
    }
    bool operator!=(const BigInt& big) const noexcept {
        //return *this < big || big < *this;
        return !(*this == big);
    }
    bool operator<(const BigInt &big) const noexcept {
        if (sign != big.sign)
            return sign && !big.sign;
        if (size() != big.size())
            return sign ? size() > big.size() : size() < big.size();

        auto [mm1, mm2] = std::mismatch(rbegin(), rend(), big.rbegin(), big.rend());
        if (mm1 != rend() && mm2 != big.rend())
            return sign ? *mm1 > *mm2 : *mm1 > *mm2;
        return false;
    }
    bool operator>(const BigInt &big) const noexcept {
        return big < *this;
    }
    bool operator<=(const BigInt &big) const noexcept {
        return !(big < *this);
    }
    bool operator>=(const BigInt &big) const noexcept {
        return !(*this < big);
    }

    void trim() {
        while (!empty() && back() == 0)
            pop();
        if (empty())
            sign = false;
    }

    // Addition operator
    BigInt operator+(const BigInt& big) const noexcept {
        if (sign == big.sign)
        {
            // Same sign: Add the absolute values and keep the sign
            return {add(digits, big.digits), sign};
        }
        else
        {
            // Different signs: Subtract the smaller absolute value from the greater
            // and keep sign of greater
            if (absGreaterThan(digits, big.digits))
                return {subtract(digits, big.digits), sign};
            else
                return {subtract(big.digits, digits), big.sign};
        }
    }
    BigInt& operator+=(const BigInt& big) noexcept {
        *this = *this + big;
        return *this;
    }

    // Subtraction operator
    BigInt operator-(const BigInt& big) const noexcept {
        if (sign == big.sign)
        {
            // Same sign: Subtract the smaller absolute value from the larger
            // and change sign accordingly.
            if (absGreaterThan(digits, big.digits))
                return {subtract(digits, big.digits), sign};
            else
                return {subtract(big.digits, digits), !sign};
        }
        else
        {
            // Different signs: Add the absolute values
            // and keep the sign of the first operand.
            return {add(digits, big.digits), sign};
        }
    }
    BigInt& operator-=(const BigInt& big) noexcept {
        *this = *this - big;
        return *this;
    }

    // Multiplication operator
    BigInt operator*(const BigInt& big) const noexcept {
        return {multiply(digits, big.digits),
                (sign && !big.sign) || (!sign && big.sign)};
    }
    BigInt& operator*=(const BigInt& big) noexcept {
        *this = *this * big;
        return *this;
    }

    // Division operator
    BigInt operator/(const BigInt& big) const noexcept {
        if (big == BigInt(0))
            // throw std::runtime_error("Division by zero");
            cerr << "Division by zero";

        auto [quotient, _] = divide(digits, big.digits);
        return {quotient, (sign && !big.sign) || (!sign && big.sign)};
    }
    BigInt& operator/=(const BigInt& big) noexcept {
        *this = *this / big;
        return *this;
    }

    // Modulus operator
    BigInt operator%(const BigInt& big) const noexcept {
        if (big == BigInt(0))
            // throw std::runtime_error("Modulus by zero");
            cerr << "Modulus by zero";
        /*
        BigInt quotient  = *this / big;      // Divide to get quotient
        BigInt product   = quotient * big;   // Multiply quotient by divisor
        BigInt remainder = *this - product;  // Subtract product from the original BigInt
        */

        auto [_, remainder] = divide(digits, big.digits);

        return {remainder, sign};
    }
    BigInt& operator%=(const BigInt& big) noexcept {
        *this = *this % big;
        return *this;
    }

    // Multiply BigInt by an integer
    BigInt operator*(int64_t num) const noexcept {
        BigInt result = *this;
        if (num < 0)
        {
            num = -num;
            result.sign = !(result.sign);
        }
        uint16_t carry = 0;
        std::for_each(result.begin(), result.end(),
        [=, &carry](uint8_t& d) {
            int mul = d * num + carry;
            d     = mul % 10;  // Store last digit
            carry = mul / 10;  // Carry forward
        });

        // Add remaining carry to result
        while (carry)
        {
            result.push(carry % 10);
            carry /= 10;
        }
        return result;
    }

    BigInt& operator*=(int64_t num) noexcept {
        *this = *this * num;
        return *this;
    }

    BigInt operator/(int64_t num) const noexcept {
        BigInt result = *this;
        if (num < 0)
        {
            num = -num;
            result.sign = !(result.sign);
        }
        uint16_t rem = 0;
        std::for_each(result.rbegin(), result.rend(),
        [=, &rem](uint8_t& d) {
            int div = d + rem * 10;
            d   = div / num;
            rem = div % num;
        });
        result.trim();

        return result;
    }

    BigInt& operator/=(int64_t num) noexcept {
        *this = *this / num;
        return *this;
    }
    BigInt operator%(int64_t num) const noexcept {
        if (num < 0)
            num = -num;
        int m = 0;
        std::for_each(rbegin(), rend(),
        [=, &m](uint8_t d) {
            m = (d + m * 10) % num;
        });
        if (sign) m = -m;
        return {m};
    }
    BigInt& operator%=(int64_t num) noexcept {
        *this = *this % num;
        return *this;
    }
    // Function to calculate factorial of BigInt
    BigInt operator!() const noexcept {
        BigInt fac = 1;  // Start with 1 for 0! and 1!
        auto num = std::int64_t(*this);
        for (int64_t i = 2; i <= num; ++i)
            fac *= i;
        return fac;
    }

    uint64_t sum_digits() const noexcept {
        uint64_t digitSum = 0;
        for (auto itr = begin(); itr < end(); ++itr)
            digitSum += *itr;
        return digitSum;
    }

    BigInt pow_mod(int exp, uint64_t mod) const noexcept {
        BigInt pow = 1;
        BigInt base = *this;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                pow = (pow * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return pow;
    }

    std::string to_string(bool signShow = false) const noexcept {
        std::ostringstream oss;
        if (sign && !(size() == 1 && digits[0] == 0))
            oss << '-';  // Print the negative sign if number is negative
        else if (signShow)
            oss << '+';
        oss << (empty() ? 0 : back());
        for (auto itr = rbegin() + 1; itr != rend(); ++itr)
            oss << int(*itr);

        return oss.str();
    }

    friend BigInt gcd(const BigInt &a, const BigInt &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend BigInt lcm(const BigInt &a, const BigInt &b) {
        return a / gcd(a, b) * b;
    }

   private:
    // Compare absolute values of two BigInts
    static bool absGreaterThan(const Digits& d1, const Digits& d2) noexcept {
        if (d1.size() != d2.size())
            return d1.size() > d2.size();

        auto [mm1, mm2] = std::mismatch(d1.rbegin(), d1.rend(), d2.rbegin(), d2.rend());
        if (mm1 != d1.rend() && mm2 != d2.rend())
            return *mm1 > *mm2;
        return false;
    }

    // Remove leading zeroes
    static void trim(Digits& d) noexcept {
        while (d.size() > 1 && d.back() == 0)
            d.pop_back();
    }

    // Helper function for adding two digit arrays
    static Digits add(const Digits& d1, const Digits& d2) noexcept {
        Digits result;

        size_t n = std::max(d1.size(), d2.size());
        int sum = 0;
        for (size_t i = 0; i < n || sum; ++i)
        {
            if (i < d1.size()) sum += d1[i];
            if (i < d2.size()) sum += d2[i];

            result.push_back(sum % 10);
            sum /= 10;
        }
        return result;
    }

    // Helper function for subtracting two digit arrays (assuming d1 >= d2)
    static Digits subtract(const Digits& d1, const Digits& d2) noexcept {
        Digits result;

        bool borrow = false;
        for (size_t i = 0; i < d1.size(); ++i)
        {
            int diff = d1[i] - borrow;

            if (i < d2.size()) diff -= d2[i];

            if (diff < 0)
            {
                diff += 10;
                borrow = true;
            }
            else
                borrow = false;
            result.push_back(diff);
        }

        trim(result);

        return result;
    }

    // Helper function for multipling two digit arrays
    static Digits multiply(const Digits& d1, const Digits& d2) noexcept {
        Digits result(d1.size() + d2.size(), 0);

        for (size_t i = 0; i < d1.size(); ++i)
        {
            int carry = 0;
            for (size_t j = 0; j < d2.size() || carry; ++j) {
                int mul =
                    result[i + j] + d1[i] * (j < d2.size() ? d2[j] : 0) + carry;
                result[i + j] = mul % 10;
                carry = mul / 10;
            }
        }

        trim(result);
    
        return result;
    }

    // Helper function for dividing two digit arrays (returns quotient)
    static std::pair<Digits, Digits> divide(const Digits& d1,
                                            const Digits& d2) noexcept {
        Digits remainder;
        Digits quotient;

        for (auto itr = d1.rbegin(); itr != d1.rend(); ++itr)
        {
            remainder.insert(remainder.begin(), *itr);
            trim(remainder);

            // Find how many times 'd2' fits into 'remainder'
            int count = 0;
            while (absGreaterThan(remainder, d2) || remainder == d2)
            {
                remainder = subtract(remainder, d2);
                ++count;
            }

            // Add the count to the quotient
            quotient.insert(quotient.begin(), count);
        }

        trim(quotient);

        return {quotient, remainder};
    }

    friend std::istream& operator>>(std::istream &is, BigInt &big) {
        std::string s;
        is >> s;
        big.read(s);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const BigInt& big) {
        os << big.to_string();

        return os;
    }

    Digits digits;  // Store digits in reverse order
    bool sign;      // Sign of the number: [false for +ve, true for -ve]
};

