include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_CONTACT "sqmir@163.com")
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_BINARY_DIR}/packages)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

SET(CPACK_PACKAGE_DIRECTORY "${CMAKE_INSTALL_PREFIX}")
set(CPACK_PACKAGE_NAME "xmax")
set(CPACK_PACKAGE_VENDOR "Xmaxplatform")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION "A client for the XMax network")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A client for the XMax network")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "XMax ${CPACK_PACKAGE_VERSION}")

if(WIN32)
 SET(CPACK_GENERATOR "ZIP;NSIS")
 set(CPACK_PACKAGE_NAME "XMax") # override above
 set(CPACK_NSIS_EXECUTABLES_DIRECTORY .)
 set(CPACK_NSIS_PACKAGE_NAME "XMax v${CPACK_PACKAGE_VERSION}")
 set(CPACK_NSIS_DISPLAY_NAME "${CPACK_NSIS_PACKAGE_NAME}")
 set(CPACK_NSIS_DEFINES "  !define MUI_STARTMENUPAGE_DEFAULTFOLDER \\\"XMax\\\"")
 # it seems like windows zip files usually don't have a single directory inside them, unix tgz frequently do
 SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
elseif(APPLE)
  set(CPACK_GENERATOR "DragNDrop")
else()
  # Linux gets a .tgz
  SET(CPACK_GENERATOR "TGZ;DEB")
  SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
  SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 1)
endif()

include(CPack)