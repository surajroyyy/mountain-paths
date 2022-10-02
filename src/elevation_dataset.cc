#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset( const std::string& file,
                                    size_t width,
                                    size_t height ):
    width_( width ), height_( height ) {
  std::ifstream ifs( file );
  int value = 0;
  bool flag = true;
  if ( !ifs.is_open() ) throw std::runtime_error( "Cannot open file" );
  while ( ifs.good() ) {
    if ( !flag ) break;
    for ( int row = 0; row < (int)height_; ++row ) {
      if ( !flag ) break;
      std::vector<int> cols;
      for ( int col = 0; col < (int)width_; ++col ) {
        ifs >> value;
        // std::cout << value << std::endl;
        if ( ifs.bad() ) {
          throw std::runtime_error( "Formatted-read failure" );
        } else if ( ifs.fail() ) {
          ifs.clear();
          ifs.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        } else {
          cols.push_back( value );
        }
        if ( ifs.eof() ) {
          flag = false;
          break;
        }
      }
      data_.push_back( cols );
    }
  }
  std::cout << "size: " << data_.size() << std::endl;
  if ( data_.size() != height_ ) {
    data_.pop_back();
  }
  int max = data_.at( 0 ).at( 0 );
  int min = data_.at( 0 ).at( 0 );
  int row_size = data_.size();
  int col_size = 0;
  int num_elements = 0;
  for ( int i = 0; i < row_size; ++i ) {
    col_size = data_.at( i ).size();
    std::cout << i << ": ";
    for ( int j = 0; j < col_size; ++j ) {
      if ( max < data_.at( i ).at( j ) ) max = data_.at( i ).at( j );
      if ( min > data_.at( i ).at( j ) ) min = data_.at( i ).at( j );
      std::cout << data_.at( i ).at( j ) << " ";
      num_elements++;
    }
    std::cout << std::endl;
  }
  min_ele_ = min;
  max_ele_ = max;
  int num_expected = (int)width_ * (int)height_;
  std::cout << "num elements: " << num_elements << std::endl;
  std::cout << "expected: " << num_expected << std::endl;
  if ( num_elements != num_expected )
    throw std::runtime_error( "Wrong number of data points in file" );
}
size_t ElevationDataset::width() const { return width_; }
size_t ElevationDataset::height() const { return height_; }
int ElevationDataset::max_ele() const { return max_ele_; }
int ElevationDataset::min_ele() const { return min_ele_; }
int ElevationDataset::datum_at( size_t row, size_t col ) const {
  return data_.at( row ).at( col );  // correct?
}
const std::vector<std::vector<int>>& ElevationDataset::get_data() const {
  return data_;
}