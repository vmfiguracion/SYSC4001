/* A common header file to describe the shared memory we wish to pass about. */

#define TEXT_SZ 2048

struct shared_use_st {
	int shared_matrix[4][4];
    char some_text[TEXT_SZ];
};
