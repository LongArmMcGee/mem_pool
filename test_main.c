#include "mem_pool.h"
#include "CUnit/Basic.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/* Pointer to the file used by the tests. */

typedef struct 
{
   uint32_t data1;
   uint32_t data2;
} test_object;


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite_mem_pool(void)
{

   return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite_mem_pool(void)
{
   return 0;
}

/* Simple test of fprintf().
 * Writes test data to the temporary file and checks
 * whether the expected number of bytes were written.
 */
void test_mem_pool_create(void)
{
   mem_pool test_pool;
   size_t pool_size = 3;

   CU_ASSERT_TRUE(mem_pool_create(&test_pool, pool_size, sizeof(test_object)));

   uint8_t* p_current = (uint8_t*) test_pool.p_alloc;
   Chunk* p_next = test_pool.p_alloc;
   
   int i;
   for (i = 0; i < pool_size; i++)
   {
      CU_ASSERT_PTR_EQUAL((p_current + sizeof(test_object)), test_pool.p_alloc->next);
      p_current = (uint8_t*) p_next;
      p_next = p_next->next;
   }

   /* List is terminated with null next pointer */
   CU_ASSERT_PTR_NULL(p_next);
}

/* Simple test of fread().
 * Reads the data previously written by testFPRINTF()
 * and checks whether the expected characters are present.
 * Must be run after testFPRINTF().
 */
void test_mem_pool_alloc(void)
{

   CU_ASSERT_TRUE(true);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite__mem_pool", init_suite_mem_pool, clean_suite_mem_pool);
   if (NULL == pSuite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of fprintf()", test_mem_pool_create)) ||
       (NULL == CU_add_test(pSuite, "test of fread()", test_mem_pool_alloc)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}