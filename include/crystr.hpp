/*
 * MIT License https://github.com/Android1337/crystr/blob/main/LICENSE
 * 
 * Copyright (c) 2023 Android1337
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CRYSTR_HPP
#define CRYSTR_HPP
#include <bit> // std::bit_cast

#define USE_INLINE_FUNCTIONS 0 // you can either use virtual or __forceinline

#if USE_INLINE_FUNCTIONS == 1
#define CRYSTR_TYPE __forceinline
#else
#define CRYSTR_TYPE virtual
#ifdef _CPPRTTI
#error("Please disable Run-Time Type Information under C/C++ -> Language (/GR-)")
#endif
#endif

constexpr unsigned long long const_hash(const char* input) {
	return *input ? static_cast<unsigned long long>(*input) + 33 * const_hash(input + 1) : 5381;
}

#define crystr(str) []() { \
			constexpr static auto const_str = crys::cryStr \
				<const_hash(__DATE__ __TIME__) + __COUNTER__, sizeof(str) / sizeof(str[0]), std::remove_const_t<std::remove_reference_t<decltype(str[0])>>>((std::remove_const_t<std::remove_reference_t<decltype(str[0])>>*)str); \
					return const_str; }()

namespace crys
{
	template <unsigned long long uniqueid, unsigned int data_size, typename T>
	class cryStr
	{
	public:
		__forceinline constexpr cryStr(T* str)
		{
			for (int i = 0; i < data_size; i++)
			{
				auto v = (uniqueid + i) * double((3.1415926535897932f / (180.f)) / 2.f);
				auto y = v - (2.0f * 3.1415926535897932f) * double((0.31830988618f * 0.5f) * v + 0.5f);
				auto w = double(0);

				if (y > 3.1415926535897932f / 2)
				{
					y = 3.1415926535897932f - y;
					w = (-1.f * ((((-2.6051615e-07f * (y * y) + 2.4760495e-05f) * (y * y) - 0.0013888378f) * (y * y) + 0.041666638f) * (y * y) - 0.5f) * (y * y) + 1.0f);
				}
				else if (y < (3.1415926535897932f / 2) * -1)
				{
					y = -3.1415926535897932f - y;
					w = (-1.f * ((((-2.6051615e-07f * (y * y) + 2.4760495e-05f) * (y * y) - 0.0013888378f) * (y * y) + 0.041666638f) * (y * y) - 0.5f) * (y * y) + 1.0f);
				}
				else
					w = (1.f * ((((-2.6051615e-07f * (y * y) + 2.4760495e-05f) * (y * y) - 0.0013888378f) * (y * y) + 0.041666638f) * (y * y) - 0.5f) * (y * y) + 1.0f);

				auto z = (((((-2.3889859e-08f * (y * y) + 2.7525562e-06f) * (y * y) - 0.00019840874f) * (y * y) + 0.0083333310f) * (y * y) - 0.16666667f) * (y * y) + 1.0f);
				data[i] = str[i] ^ T(std::bit_cast<unsigned long long>(z * y + w) + i);
			}
		}

		__forceinline void encrypt()
		{
#if defined(CRYCALL_HPP) && USE_INLINE_FUNCTIONS == 0
			crycall_virtual(void, this, 0x2);
#else
			xor_encrypt();
#endif
		}

		__forceinline T* decrypt()
		{
#if defined(CRYCALL_HPP) && USE_INLINE_FUNCTIONS == 0
			crycall_virtual(void, this, 0x3);
#else
			xor_decrypt();
#endif
			thread_local auto ret = data;
			return ret;
		}

		__forceinline void clear()
		{
			for (unsigned int i = 0; i < data_size; i++)
				data[i] = 0;
		}

	private:
		CRYSTR_TYPE unsigned long long get_xor_key(unsigned int i)
		{
			thread_local auto d = double((3.1415926535897932f / (180.f)) / 2.f);
			thread_local auto v = (uniqueid + i) * d;
			thread_local auto q = double((0.31830988618f * 0.5f) * v + 0.5f);
			thread_local auto y = v - (2.0f * 3.1415926535897932f) * q;

			if (y > 3.1415926535897932f / 2)
			{
				thread_local auto ny = 3.1415926535897932f - y;
				thread_local auto z = (((((-2.3889859e-08f * (ny * ny) + 2.7525562e-06f) * (ny * ny) - 0.00019840874f) * (ny * ny) + 0.0083333310f) * (ny * ny) - 0.16666667f) * (ny * ny) + 1.0f);
				thread_local auto w = (-1.f * ((((-2.6051615e-07f * (ny * ny) + 2.4760495e-05f) * (ny * ny) - 0.0013888378f) * (ny * ny) + 0.041666638f) * (ny * ny) - 0.5f) * (ny * ny) + 1.0f);
				thread_local auto ret = z * ny + w;
				return std::bit_cast<unsigned long long>(ret) + i;
			}
			else if (y < (3.1415926535897932f / 2) * -1)
			{
				thread_local auto ny = -3.1415926535897932f - y;
				thread_local auto z = (((((-2.3889859e-08f * (ny * ny) + 2.7525562e-06f) * (ny * ny) - 0.00019840874f) * (ny * ny) + 0.0083333310f) * (ny * ny) - 0.16666667f) * (ny * ny) + 1.0f);
				thread_local auto w = (-1.f * ((((-2.6051615e-07f * (ny * ny) + 2.4760495e-05f) * (ny * ny) - 0.0013888378f) * (ny * ny) + 0.041666638f) * (ny * ny) - 0.5f) * (ny * ny) + 1.0f);
				thread_local auto ret = z * ny + w;
				return std::bit_cast<unsigned long long>(ret) + i;
			}

			thread_local auto z = (((((-2.3889859e-08f * (y * y) + 2.7525562e-06f) * (y * y) - 0.00019840874f) * (y * y) + 0.0083333310f) * (y * y) - 0.16666667f) * (y * y) + 1.0f);
			thread_local auto w = (1.f * ((((-2.6051615e-07f * (y * y) + 2.4760495e-05f) * (y * y) - 0.0013888378f) * (y * y) + 0.041666638f) * (y * y) - 0.5f) * (y * y) + 1.0f);
			thread_local auto ret = z * y + w;
			return std::bit_cast<unsigned long long>(ret) + i;
		}

		CRYSTR_TYPE void xor_byte(T* out, T* data, unsigned int i)
		{
#if defined(CRYCALL_HPP) && USE_INLINE_FUNCTIONS == 0
			out[i] = data[i] ^ T(crycall_virtual(unsigned long long, this, 0x0, i));
#else
			out[i] = data[i] ^ T(get_xor_key(i));
#endif
		}

		CRYSTR_TYPE void xor_encrypt()
		{
			if (data[data_size - 1] == 0)
			{
				for (unsigned int i = 0; i < data_size; i++)
				{
#if defined(CRYCALL_HPP) && USE_INLINE_FUNCTIONS == 0
					crycall_virtual(void, this, 0x1, data, data, i);
#else
					xor_byte(data, data, i);
#endif
				}

				data[data_size - 1] = 0xFF;
			}
		}

		CRYSTR_TYPE void xor_decrypt()
		{
			if (data[data_size - 1] != 0)
			{
				for (unsigned int i = 0; i < data_size; i++)
				{
#if defined(CRYCALL_HPP) && USE_INLINE_FUNCTIONS == 0
					crycall_virtual(void, this, 0x1, data, data, i);
#else
					xor_byte(data, data, i);
#endif
				}

				data[data_size - 1] = 0;
			}
		}

		T data[data_size] = {};
	};
}

#endif // include guard
