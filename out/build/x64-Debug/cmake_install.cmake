# Install script for directory: Z:/Projetos/RagnaGhostz

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "Z:/Projetos/RagnaGhostz/out/build/x64-Debug/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES
    "Z:/Projetos/RagnaGhostz/athena-start"
    "Z:/Projetos/RagnaGhostz/charserv.bat"
    "Z:/Projetos/RagnaGhostz/dbghelp.dll"
    "Z:/Projetos/RagnaGhostz/libmysql.dll"
    "Z:/Projetos/RagnaGhostz/LICENSE"
    "Z:/Projetos/RagnaGhostz/logserv.bat"
    "Z:/Projetos/RagnaGhostz/mapserv.bat"
    "Z:/Projetos/RagnaGhostz/pcre3.dll"
    "Z:/Projetos/RagnaGhostz/README.txt"
    "Z:/Projetos/RagnaGhostz/runserver.bat"
    "Z:/Projetos/RagnaGhostz/serv.bat"
    "Z:/Projetos/RagnaGhostz/zlib1.dll"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/conf" TYPE DIRECTORY FILES "Z:/Projetos/RagnaGhostz/conf/" REGEX "/[\\\\.]svn$" EXCLUDE REGEX "/conf\\/import\\-tmpl$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/db" TYPE DIRECTORY FILES "Z:/Projetos/RagnaGhostz/db/" REGEX "/[\\\\.]svn$" EXCLUDE REGEX "/conf\\/import\\-tmpl$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" TYPE DIRECTORY FILES "Z:/Projetos/RagnaGhostz/doc/" REGEX "/[\\\\.]svn$" EXCLUDE REGEX "/conf\\/import\\-tmpl$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(MAKE_DIRECTORY "${ENV}${CMAKE_INSTALL_PREFIX}/log")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(MAKE_DIRECTORY "${ENV}${CMAKE_INSTALL_PREFIX}/npc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/sql-files" TYPE DIRECTORY FILES "Z:/Projetos/RagnaGhostz/sql-files/" REGEX "/[\\\\.]svn$" EXCLUDE REGEX "/conf\\/import\\-tmpl$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_basex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/tools" TYPE DIRECTORY FILES "Z:/Projetos/RagnaGhostz/tools/" REGEX "/[\\\\.]svn$" EXCLUDE REGEX "/conf\\/import\\-tmpl$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xRuntime_templatesx" OR NOT CMAKE_INSTALL_COMPONENT)
  include("Z:/Projetos/RagnaGhostz/out/build/x64-Debug/InstallTemplates.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("Z:/Projetos/RagnaGhostz/out/build/x64-Debug/3rdparty/cmake_install.cmake")
  include("Z:/Projetos/RagnaGhostz/out/build/x64-Debug/src/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "Z:/Projetos/RagnaGhostz/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
