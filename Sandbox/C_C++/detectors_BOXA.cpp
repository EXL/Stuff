#include <map>
#include <string>

class Detector {
public:
    enum Detectors {
        FIRST,
        SECOND,
        THIRD
    };

    Detector() {
        m = {
            {FIRST, "First Detector"},
            {SECOND, "Second Detector"},
            {THIRD, "Third Detector"}
        };
    }

    std::string get(Detectors dec) {
        return m.at(dec);
    }

    private:
        std::map<Detectors, std::string> m;
};

int main() {
    Detector detectors;
    printf("Test: %s.\n", detectors.get(detectors.FIRST).c_str());
    printf("Test: %s.\n", detectors.get(detectors.SECOND).c_str());
    printf("Test: %s.\n", detectors.get(detectors.THIRD).c_str());
    return 0;
}
