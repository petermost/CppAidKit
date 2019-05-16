// Copyright 2019 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <pera_software/aidkit/aidkit.hpp>
#include <memory>

namespace pera_software::aidkit::cpp {

    struct free_deleter {
        void operator ()(void *memory) const noexcept {
            std::free(memory);
        }
    };

    using unique_memory_ptr = std::unique_ptr<void, free_deleter>;
    unique_memory_ptr AIDKIT_API make_unique_memory_ptr(std::size_t size);

    using shared_memory_ptr = std::shared_ptr<void>;
    shared_memory_ptr AIDKIT_API make_shared_memory_ptr(std::size_t size);

}
