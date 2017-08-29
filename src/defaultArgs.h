#include "cxxopts.hpp"


class defaultOptions{

 public: 
    cxxopts::Options* opts;
    int MAX_EVENTS;
    bool verbose;


    defaultOptions(char* shortName, char* longName){

        opts = new cxxopts::Options(shortName,longName);

        MAX_EVENTS = 99999999;
        verbose = false;
        opts->add_options()
            ("N,num_events","Number of events to analyze per sample",cxxopts::value<int>(MAX_EVENTS))
            ("v,verbose","Verbose mode (default false)",cxxopts::value<bool>(verbose));

    }


};
