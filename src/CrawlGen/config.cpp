#include <vector>
#include <string>

#include <CrawlGen/config.hpp>
#include <CrawlGen/configtypes.hpp>

namespace CrawlGen {
    using namespace std;    

    Config::Config(vector<string> argv) {
        this->argv = argv; 

    }
}
