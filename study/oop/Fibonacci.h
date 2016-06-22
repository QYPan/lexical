#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "num_sequence.h"

// derived class declarations
// normally would go in a program header file: .h

class Fibonacci : public num_sequence {
public:
   Fibonacci( int beg_pos = 1, int len = 1 )
           :  num_sequence( beg_pos, len, _elems ){}

   virtual num_sequence *clone() const 
		 { return new Fibonacci( *this ); }
		
protected:
   virtual void gen_elems( int pos ) const;
   static vector<unsigned int> _elems;
};


#endif
