/* This file is part of VoltDB.
 * Copyright (C) 2008-2010 VoltDB Inc.
 *
 * This file contains original code and/or modifications of original code.
 * Any modifications made by VoltDB Inc. are licensed under the following
 * terms and conditions:
 *
 * VoltDB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VoltDB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VoltDB.  If not, see <http://www.gnu.org/licenses/>.
 */
/* Copyright (C) 2008 by H-Store Project
 * Brown University
 * Massachusetts Institute of Technology
 * Yale University
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef BINARYTREEUNIQUEINDEX_H_
#define BINARYTREEUNIQUEINDEX_H_

//#include <map>
#include "stx/btree_map.h"
#include <iostream>
#include "common/debuglog.h"
#include "common/tabletuple.h"
#include "indexes/tableindex.h"

namespace voltdb {

/**
 * Index implemented as a Binary Unique Map.
 * @see TableIndex
 */
template<typename KeyType, class KeyComparator, class KeyEqualityChecker>
class BinaryTreeUniqueIndex : public TableIndex
{
    friend class TableIndexFactory;
    friend class TableIndexWrapper;

    //typedef std::map<KeyType, const void*, KeyComparator> MapType;
    typedef stx::btree_map<KeyType, const void*, KeyComparator> MapType;

public:

    ~BinaryTreeUniqueIndex() {};

    bool addEntry(const TableTuple* tuple)
    {
        m_tmp1.setFromTuple(tuple, column_indices_, m_keySchema);
        return addEntryPrivate(tuple, m_tmp1);
    }

    bool deleteEntry(const TableTuple* tuple)
    {
        m_tmp1.setFromTuple(tuple, column_indices_, m_keySchema);
        return deleteEntryPrivate(m_tmp1);
    }

    bool replaceEntry(const TableTuple* oldTupleValue,
                      const TableTuple* newTupleValue)
    {
        // this can probably be optimized
        m_tmp1.setFromTuple(oldTupleValue, column_indices_, m_keySchema);
        m_tmp2.setFromTuple(newTupleValue, column_indices_, m_keySchema);
        if (m_eq(m_tmp1, m_tmp2))
        {
            // no update is needed for this index
            return true;
        }

        bool deleted = deleteEntryPrivate(m_tmp1);
        bool inserted = addEntryPrivate(newTupleValue, m_tmp2);
        --m_deletes;
        --m_inserts;
        ++m_updates;
        return (deleted && inserted);
    }
    
    bool setEntryToNewAddress(const TableTuple *tuple, const void* address) {
        // set the key from the tuple 
        m_tmp1.setFromTuple(tuple, column_indices_, m_keySchema);
        ++m_updates; 
        
        m_entries.erase(m_tmp1); 
        std::pair<typename MapType::iterator, bool> retval = m_entries.insert(std::pair<KeyType, const void*>(m_tmp1, address));
        return retval.second;
    }

    bool checkForIndexChange(const TableTuple* lhs, const TableTuple* rhs)
    {
        m_tmp1.setFromTuple(lhs, column_indices_, m_keySchema);
        m_tmp2.setFromTuple(rhs, column_indices_, m_keySchema);
        return !(m_eq(m_tmp1, m_tmp2));
    }

    bool exists(const TableTuple* values)
    {
        ++m_lookups;
        m_tmp1.setFromTuple(values, column_indices_, m_keySchema);
        return (m_entries.find(m_tmp1) != m_entries.end());
    }

    bool moveToKey(const TableTuple* searchKey)
    {
        ++m_lookups;
        m_begin = true;
        m_tmp1.setFromKey(searchKey);
        m_keyIter = m_entries.find(m_tmp1);
        if (m_keyIter == m_entries.end()) {
            m_match.move(NULL);
            return false;
        }
        m_match.move(const_cast<void*>(m_keyIter->second));
        return !m_match.isNullTuple();
    }

    bool moveToTuple(const TableTuple* searchTuple)
    {
        ++m_lookups;
        m_begin = true;
        m_tmp1.setFromTuple(searchTuple, column_indices_, m_keySchema);
        m_keyIter = m_entries.find(m_tmp1);
        if (m_keyIter == m_entries.end()) {
            m_match.move(NULL);
            return false;
        }
        m_match.move(const_cast<void*>(m_keyIter->second));
        return !m_match.isNullTuple();
    }

