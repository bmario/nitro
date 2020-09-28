/*
 * Copyright (c) 2015-2017, Technische Universität Dresden, Germany
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <nitro/except/raise.hpp>

#include <array>
#include <type_traits>

namespace nitro
{
namespace lang
{
    template <typename T>
    class fixed_vector
    {
    public:
        using iterator = typename std::vector<T>::iterator;

        using reverse_iterator = typename std::vector<T>::reverse_iterator;

        fixed_vector(const std::size_t& capacity)
        : capacity_(capacity), data_(std::make_shared<T[]>(capacity))
        {
        }

        template <typename Iterabel>
        fixed_vector(std::size_t capacity, const Iterabel& array)
        : capacity_(capacity), data_(std::make_shared<T[]>(capacity))
        {
            emplace_back(array.begin(), array.end());
        }

        fixed_vector(const fixed_vector<T>& v) : fixed_vector(v.capacity(), v)
        {
        }

        fixed_vector operator=(const fixed_vector<T>& v)
        {
            return fixed_vector(v.capacity(), v);
        }

        ~fixed_vector() = default;

        bool empty() const
        {
            return size_ == 0;
        }

        const std::size_t& size() const
        {
            return size_;
        }

        std::size_t capacity() const
        {
            return capacity_;
        }

        T& operator[](const std::size_t& key)
        {
            if (key >= capacity())
                raise("Key is larger than capacity");

            if (key > size())
                raise("Key is larger than size, use append() instead");

            return data_[key];
        }

        T& at(const std::size_t& key)
        {
            if (key >= capacity())
                raise("Key is larger than capacity");

            if (key > size())
                raise("Key is larger than size, use append() instead");

            return data_[key];
        }

        const T& operator[](const std::size_t& key) const
        {
            if (key >= capacity())
                raise("Key is larger than capacity!");

            if (key > size())
                raise("Key is larger than size, use emplace_back() instead!");

            return data_[key];
        }

        const T& at(const std::size_t& key) const
        {
            if (key >= capacity())
                raise("Key is larger than capacity!");

            if (key > size())
                raise("Key is larger than size, use emplace_back() instead!");

            return data_[key];
        }

        T& front() noexcept
        {
            return data_[0];
        }

        const T& front() const noexcept
        {
            return data_[0];
        }

        T& back() noexcept
        {
            return data_[size_ - 1];
        }

        const T& back() const noexcept
        {
            return data_[size_ - 1];
        }

        std::size_t emplace(const T& value)
        {
            return emplace_back(value);
        }

        template <typename Iter>
        void emplace(Iter start, const Iter& end)
        {
            emplace_back(start, end);
        }

        template <typename Iter, typename func>
        void emplace(Iter start, const Iter& end, func depackage_func)
        {
            emplace_back(start, end, depackage_func);
        }

        std::size_t emplace_back(const T& value)
        {

            if (size_ >= capacity())
                raise("No capacity left!");

            data_[size_] = T(value);
            ++size_;

            return size_ - 1;
        }

        template <typename Iter>
        void emplace_back(Iter start, const Iter& end)
        {
            while (start != end)
            {
                if (size_ >= capacity())
                    raise("No capacity left!");

                data_[size_] = T(*start);
                ++size_;

                ++start;
            }
        }

        std::size_t insert(const T& value)
        {

            if (size_ >= capacity())
                raise("No capacity left!");

            data_[size_] = value;
            ++size_;

            return size_ - 1;
        }

        template <typename Iter>
        void insert(Iter start, const Iter& end)
        {
            while (start != end)
            {
                if (size_ >= capacity())
                    raise("No capacity left!");

                data_[size_] = *start;
                ++size_;

                ++start;
            }
        }

        template <typename Iter, typename func>
        void insert(Iter start, const Iter& end, func depackage_func)
        {
            while (start != end)
            {
                if (size_ >= capacity())
                    raise("No capacity left!");

                data_[size_] = depackage_func(start);
                ++size_;

                ++start;
            }
        }

        template <typename iterabel>
        void merge(iterabel array)
        {
            emplace_back(array.begin(), array.end());
        }

        std::size_t push_back(const T& value)
        {

            if (size_ >= capacity())
                raise("No capacity left!");

            data_[size_] = value;
            ++size_;

            return size_ - 1;
        }

        T pop_back(const std::size_t& key)
        {

            if (size_ == 0)
                raise("Container is empty!");

            --size_;
            return data_[size_];
        }

        typename fixed_vector<T>::iterator begin() noexcept
        {
            return iterator(&data_[0]);
        }

        typename fixed_vector<T>::reverse_iterator rbegin() noexcept
        {
            return reverse_iterator(&data_[size_ - 1]);
        }

        typename fixed_vector<T>::iterator end() noexcept
        {
            return iterator(&data_[size_]);
        }

        typename fixed_vector<T>::reverse_iterator rend() noexcept
        {
            return reverse_iterator(&data_[-1]);
        }

        const typename fixed_vector<T>::iterator begin() const noexcept
        {
            return iterator(&data_[0]);
        }

        const typename fixed_vector<T>::reverse_iterator rbegin() const noexcept
        {
            return reverse_iterator(&data_[size_ - 1]);
        }

        const typename fixed_vector<T>::iterator end() const noexcept
        {
            return iterator(&data_[size_]);
        }

        const typename fixed_vector<T>::reverse_iterator rend() const noexcept
        {
            return reverse_iterator(&data_[-1]);
        }

        const typename fixed_vector<T>::iterator cbegin() const noexcept
        {
            return iterator(&data_[0]);
        }

        const typename fixed_vector<T>::reverse_iterator crbegin() const noexcept
        {
            return reverse_iterator(&data_[size_ - 1]);
        }

        const typename fixed_vector<T>::iterator cend() const noexcept
        {
            return iterator(&data_[size_]);
        }

        const typename fixed_vector<T>::reverse_iterator crend() const noexcept
        {
            return reverse_iterator(&data_[-1]);
        }

        template <size_t I>
        T& get() noexcept
        {
            return this->at(I);
        }

        template <size_t I>
        const T& get() const noexcept
        {
            return this->at(I);
        }

        void erase(std::size_t key)
        {
            if (key >= size())
                raise("Key does not exsist!");

            while (key + 1 < size() && key + 1 < capacity())
            {
                data_[key] = data_[key + 1];
                ++key;
            }
            --size_;
        }

        std::shared_ptr<T[]> data()
        {
            return data_;
        }

    private:
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;

        std::shared_ptr<T[]> data_;
    };

} // namespace lang
} // namespace nitro

namespace std
{
template <size_t I, typename T>
T& get(nitro::lang::fixed_vector<T>& c) noexcept
{
    return c.at(I);
}
} // namespace std
