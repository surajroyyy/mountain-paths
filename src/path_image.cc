#include "path_image.hpp"

PathImage::PathImage( const GrayscaleImage& image,
                      const ElevationDataset& dataset ):
    width_( dataset.width() ), height_( dataset.height() ) {
  const Color red = Color( 252, 25, 63 );
  const Color green = Color( 31, 253, 13 );
  for ( size_t i = 0; i < image.height(); ++i ) {
    std::vector<Color> cols;
    for ( size_t j = 0; j < image.width(); ++j ) {
      cols.push_back( image.color_at( i, j ) );
    }
    path_image_.push_back( cols );
  }
  for ( int i = 0; i < (int)height_; ++i ) {
    int row = i;
    Path current_path = Path( width_, row );
    for ( int j = 0; j < (int)width_; ++j ) {
      int current = dataset.datum_at( i, j ), fwd_up = 0, fwd = 0, fwd_down = 0;
      path_image_[i][j] = red;
      current_path.set_loc( j, i );
      if ( j >= (int)width_ - 1 ) break;
      if ( i != 0 && i < (int)height_ - 1 ) {  // middle of image
        fwd_up = abs( dataset.datum_at( i - 1, j + 1 ) - current );
        fwd = abs( dataset.datum_at( i, j + 1 ) - current );
        fwd_down = abs( dataset.datum_at( i + 1, j + 1 ) - current );
        if ( fwd_up < fwd && fwd_up < fwd_down ) {
          i--;
          current_path.inc_ele_change( fwd_up );
        } else if ( ( fwd_down < fwd && fwd_down < fwd_up ) ||
                    ( fwd_down == fwd_up && fwd_down < fwd ) ) {
          i++;
          current_path.inc_ele_change( fwd_down );
        } else {
          current_path.inc_ele_change( fwd );
        }
      } else if ( i == 0 ) {  // top of image
        fwd = abs( dataset.datum_at( i, j + 1 ) - current );
        fwd_down = abs( dataset.datum_at( i + 1, j + 1 ) - current );
        if ( fwd_down < fwd ) {
          i++;
          current_path.inc_ele_change( fwd_down );
        } else
          current_path.inc_ele_change( fwd );
      } else if ( i >= int( height_ ) - 1 ) {  // bottom of image
        fwd = abs( dataset.datum_at( i, j + 1 ) - current );
        fwd_up = abs( dataset.datum_at( i - 1, j + 1 ) - current );
        if ( fwd_up < fwd ) {
          i--;
          current_path.inc_ele_change( fwd_up );
        } else
          current_path.inc_ele_change( fwd );
      }
    }
    i = row;
    paths_.push_back( current_path );
  }
  Path min = paths_.at( 0 );
  for ( Path path : paths_ ) {
    if ( path.ele_change() < min.ele_change() ) min = path;
  }
  int count = 0;
  for ( int i : min.path() ) {
    path_image_[i][count] = green;
    count++;
  }
}
size_t PathImage::width() const { return width_; }
size_t PathImage::height() const { return height_; }
unsigned int PathImage::max_color_value() const { return max_color_value_; }
const std::vector<Path>& PathImage::paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::path_image() const {
  return path_image_;
}
void PathImage::to_ppm( const std::string& name ) const {
  // create ppm
  std::ofstream ofs( name );
  ofs << "P3"
      << "\n"
      << width_ << " " << height_ << "\n"
      << max_color_value_ << std::endl;
  for ( size_t i = 0; i < height_; ++i ) {
    for ( size_t j = 0; j < width_; ++j ) {
      Color current = path_image_.at( i ).at( j );
      ofs << current.red() << " " << current.green() << " " << current.blue();
      if ( j != width_ - 1 ) ofs << " ";
    }
    ofs << "\n";
  }
}
