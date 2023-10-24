
#include <sys/time.h>
#include "map/map.hpp"
#include <map>



time_t timer() {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}
int main(void  )
{
    time_t begin_1;
    time_t end_1;
        ft::map<int,int> my_map;

        begin_1 = timer();
        for(size_t i = 0; i < 10000000; i++)
        {
            my_map.insert(ft::make_pair(i, i));
        }
        end_1 = timer();
        std::cerr << "this is my time " << end_1 - begin_1 << std::endl;
        std::cerr << "----------------" << std::endl;
    time_t begin_2;
    time_t end_2;
        std::map<int,int> my_map2;

        begin_2 = timer();
        for(size_t i = 0; i < 10000000; i++)
        {
            my_map2.insert(std::make_pair(i, i));
        }
        end_2 = timer();
        std::cerr << "std 's time " << end_2 - begin_2 << std::endl;
}