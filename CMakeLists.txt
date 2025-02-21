cmake_minimum_required(VERSION 3.5)

project(Navegador)

# Encontrar o Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui WebEngineWidgets)

# Habilitar a geração do MOC (se necessário)
set(CMAKE_AUTOMOC ON)

# Incluir diretórios de cabeçalho do Qt
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS})

# Defina o target para o executável primeiro
set(SOURCES main.cpp)

# Criar o executável
add_executable(navegador ${SOURCES})

# Adicionar o arquivo de recursos .qrc
qt5_add_resources(RESOURCE_FILES resources.qrc)

# Adicionar os arquivos de recursos ao target
target_sources(navegador PRIVATE ${RESOURCE_FILES})

# Linkar as bibliotecas do Qt
target_link_libraries(navegador Qt5::Core Qt5::Gui Qt5::WebEngineWidgets)