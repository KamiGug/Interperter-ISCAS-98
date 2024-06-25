# CMakeList.txt : CMake project for tester, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("tester")

# Add source to this project's executable.
add_executable (tester  "helpers/misc.cpp" "domain/Signal.cpp" "domain/Gate/Gate.cpp" "domain/Gate/AndGate.cpp" "domain/Gate/OrGate.cpp" "domain/Gate/NandGate.cpp" "domain/Gate/NorGate.cpp" "domain/Gate/NotGate.cpp" "domain/Gate/XorGate.cpp" "domain/Gate/XnorGate.cpp" "infrastructure/Interpreter/Interpreter.cpp" "tester.cpp" "helpers/gateFactory.cpp" "helpers/gateFactory.h" "infrastructure/Tester/Tester.cpp" "infrastructure/Tester/Tester.h" "infrastructure/Tester/CsvTester.cpp" "infrastructure/Tester/CsvTester.h" "infrastructure/Tester/BinaryNumberTester.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tester PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
