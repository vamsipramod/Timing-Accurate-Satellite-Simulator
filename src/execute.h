#include "decode.h"
#include "reg.h"

class Execute{

    private:
        static int32_t get_simm13(int32_t num);

    public:
        static void execute(inst* inst_details);

};
