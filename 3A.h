#include <random>

class HashFunction;
class HashTable;

int64_t SumOfSquares(const std::vector<int>& numbers);
template <class RandomGenerator>
HashFunction GenerateRandomHashFunction(RandomGenerator& generator);
template <class Predicate, class RandomGenerator>
HashFunction GenerateHashFunctionByPredicate(const std::vector<int>& numbers, size_t m,
                                             Predicate pred, RandomGenerator& generator);
bool HasNoCollisions(const HashTable& hash_table);

class HashFunction {
public:
    HashFunction() = default;
    HashFunction(size_t a, size_t b, size_t p) : a_(a), b_(b), p_(p) {
    }

    size_t operator()(int x) const {
        return ((static_cast<uint64_t>(a_) * x) + b_) % p_; // (a * x + b) mod p.
    }

private:
    size_t a_;
    size_t b_;
    size_t p_;
};

class HashTable {
public:
    HashTable() = default;
    HashTable(const HashFunction& f, size_t m) : f_(f), m_(m) {
    }

    void Initialize(const std::vector<int>& numbers) {
        std::vector<std::vector<int>> table(m_);
        for (auto x : numbers) {
            size_t index = f_(x) % m_;
            table[index].push_back(x);
        }
        hash_table_ = std::move(table);
    }

    bool Contains(int number) const {
        if (m_ == 0) {
            return false;
        }
        size_t i = f_(number) % m_;

        if (hash_table_[i].empty()) {
            return false;
        }

        if (hash_table_[i][0] == number) {
            return true;
        }

        return false;
    }

    HashFunction GetHashFunction() const {
        return f_;
    }

    std::vector<int> DistributionByBuckets() const {
        std::vector<int> distribution(m_);
        size_t i = 0;
        for (const auto& bucket : hash_table_) {
            distribution[i] = static_cast<int>(bucket.size());
            i++;
        }
        return distribution;
    }

    friend class FixedSet;

private:
    std::vector<std::vector<int>> hash_table_;
    HashFunction f_; // хэш функция, с помощью которой строится таблица.
    size_t m_; // число бакетов.

    std::vector<std::vector<int>> GetHashTable() const {
        return hash_table_;
    }

    size_t Size() const {
        return m_;
    }
};

class FixedSet {
public:
    FixedSet() = default;

    void Initialize(const std::vector<int>& numbers) {
        std::mt19937 generator;
        if (numbers.empty()) {
            hash_table_ = HashTable(GenerateRandomHashFunction(generator), 0);
            return;
        }
        size_t m = numbers.size() * 2;
        auto predicate = [&](const HashTable& hash_table) {
            return SumOfSquares(hash_table.DistributionByBuckets())
                    <= 3 * static_cast<int64_t>(numbers.size()); };

        auto f = GenerateHashFunctionByPredicate(
                numbers, numbers.size() * 2, predicate, generator);
        hash_table_ = HashTable(f, m);
        hash_table_.Initialize(numbers);

        std::vector<HashTable> tables;
        for (const auto& bucket : hash_table_.GetHashTable()) {
            auto function = GenerateHashFunctionByPredicate(
                    bucket, bucket.size() * bucket.size(), HasNoCollisions, generator);
            auto table = HashTable(function, bucket.size() * bucket.size());
            table.Initialize(bucket);
            tables.push_back(table);
        }
        tables_ = std::move(tables);
    }

    bool Contains(int number) const {
        size_t m = hash_table_.Size();
        if (m == 0) {
            return false;
        }
        auto f = hash_table_.GetHashFunction();
        size_t index = f(number) % m;

        return tables_[index].Contains(number);
    }

private:
    HashTable hash_table_;
    std::vector<HashTable> tables_;
};

int64_t SumOfSquares(const std::vector<int>& numbers) {
    int64_t sum_of_squares = 0;
    for (auto num : numbers) {
        sum_of_squares += num * static_cast<int64_t>(num);
    }
    return sum_of_squares;
}

template <class RandomGenerator>
HashFunction GenerateRandomHashFunction(RandomGenerator& generator) {
    size_t p = 2000000011;
    // простое число такое, чтобы все числа из диапазона [-10^9, 10^9] имели разные вычеты.

    std::uniform_int_distribution<std::mt19937::result_type> dist(1, p - 1);
    size_t a = dist(generator);
    size_t b = dist(generator);

    return {a, b, p};
}

template <class Predicate, class RandomGenerator>
HashFunction GenerateHashFunctionByPredicate(const std::vector<int>& numbers, size_t m,
                                             Predicate pred, RandomGenerator& generator) {
    HashTable hash_table(GenerateRandomHashFunction(generator), m);
    hash_table.Initialize(numbers);
    while (!pred(hash_table)) {
        HashTable table(GenerateRandomHashFunction(generator), m);
        table.Initialize(numbers);
        hash_table = std::move(table);
    }
    return hash_table.GetHashFunction();
}

bool HasNoCollisions(const HashTable& hash_table) {
    auto distribution = hash_table.DistributionByBuckets();
    for (auto num : distribution) {
        if (num > 1) {
            return false;
        }
    }
    return true;
}
