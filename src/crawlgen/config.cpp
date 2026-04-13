#include <vector>
#include <string>

#include <crawlgen/config.hpp>
#include <crawlgen/configtypes.hpp>

namespace CrawlGen {
    using namespace std;    

    Config::Config(vector<string> &argv): argv(argv) {
    }
}
