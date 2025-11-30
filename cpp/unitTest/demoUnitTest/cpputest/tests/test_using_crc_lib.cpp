#include <CppUTest/TestHarness.h>

#include <boost/crc.hpp>  // for boost::crc_32_type
#include <iostream>   // for std::cerr, std::cout
#include <ostream>    // for std::endl
#include <cstdlib>    // for EXIT_SUCCESS, EXIT_FAILURE

TEST_GROUP(CrcTest)
{
};

TEST(CrcTest, Compile)
{
    boost::crc_32_type  result;
    char  buffer[  ] {0x01, 0x02, 0x03, 0x04};
    unsigned int crc_expected_CRC_32_ISO_HDLC = 0xB63CFBCD;

    result.process_bytes( buffer, sizeof(buffer) );

    auto crc_after = result.checksum();
    CHECK_EQUAL(crc_expected_CRC_32_ISO_HDLC, crc_after);
}

