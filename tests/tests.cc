//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                MP : MOUNTAIN PATHS : Student Test Cases                  //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////
TEST_CASE( "Elevation Dataset", "[elevation]" ) {
  SECTION( "2w 2h same values" ) {
    bool flag = true;
    ElevationDataset test_set =
        ElevationDataset( "ex_input_data/test-data.dat", 2, 2 );
    std::vector<std::vector<int>> compare = { { -1, -1 }, { -1, -1 } };
    for ( size_t i = 0; i < test_set.height(); ++i ) {
      for ( size_t j = 0; j < test_set.width(); ++j ) {
        if ( test_set.datum_at( i, j ) != compare.at( i ).at( j ) )
          flag = false;
      }
    }
    REQUIRE( flag );
    REQUIRE( test_set.min_ele() == -1 );
    REQUIRE( test_set.max_ele() == -1 );
    REQUIRE( test_set.get_data().size() == 2 );
    REQUIRE( test_set.get_data().at( 0 ).size() == 2 );
    REQUIRE( test_set.datum_at( 0, 0 ) == -1 );
  }
  SECTION( "Mixed values with blank line at end of file" ) {
    bool flag = true;
    ElevationDataset test_set =
        ElevationDataset( "ex_input_data/all-tie-row1-2w-3h.dat", 2, 3 );
    std::vector<std::vector<int>> compare = { { 9, 10 }, { 8, 10 }, { 7, 10 } };
    for ( size_t i = 0; i < test_set.height(); ++i ) {
      for ( size_t j = 0; j < test_set.width(); ++j ) {
        if ( test_set.datum_at( i, j ) != compare.at( i ).at( j ) )
          flag = false;
      }
    }
    REQUIRE( flag );
    REQUIRE( test_set.min_ele() == 7 );
    REQUIRE( test_set.max_ele() == 10 );
    REQUIRE( test_set.get_data().size() == 3 );
    REQUIRE( test_set.get_data().at( 0 ).size() == 2 );
    REQUIRE( test_set.datum_at( 0, 0 ) == 9 );
  }
}

TEST_CASE( "GrayscaleImage", "[grayscale]" ) {
  SECTION( "Initialize with ElevationData" ) {
    ElevationDataset test_set =
        ElevationDataset( "ex_input_data/prompt_5w_2h", 5, 2 );
    GrayscaleImage gray = GrayscaleImage( test_set );
    REQUIRE( gray.get_image().size() == 3 );
  }
  SECTION( "Initialize with data file" ) {
    GrayscaleImage gray = GrayscaleImage( "ex_input_data/prompt_5w_2h", 5, 2 );
  }
  SECTION( "min = max elevation" ) {
    bool flag = true;
    GrayscaleImage gray = GrayscaleImage( "ex_input_data/test-data.dat", 2, 2 );
    for ( int i = 0; i < (int)gray.height(); ++i ) {
      for ( int j = 0; j < (int)gray.width(); ++j ) {
        if ( !( gray.color_at( i, j ) == Color( 0, 0, 0 ) ) ) flag = false;
      }
    }
    REQUIRE( flag );
  }
}

TEST_CASE( "PathImage", "[path]" ) {}
//////////////////////////////////////////////////////////////////////////////