cmake_minimum_required(VERSION 3.13)

# Установка проекта и его параметров
project(ConanSample LANGUAGES CXX)

# Включение автоматической обработки Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP ON)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка для использования менеджера пакетов Conan2
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LW)
string(TOLOWER "${CMAKE_GENERATOR_PLATFORM}" CMAKE_GEN_PL_LW)
string(TOLOWER "${CMAKE_CXX_FLAGS}" CMAKE_CXX_FLAGS_LW)
string(REGEX MATCH "debug" CXX_DEBUG_FOUND "${CMAKE_CXX_FLAGS_LW}")

# Вывод сообщений для отладки
message("MSVC = ${MSVC}")
message("CMAKE_BUILD_TYPE_LW = ${CMAKE_BUILD_TYPE_LW}")
message("CMAKE_CXX_FLAGS_LW = ${CMAKE_CXX_FLAGS_LW}")
message("CXX_DEBUG_FOUND = ${CXX_DEBUG_FOUND}")
message("CMAKE_GENERATOR_PLATFORM_LW = ${CMAKE_GEN_PL_LW}")
message("CMAKE_SIZEOF_VOID_P = ${CMAKE_SIZEOF_VOID_P}")

# Установка параметров для режима отладки
if(CMAKE_BUILD_TYPE_LW STREQUAL "debug" OR CXX_DEBUG_FOUND STREQUAL "debug")
    set(CONAN_ST_DEBUG "--settings=build_type=Debug")
    set(CONAN_SUBFOLDER "Debug")
    message("DEBUG_OPTION = ${CONAN_ST_DEBUG}")
else()
    set(CONAN_SUBFOLDER "Release")
endif()

# Настройка для Windows Visual Studio
if("${MSVC}")
    if(CMAKE_SIZEOF_VOID_P LESS "8" OR CMAKE_GEN_PL_LW STREQUAL "win32")
        set(VS_PREF "VS32_")
        set(CONAN_ST_PROFILE "--profile:all=vs_release32")
    else()
        set(VS_PREF "VS_")
        set(CONAN_ST_PROFILE "--profile:all=vs_release")
    endif()

    set(CONAN_ST_OUTPUT "--output-folder=${CMAKE_CURRENT_SOURCE_DIR}/build/${VS_PREF}${CONAN_SUBFOLDER}")
    message("CONAN_ST_PROFILE = ${CONAN_ST_PROFILE}")

    set(CONAN_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/build/${VS_PREF}${CONAN_SUBFOLDER}/build/generators/conan_toolchain.cmake")

else() # Настройка для Windows MinGW или Linux
    if("${WIN32}" AND CMAKE_SIZEOF_VOID_P LESS "8")
        set(CONAN_ST_PROFILE "--profile:host=mingw8_1_release32")
        set(CONAN_ST_OUTPUT "--output-folder=${CMAKE_CURRENT_SOURCE_DIR}/build/MGW32_${CONAN_SUBFOLDER}")
        message("CONAN_ST_PROFILE = ${CONAN_ST_PROFILE}")

        set(CONAN_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/build/MGW32_${CONAN_SUBFOLDER}/build/${CONAN_SUBFOLDER}/generators/conan_toolchain.cmake")
    else()
        set(CONAN_ST_PROFILE "--profile:host=mingw8_1_release64")
        set(CONAN_ST_OUTPUT "--output-folder=${CMAKE_CURRENT_SOURCE_DIR}/build/MGW64_${CONAN_SUBFOLDER}")

        add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)
        add_compile_options(-fPIC)

        message("CONAN_ST_PROFILE = ${CONAN_ST_PROFILE}")

        set(CONAN_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/build/${CONAN_SUBFOLDER}/generators/conan_toolchain.cmake")
    endif()
endif()

# Выполнение команды установки Conan
execute_process(
    COMMAND conan install ./ --build=missing ${CONAN_ST_PROFILE} ${CONAN_ST_DEBUG} ${CONAN_ST_OUTPUT}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Установка политики CMake
cmake_policy(SET CMP0091 NEW)

# Проверка наличия файла Conan
if (NOT EXISTS ${CONAN_INCLUDE})
    message(FATAL_ERROR "Missing file: ${CONAN_INCLUDE} !")
endif()
include("${CONAN_INCLUDE}")

# Поиск и подключение библиотек OpenCV и Qt
find_package(OpenCV REQUIRED)

find_package(QT NAMES Qt6 COMPONENTS Core)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core REQUIRED Gui REQUIRED Widgets)
else()
    find_package(Qt6 COMPONENTS Core REQUIRED Gui REQUIRED Widgets)
endif()

# Создание исполняемого файла
add_executable(${PROJECT_NAME} main.cpp)

# Указание директорий для включения
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIR})

# Подключение библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBRARIES})

# Завершение настройки для Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable("${PROJECT_NAME}")
endif()