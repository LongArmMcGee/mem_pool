#include <stdbool.h>
#include <stddef.h>

typedef struct Chunk* p_alloc;

/* May be necessary in some cases? I don't think so*/
/* struct Chunk; */

typedef struct 
{
    /* Haven't figured out how to get around needing struct keyword here */
    struct Chunk* next;
} Chunk;

/*
 * Memory Pool
 * Limited memory pool which allocates space off the heap only at initialization.
 * This allows the user to limit heap allocation of the application and avoid head memory risks.
 * Implemented as a linked list which exists in the users data chunks. 
 * This requires chunk size > pointer size (4 bytes).
 */

typedef struct 
{
    size_t chunk_size;      /* Single object size */
    size_t num_elements;    /* Number of objects in pool. Uneeded?*/
    Chunk* p_alloc;
} mem_pool;

/*
 * Constructor
 * 
 * @param num_chunks creates allocates the numberof chunks in the pool
 * 
 */
bool mem_pool_create(mem_pool* this, size_t num_chunks, size_t chunk_size);

void mem_pool_alloc();