    void moveToKeyOrGreater(const TableTuple* searchKey)
    {
        ++m_lookups;
        m_begin = true;
        m_tmp1.setFromKey(searchKey);
        m_keyIter = m_entries.lower_bound(m_tmp1);
    }

    void moveToGreaterThanKey(const TableTuple* searchKey)
    {
        ++m_lookups;
        m_begin = true;
        m_tmp1.setFromKey(searchKey);
        m_keyIter = m_entries.upper_bound(m_tmp1);
    }

    void moveToEnd(bool begin)
    {
        ++m_lookups;
        m_begin = begin;
        if (begin)
            m_keyIter = m_entries.begin();
        else
            m_keyRIter = m_entries.rbegin();
    }

    TableTuple nextValue()
    {
        TableTuple retval(m_tupleSchema);

        if (m_begin) {
            if (m_keyIter == m_entries.end())
                return TableTuple();
            retval.move(const_cast<void*>(m_keyIter->second));
            ++m_keyIter;
        } else {
            if (m_keyRIter == (typename MapType::const_reverse_iterator) m_entries.rend())
                return TableTuple();
            retval.move(const_cast<void*>(m_keyRIter->second));
            ++m_keyRIter;
        }

        return retval;
    }

    TableTuple nextValueAtKey()
    {
        TableTuple retval = m_match;
        m_match.move(NULL);
        return retval;
    }

    bool advanceToNextKey()
    {
        if (m_begin) {
            ++m_keyIter;
            if (m_keyIter == m_entries.end())
            {
                m_match.move(NULL);
                return false;
            }
            m_match.move(const_cast<void*>(m_keyIter->second));
        } else {
            ++m_keyRIter;
            if (m_keyRIter == (typename MapType::const_reverse_iterator) m_entries.rend())
            {
                m_match.move(NULL);
                return false;
            }
            m_match.move(const_cast<void*>(m_keyRIter->second));
        }

        return !m_match.isNullTuple();
    }

    size_t getSize() const { return m_entries.size(); }
    int64_t getMemoryEstimate() const {
        return 0;
        // return m_entries.bytesAllocated();
    }
    
    std::string getTypeName() const { return "BinaryTreeUniqueIndex"; };
    std::string debug() const
    {
        std::ostringstream buffer;
        buffer << TableIndex::debug() << std::endl;

        typename MapType::const_iterator i = m_entries.begin();
        while (i != m_entries.end()) {
            TableTuple retval(m_tupleSchema);
            retval.move(const_cast<void*>(i->second));
            buffer << retval.debugNoHeader() << std::endl;
            ++i;
        }
        std::string ret(buffer.str());
        return (ret);
    }
protected:
    BinaryTreeUniqueIndex(const TableIndexScheme &scheme) :
        TableIndex(scheme),
        m_entries(KeyComparator(m_keySchema)),
        m_begin(true),
        m_eq(m_keySchema)
    {
      //std::cout << "BEGIN\t" << scheme.name << "\n";
        m_match = TableTuple(m_tupleSchema);
	//std::cout << "END\t" << scheme.name << "\n";
    }

    inline bool addEntryPrivate(const TableTuple* tuple, const KeyType &key)
    {
        ++m_inserts;
        std::pair<typename MapType::iterator, bool> retval =
            m_entries.insert(std::pair<KeyType, const void*>(key,
                                                             tuple->address()));
        return retval.second;
    }

    inline bool deleteEntryPrivate(const KeyType &key)
    {
        ++m_deletes;
        return m_entries.erase(key);
    }
        
    /*
    inline bool setEntryToNullPrivate(const KeyType &key)
    {        
        ++m_updates; 
        
        m_entries.erase(key); 
        std::pair<typename MapType::iterator, bool> retval = m_entries.insert(std::pair<KeyType, const void*>(key, NULL));
        return retval.second;
    }
     */

    MapType m_entries;
    KeyType m_tmp1;
    KeyType m_tmp2;

    // iteration stuff
    bool m_begin;
    typename MapType::const_iterator m_keyIter;
    typename MapType::const_reverse_iterator m_keyRIter;
    TableTuple m_match;

    // comparison stuff
    KeyEqualityChecker m_eq;
};

}

#endif // BINARYTREEUNIQUEINDEX_H_
