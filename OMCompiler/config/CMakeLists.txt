
add_library(omc_config_portability STATIC)
add_library(omc::config::portability ALIAS omc_config_portability)

target_sources(omc_config_portability PRIVATE omc_portability.c)

target_include_directories(omc_config_portability PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})