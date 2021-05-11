// PS IN1 320 LAB08
// Maciej Lewicki
// lm34410@zut.edu.pl
#ifndef SHARED_H
#define SHARED_H
#include <stddef.h>
#include <sys/types.h>
#define MAX_HASH_LEN 256
#define MAX_PASS_LEN 512

enum WorkStatus{
    Started,
    Finished,
    Error
};

struct smHeader{
    char hash[MAX_HASH_LEN];
    char saltAndId[MAX_HASH_LEN/2];
};

struct WorkDesc{
    size_t size;
    size_t offset;
};

struct WorkMsg{
    pid_t pid;
    enum   WorkStatus status;
    struct WorkDesc left;
    char msg[MAX_PASS_LEN];
};

const char mq_work_name[]         = "/workQ";
const char mq_return_name[]       = "/returnQ";
const char shared_mem_name[]      = "/sm";

#endif // SHARED_H
