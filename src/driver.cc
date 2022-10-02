#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  //   ElevationDataset ed1 =
  //       ElevationDataset( "ex_input_data/all-tie-row1-2w-3h.dat", 2, 3 );
  ElevationDataset ed2 =
      ElevationDataset( "ex_input_data/map-input-w51-h55.dat", 51, 55 );
  //   ElevationDataset ed3 =
  //       ElevationDataset( "ex_input_data/map-input-w480-h480.dat", 480, 480
  //       );
  //   ElevationDataset ed4 =
  //       ElevationDataset( "ex_input_data/test-data.dat", 2, 2 );
  //   GrayscaleImage gi = GrayscaleImage( ed3 );
  //   gi.to_ppm( "grayscale.ppm" );
  //   PathImage pi = PathImage( gi, ed3 );
  //   pi.to_ppm( "path-image.ppm" );
  int i = 7;
  int *p = &i;
  
}