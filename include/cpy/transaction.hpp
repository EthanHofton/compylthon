#ifndef __CPY_TRANSACTION_HPP__
#define __CPY_TRANSACTION_HPP__

#include <cstddef>
#include <stack>

namespace cpy {

struct transaction {
    size_t pos_restore;
    size_t pos_current;

    transaction(size_t pos) : pos_restore(pos), pos_current(pos) {}
};

class transaction_manager {
public:

    inline void start() {
        m_transactions.emplace(pos());
    }
    inline void commit() {
        auto transaction = m_transactions.top();
        m_transactions.pop();
        pos() = transaction.pos_current;
    }
    inline void rollback() {
        auto transaction = m_transactions.top();
        m_transactions.pop();
        pos() = transaction.pos_restore;
    }
    inline size_t& pos() {
        return m_transactions.empty() ? m_pos : m_transactions.top().pos_current;
    }

    inline const size_t& pos() const {
        return m_transactions.empty() ? m_pos : m_transactions.top().pos_current;
    }

private:

    size_t m_pos = 0;
    std::stack<transaction> m_transactions;

};

} // namespace cpy

#endif // __CPY_TRANSACTION_HPP__
