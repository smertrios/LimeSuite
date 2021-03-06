########################################################################
## Support for NovenaRF7 connection
########################################################################

set(THIS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionNovenaRF7)

set(CONNECTION_NOVENARF7_SOURCES
    ${THIS_SOURCE_DIR}/ConnectionNovenaRF7Entry.cpp
    ${THIS_SOURCE_DIR}/ConnectionNovenaRF7.cpp
    ${THIS_SOURCE_DIR}/ConnectionNovenaRF7_streaming.cpp
    ${THIS_SOURCE_DIR}/StreamChannel.cpp
)

include(CheckIncludeFile)
set(CMAKE_REQUIRED_DEFINITIONS -DNULL=0)
CHECK_INCLUDE_FILE(linux/spi/spidev.h HAS_SPIDEV_H)
CHECK_INCLUDE_FILE(linux/i2c-dev.h HAS_I2CDEV_H)

#require a special version of i2c-dev.h that comes with the libi2c-dev package
if (HAS_I2CDEV_H)
    include(CheckCSourceCompiles)
    set(code "#include <linux/i2c-dev.h>\nint main(){struct i2c_msg messages[2]; return 0;}")
    CHECK_C_SOURCE_COMPILES("${code}" HAS_I2C_MSG)
else (HAS_I2CDEV_H)
    set(HAS_I2C_MSG FALSE)
endif (HAS_I2CDEV_H)

########################################################################
## Feature registration
########################################################################
include(FeatureSummary)
include(CMakeDependentOption)
cmake_dependent_option(ENABLE_NOVENARF7 "Enable NovenaRF7" OFF "ENABLE_LIBRARY;HAS_SPIDEV_H;HAS_I2C_MSG" OFF)
add_feature_info(ConnectionNovenaRF7 ENABLE_NOVENARF7 "NovenaRF7 Connection support")
if (NOT ENABLE_NOVENARF7)
    return()
endif()

########################################################################
## Add to library
########################################################################
target_sources(LimeSuite PRIVATE ${CONNECTION_NOVENARF7_SOURCES})
