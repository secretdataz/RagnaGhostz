# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "Z:/Projetos/RagnaGhostz;Z:/Projetos/RagnaGhostz/out/build/x64-Debug")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_GENERATOR "NSIS")
set(CPACK_INSTALL_CMAKE_PROJECTS "Z:/Projetos/RagnaGhostz/out/build/x64-Debug;rAthena;ALL;/")
set(CPACK_INSTALL_PREFIX "Z:/Projetos/RagnaGhostz/out/install/x64-Debug")
set(CPACK_MODULE_PATH "Z:/Projetos/RagnaGhostz/3rdparty/cmake")
set(CPACK_NSIS_DISPLAY_NAME "rAthena 0.1.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "rAthena 0.1.1")
set(CPACK_OUTPUT_CONFIG_FILE "Z:/Projetos/RagnaGhostz/out/build/x64-Debug/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "Z:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.15/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MMORPG server package")
set(CPACK_PACKAGE_FILE_NAME "rAthena-0.1.1-win64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "rAthena 0.1.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "rAthena 0.1.1")
set(CPACK_PACKAGE_NAME "rAthena")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_RESOURCE_FILE_LICENSE "Z:/Projetos/RagnaGhostz/LICENSE")
set(CPACK_RESOURCE_FILE_README "Z:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.15/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "Z:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-3.15/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "Z:/Projetos/RagnaGhostz/out/build/x64-Debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_RPM "")
set(CPACK_SOURCE_TBZ2 "")
set(CPACK_SOURCE_TGZ "")
set(CPACK_SOURCE_TXZ "")
set(CPACK_SOURCE_TZ "")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "Z:/Projetos/RagnaGhostz/out/build/x64-Debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()

# Configuration for component group "Runtime"
set(CPACK_COMPONENT_GROUP_RUNTIME_DISPLAY_NAME "Runtime")
set(CPACK_COMPONENT_GROUP_RUNTIME_DESCRIPTION "Runtime files")

# Configuration for component "Runtime_base"

SET(CPACK_COMPONENTS_ALL)
set(CPACK_COMPONENT_RUNTIME_BASE_DISPLAY_NAME "Base files")
set(CPACK_COMPONENT_RUNTIME_BASE_DESCRIPTION "configurations, dbs, npcs, docs, ...")
set(CPACK_COMPONENT_RUNTIME_BASE_GROUP Runtime)

# Configuration for component "Runtime_templates"

SET(CPACK_COMPONENTS_ALL)
set(CPACK_COMPONENT_RUNTIME_TEMPLATES_DISPLAY_NAME "Base templates")
set(CPACK_COMPONENT_RUNTIME_TEMPLATES_DESCRIPTION "conf/import and save (generated from conf/import-tmpl and save-tmpl)")
set(CPACK_COMPONENT_RUNTIME_TEMPLATES_GROUP Runtime)

# Configuration for component group "Development"
set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DISPLAY_NAME "Development")
set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION "Development files")

# Configuration for component "Development_base"

SET(CPACK_COMPONENTS_ALL)
set(CPACK_COMPONENT_DEVELOPMENT_BASE_DISPLAY_NAME "Base files")
set(CPACK_COMPONENT_DEVELOPMENT_BASE_DESCRIPTION "projects, 3rdparty, sources, templates")
set(CPACK_COMPONENT_DEVELOPMENT_BASE_GROUP Development)

# Configuration for component "Runtime_loginserver"

SET(CPACK_COMPONENTS_ALL Runtime_base Runtime_templates)
set(CPACK_COMPONENT_RUNTIME_LOGINSERVER_DISPLAY_NAME "login-server")
set(CPACK_COMPONENT_RUNTIME_LOGINSERVER_DESCRIPTION "login-server")
set(CPACK_COMPONENT_RUNTIME_LOGINSERVER_GROUP Runtime)

# Configuration for component "Runtime_charserver"

SET(CPACK_COMPONENTS_ALL Runtime_base Runtime_loginserver Runtime_templates)
set(CPACK_COMPONENT_RUNTIME_CHARSERVER_DISPLAY_NAME "char-server")
set(CPACK_COMPONENT_RUNTIME_CHARSERVER_DESCRIPTION "char-server")
set(CPACK_COMPONENT_RUNTIME_CHARSERVER_GROUP Runtime)

# Configuration for component "Runtime_mapserver"

SET(CPACK_COMPONENTS_ALL Runtime_base Runtime_charserver Runtime_loginserver Runtime_templates)
set(CPACK_COMPONENT_RUNTIME_MAPSERVER_DISPLAY_NAME "map-server")
set(CPACK_COMPONENT_RUNTIME_MAPSERVER_DESCRIPTION "map-server")
set(CPACK_COMPONENT_RUNTIME_MAPSERVER_GROUP Runtime)

# Configuration for component "Runtime_mapcache"

SET(CPACK_COMPONENTS_ALL Runtime_base Runtime_charserver Runtime_loginserver Runtime_mapserver Runtime_templates)
set(CPACK_COMPONENT_RUNTIME_MAPCACHE_DISPLAY_NAME "mapcache")
set(CPACK_COMPONENT_RUNTIME_MAPCACHE_DESCRIPTION "mapcache generator")
set(CPACK_COMPONENT_RUNTIME_MAPCACHE_GROUP Runtime)
