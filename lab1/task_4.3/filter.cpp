// file name = filter.cpp

#include"filter.h"

void filter :: prc_filter(){

	char_out='#';

	if (char_in=='s' || char_in=='y' || char_in=='t' || char_in=='e' || char_in=='m' || char_in=='c')
	char_out=char_in; 
}
