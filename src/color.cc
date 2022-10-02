#include "color.hpp"

#include <stdexcept>

Color::Color(): red_( 0 ), green_( 0 ), blue_( 0 ) {}

Color::Color( int r, int g, int b ): red_( r ), green_( g ), blue_( b ) {
  // need to ensure valid color has been constructed...
  const int kMax = 255;
  if ( r < 0 || r > kMax || g < 0 || g > kMax || b < 0 || b > kMax ) {
    throw std::runtime_error( "Invalid color" );
  }
}

// do not modify: auto-grader relies on this definition of equality.
bool operator==( const Color& rhs, const Color& lhs ) {
  return ( rhs.red() == lhs.red() && rhs.green() == lhs.green() &&
           rhs.blue() == lhs.blue() );
}