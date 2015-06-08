#pragma once

#include <boost/iostreams/categories.hpp>
#include <iosfwd>
#include <algorithm>

template < typename Container >
	class container_output_buffer {
		public:
			typedef char char_type;
			typedef boost::iostreams::sink_tag category;

			container_output_buffer( Container *container ) 
			{
				container_ = container;
			}

			std::streamsize write( const char_type *value, std::streamsize size ) 
			{
				container_->insert( container_->end(), value, value + size );
				return size;
			}

		private:
			Container *container_;
	};



template < typename Container >
	class container_input_buffer {
		public:
			typedef char char_type;
			typedef boost::iostreams::source_tag category;
			typedef typename Container::size_type size_type;

			container_input_buffer( const Container *container ) 
			{
				container_ = container;
				position_ = 0;
			}

			std::streamsize read( char_type *value, std::streamsize size ) 
			{
				size_type remaining = std::min( static_cast< size_type >( size ), container_->size() - position_ );
				if ( remaining != 0 ) {
					std::copy( container_->begin() + position_, container_->begin() + position_ + remaining, value );
					position_ += remaining;
					return remaining;
				} else
					return -1;
			}

		private:
			const Container *container_;
			size_type position_;
	};
