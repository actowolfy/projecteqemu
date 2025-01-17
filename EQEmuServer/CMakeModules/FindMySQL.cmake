# - Find mysqlclient
#
# -*- cmake -*-
#
# Find the native MySQL includes and library
#
#  MySQL_INCLUDE_DIR - where to find mysql.h, etc.
#  MySQL_LIBRARIES   - List of libraries when using MySQL.
#  MySQL_FOUND       - True if MySQL found.
#  The following can be used as a hint as to where to search:
#  MYSQL_ROOT

IF (MySQL_INCLUDE_DIR AND MySQL_LIBRARIES)
  # Already in cache, be silent
  SET(MySQL_FIND_QUIETLY TRUE)
ENDIF (MySQL_INCLUDE_DIR AND MySQL_LIBRARIES)

# Include dir
IF(MYSQL_ROOT)
    FIND_PATH(MySQL_INCLUDE_DIR
      NAMES mysql.h
      PATHS ${MYSQL_ROOT}/include
      PATH_SUFFIXES mysql
    )
ELSE(MYSQL_ROOT)
    FIND_PATH(MySQL_INCLUDE_DIR
      NAMES mysql.h
      PATH_SUFFIXES mysql
    )
ENDIF(MYSQL_ROOT)

# Library
SET(MySQL_NAMES mysqlclient_r mysqlclient)
IF(MYSQL_ROOT)
    FIND_LIBRARY(MySQL_LIBRARY_DEBUG
      NAMES ${MySQL_NAMES}
      PATHS ${MYSQL_ROOT}/lib/debug /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
      PATH_SUFFIXES mysql
    )
    
    FIND_LIBRARY(MySQL_LIBRARY_RELEASE
      NAMES ${MySQL_NAMES}
      PATHS ${MYSQL_ROOT}/lib /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
      PATH_SUFFIXES mysql
    )
ELSE(MYSQL_ROOT)
    FIND_LIBRARY(MySQL_LIBRARY_DEBUG
      NAMES ${MySQL_NAMES}
      PATHS /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
      PATH_SUFFIXES mysql
    )
    
    FIND_LIBRARY(MySQL_LIBRARY_RELEASE
      NAMES ${MySQL_NAMES}
      PATHS /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64
      PATH_SUFFIXES mysql
    )
ENDIF(MYSQL_ROOT)

IF (MySQL_INCLUDE_DIR AND MySQL_LIBRARY_DEBUG AND MySQL_LIBRARY_RELEASE)
  SET(MySQL_FOUND TRUE)
  SET( MySQL_LIBRARIES ${MySQL_LIBRARY_DEBUG} ${MySQL_LIBRARY_RELEASE} )
ELSE (MySQL_INCLUDE_DIR AND MySQL_LIBRARY_DEBUG AND MySQL_LIBRARY_RELEASE)
  SET(MySQL_FOUND FALSE)
  SET( MySQL_LIBRARIES )
ENDIF (MySQL_INCLUDE_DIR AND MySQL_LIBRARY_DEBUG AND MySQL_LIBRARY_RELEASE)


# handle the QUIETLY and REQUIRED arguments and set MySQL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MySQL DEFAULT_MSG MySQL_LIBRARY_DEBUG MySQL_LIBRARY_RELEASE MySQL_INCLUDE_DIR)

IF(MySQL_FOUND)
  SET( MySQL_LIBRARIES ${MySQL_LIBRARY_DEBUG} ${MySQL_LIBRARY_RELEASE} )
ELSE(MySQL_FOUND)
  SET( MySQL_LIBRARIES )
ENDIF(MySQL_FOUND)

MARK_AS_ADVANCED(
  MySQL_LIBRARY_DEBUG
  MySQL_LIBRARY_RELEASE
  MySQL_INCLUDE_DIR
  )
  