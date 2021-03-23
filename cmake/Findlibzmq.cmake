# - Find libzmq
#
#  ZEROMQ_INCLUDE_DIR
#  ZEROMQ_LIBRARIES
#  ZEROMQ_FOUND

find_path(libzmq_INCLUDE_DIR NAMES zmq.h)
mark_as_advanced(libzqm_INCLUDE_DIR)

find_library(libzmq_LIBRARY NAMES zmq)
mark_as_advanced(libzmq_LIBRARY)

# Extract version information from the header file
if(libzmq_INCLUDE_DIR)
    file(STRINGS ${libzmq_INCLUDE_DIR}/zmq.h _major_ver_line
         REGEX "^#define ZMQ_VERSION_MAJOR [0-9]+"
         LIMIT_COUNT 1)
    file(STRINGS ${libzmq_INCLUDE_DIR}/zmq.h _minor_ver_line
         REGEX "^#define ZMQ_VERSION_MINOR [0-9]+"
         LIMIT_COUNT 1)
    file(STRINGS ${libzmq_INCLUDE_DIR}/zmq.h _patch_ver_line
         REGEX "^#define ZMQ_VERSION_PATCH [0-9]+"
         LIMIT_COUNT 1)
    string(REGEX MATCH "[0-9]+" _version_major ${_major_ver_line})
    string(REGEX MATCH "[0-9]+" _version_minor ${_minor_ver_line})
    string(REGEX MATCH "[0-9]+" _version_patch ${_patch_ver_line})
    set(libzmq_VERSION "${_version_major}.${_version_minor}.${_version_patch}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libzmq
    REQUIRED_VARS libzmq_INCLUDE_DIR libzmq_LIBRARY
    VERSION_VAR libzmq_VERSION)

if (libzmq_FOUND)
    set(libzmq_INCLUDE_DIRS ${libzmq_INCLUDE_DIR})
    set(libzmq_LIBRARIES ${libzmq_LIBRARY})
    if (NOT TARGET libzmq::libzmq)
        add_library(libzmq::libzmq UNKNOWN IMPORTED)
        set_target_properties(libzmq::libzmq PROPERTIES
            IMPORTED_LOCATION "${libzmq_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${libzmq_INCLUDE_DIR}"
        )
    endif()
endif()
