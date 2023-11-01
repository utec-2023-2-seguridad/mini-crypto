# Toy blockchain
# Copyright © 2023 Otreblan
#
# mini-crypto is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# mini-crypto is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with mini-crypto.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13.0)

project(mini-crypto
	VERSION 0.0.0
	DESCRIPTION "Toy blockchain"
	HOMEPAGE_URL "https://github.com/utec-2023-2-seguridad/mini-crypto"
)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

Include(FetchContent)
include(CPack)
include(FindPkgConfig)
include(GNUInstallDirs)

# The program itself
add_executable(${PROJECT_NAME})

# C++ version
set_target_properties(${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 20
)

# Packages
find_package(bash-completion)

add_subdirectory(src) # Sources list
add_subdirectory(pkg) # Packaging

# Shared libraries
pkg_check_modules(libraries
	REQUIRED IMPORTED_TARGET
		libsodium
)

FetchContent_Declare(
	EnTT
	GIT_REPOSITORY https://github.com/skypjack/entt
	GIT_TAG        v3.12.2
	OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(EnTT)

find_package(Boost REQUIRED)
find_package(EnTT REQUIRED)
find_package(OpenMP REQUIRED)
#find_package(msgpackc-cxx REQUIRED)

# Linking
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Boost::headers
		EnTT::EnTT
		OpenMP::OpenMP_CXX
		PkgConfig::libraries
		#msgpackc-cxx
)

# Default flags
target_compile_options(${PROJECT_NAME}
	PRIVATE
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_precompile_headers(${PROJECT_NAME}
		PRIVATE
			<boost/asio.hpp>
			<entt/entt.hpp>
	)
endif()

# Bash completion
file(WRITE ${CMAKE_BINARY_DIR}/bash-completion/${PROJECT_NAME}
	"complete -F _longopt ${PROJECT_NAME}"
)

install(FILES
	${CMAKE_BINARY_DIR}/bash-completion/${PROJECT_NAME}
	DESTINATION ${BASH_COMPLETION_COMPLETIONSDIR}/
)

# Install target
install(TARGETS ${PROJECT_NAME}
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)
