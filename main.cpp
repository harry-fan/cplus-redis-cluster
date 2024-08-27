#include <iostream>
#include "hircluster.h"

#define CLUSE_NODES "127.0.0.1:7001,127.0.0.1:7002,127.0.0.1:7003,127.0.0.1:7004,127.0.0.1:7005,127.0.0.1:7006"
#define CLUSE_PASSWD "1234567890"

int main() {
    redisClusterContext *rcc = redisClusterContextInit();
    redisClusterSetOptionAddNodes(rcc, CLUSE_NODES);
    redisClusterSetOptionRouteUseSlots(rcc);
    redisClusterSetOptionPassword(rcc, CLUSE_PASSWD);
    redisClusterConnect2(rcc);
    if (rcc && rcc->err) {
        std::cout << "connect error:" << rcc->err << std::endl;
        redisClusterFree(rcc);
        return 0;
    }
    redisReply *reply = (redisReply *) redisClusterCommand(rcc, "SET name life");
    if (reply && rcc && !rcc->err) {
        std::cout << "replay:" << reply->type << "|" << reply->str << "|" << reply->len << std::endl;
    }
    freeReplyObject(reply);
    redisClusterFree(rcc);
    return 0;
}
