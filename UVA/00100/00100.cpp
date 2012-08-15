#include <iostream>
#include <vector>

template<typename T = int>
class BlackBox 
{

public:
    BlackBox(T maxsize) : tablesize_(maxsize)
    {
        table_ = std::vector<T>(maxsize, 0);
        // Seed the table for values 0 and 1
        // Note: 0 treated as odd=> 0: 3*(0) + 1 => 1
        // Sequence 0 1 => length = 2
        table_[0] = 2;
        table_[1] = 1;
    }
    ~BlackBox()
    { }

    void print()
    {
        printf("%d ", current_);
    }

    void printn()
    {
        printf("\n");
    }

    // compute the length of the sequence started from 'current' if not
    // found in the table, we will compute the sequence storing each
    // value on a 'stack' so we can update it along with the final value
    // sequence S=>
    // compute(S[0]) => length(S)
    // compute(S[1]) => length(S) - 1
    // ...
    // compute(S[n-1]) => 1

    std::size_t compute(T current)
    {
        std::size_t count = 0;

        if (current < tablesize_ && table_[current]) {
            //std::cout << "=> " << current << " ";
            return table_[current];
        }

        // Not in table, increment operation count and
        // perform at least one operation
        stack_.push_back(current);
        count++;

        //std::cout << current << " ";
        // Detect odd (1s bit)
        if ((current & 0x01)) 
        {
            // odd
            // 3n+1
            current = 3 * current + 1;

            //std::cout << current << " ";
            // After performing an expensive 3n+1 operation
            // the number will always be even, so increase
            // count and perform divide by two operation
            stack_.push_back(current);
            count++;
        }

        // even
        // divide by two
        current = current >> 1;

        return (count + compute(current));
    }

    // if compute() put anything on the stack, we will update the table
    // containing the sequence lengths
    // compute(index]) = table[index]
    void update_table()
    {
        T thecount = count_;
        typename std::vector<T>::iterator it = stack_.begin();
        typename std::vector<T>::iterator it_end = stack_.end();

        for ( ; it != it_end; it++) 
        {
            T index = *it;

            if (index < tablesize_)
                table_[index] = thecount;

            thecount--;
        }
    }

    // find the longest sequence over the range [start, end]
    void start(T start, T end)
    {
        T index;

        maxcount_ = 0;

        if (end < start) {
            std::swap(start, end);
        }

        for (index = start; index <= end; index++) {
            current_ = index;
            count_ = 1;

            stack_.clear();

            count_ = compute(index);

            if (!stack_.empty())
                update_table();

            if (count_ > maxcount_)
                maxcount_ = count_;
        }

    }

    std::size_t max() { return maxcount_; }

protected:

private:
    std::vector<T> table_;
    std::vector<T> stack_;
    std::size_t tablesize_;
    T input_;
    T current_;
    std::size_t count_;
    std::size_t maxcount_;
};

// usage: ./100
//
// on each line enter a range, n m
// where 0 <= n,m <= tablesize
// the output will be
// n m MAXSEQLENGTH
int main(int argc, char *argv[])
{
    // Table size for tracking (FULL SIZE)
    long long const tablesize = 1000000;

    // TODO:
    // Could consider splitting the table in half since
    // for even_num/2 => odd num
    // the sequence length is given by:
    // table[even_num] = table[even_num/2] + 1
    // Potentially good idea?

    BlackBox<long long> box(tablesize);
    long long start;
    long long end;

    while (std::cin >> start >> end)
    {

        box.start(start, end);

        std::cout << start << " " << end << " " << box.max() << "\n";
    }
    return 0;
}