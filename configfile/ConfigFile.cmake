set (CONFIG_FILE_GENERATOR "${RHOBAN_UTILS_DIRECTORY}/configfile/generate.py")

macro (config_file NAME)
    set (OUTPUT_DIR "${PROJECT_BINARY_DIR}/configs")
    set (GENERATE_FILES
        "${OUTPUT_DIR}/${NAME}.h"
        "${OUTPUT_DIR}/${NAME}.cpp"
        )
    set (YAML_FILE
        "${PROJECT_SOURCE_DIR}/${NAME}.yml"
        )
    add_custom_command(
        OUTPUT ${GENERATE_FILES}
        COMMAND "${CONFIG_FILE_GENERATOR}" "${PROJECT_SOURCE_DIR}" "${NAME}" "${OUTPUT_DIR}"
        DEPENDS "${YAML_FILE}" ${ARGN}
        )
    set (ALL_SOURCES ${ALL_SOURCES}
        "${OUTPUT_DIR}/${NAME}.cpp"
        )
endmacro (config_file)

include_directories ("${PROJECT_BINARY_DIR}/configs")
include_directories ("${YAML_HEADERS}")
