#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <Windows.h>

namespace d3dcore {

	
		std::string WChar_to_string(WCHAR* wChar) {
			char ch[256];
			char DefChar = ' ';
			WideCharToMultiByte(CP_ACP, 0, wChar, -1, ch, 260, &DefChar, NULL);

			std::string ss(ch);

			return ss;
		}

		// Throw a std::system_error if the HRESULT indicates failure.
		template< typename T >
		void throw_if_failed(HRESULT hr, T&& msg)
		{
			if (FAILED(hr))
				throw std::system_error{ hr, std::system_category(), std::forward<T>(msg) };
		}



	

	
	

}