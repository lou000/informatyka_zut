// PS IN1 320 LAB08
// Maciej Lewicki
// lm34410@zut.edu.pl
#ifndef SHARED_H
#define SHARED_H
#include <stddef.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <mqueue.h>
#include <signal.h>
#include <time.h>

#define MAX_HASH_LEN 256
#define MAX_PASS_LEN 512

#define LOG_ERR(...) \
        do { \
        int errsv = errno;\
        fprintf(stderr, __VA_ARGS__);\
        fprintf(stderr, "%d %s\n", errsv, strerror(errsv));}\
        while (0)

#define ASSERT_ERROR(val, val_on_error)\
    do { \
    if(val == val_on_error)\
    {\
        LOG_ERR("%s failed with error: ", #val);\
        assert(0);\
    }}\
    while (0)

enum WorkStatus{
    Started,
    Finished,
    Exit
};

struct smHeader{
    char hash[MAX_HASH_LEN];
    char saltAndId[MAX_HASH_LEN/2];
    size_t sm_size;
};

struct WorkDesc{
    uint id;
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
