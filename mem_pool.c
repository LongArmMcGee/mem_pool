#include "mem_pool.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool mem_pool_create(mem_pool* this, size_t num_chunks, size_t chunk_size)
{
    bool success = false;

    /* Chunks must be large enough to store a pointer to maintain link list when not used by user. */
    if(chunk_size > sizeof(sizeof(this)) &&
       this->p_alloc != NULL)
    {
        /* Set free pointer to first chunk */
        this->p_alloc = (Chunk*) malloc(num_chunks * chunk_size);

        Chunk* p_current = this->p_alloc;

        /* Thread linked list by walking forward chunk_size bytes and setting next ptr there */
        size_t i;
        for (i = 0; i < num_chunks - 1 /* -1 b/c head is done */; i++)
        {
            /* Need to increment by the chunk (user data) size before we write our linked list data */
            p_current->next = (Chunk*) ((uint8_t*) p_current + chunk_size);

            p_current = p_current->next;
        }

        success = true;
    }

    return success;
}

