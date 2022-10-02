#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage( const ElevationDataset& dataset ):
    width_( dataset.width() ), height_( dataset.height() ) {
  int shade_of_gray = 0;
  Color gray;
  for ( std::vector<int> cols : dataset.get_data() ) {
    std::vector<Color> gray_col;
    for ( int datum : cols ) {
      if ( dataset.max_ele() != dataset.min_ele() ) {
        double num = datum - dataset.min_ele();
        double denom = dataset.max_ele() - dataset.min_ele();
        shade_of_gray = round( ( num / denom ) * max_color_value_ );
      }
      // std::cout << shade_of_gray << std::endl;
      gray = Color( shade_of_gray, shade_of_gray, shade_of_gray );
      gray_col.push_back( gray );
    }
    image_.push_back( gray_col );
  }
}
GrayscaleImage::GrayscaleImage( const std::string& path,
                                size_t width,
                                size_t height ):
    GrayscaleImage( ElevationDataset( path, width, height ) ) {}
size_t GrayscaleImage::width() const { return width_; }
size_t GrayscaleImage::height() const { return height_; }
unsigned int GrayscaleImage::max_color_value() const {
  return max_color_value_;
}
const Color& GrayscaleImage::color_at( int row, int col ) const {
  return image_.at( row ).at( col );
}
const std::vector<std::vector<Color>>& GrayscaleImage::get_image() const {
  return image_;
}
void GrayscaleImage::to_ppm( const std::string& name ) const {
  std::ofstream ofs( name );
  ofs << "P3"
      << "\n"
      << width_ << " " << height_ << "\n"
      << max_color_value_ << std::endl;
  for ( size_t i = 0; i < height_; ++i ) {
    for ( size_t j = 0; j < width_; ++j ) {
      Color current = image_.at( i ).at( j );
      ofs << current.red() << " " << current.green() << " " << current.blue();
      if ( j != width_ - 1 ) ofs << " ";
    }
    ofs << "\n";
  }
}
