#include "filelist_cache.h"

bool keyeq_func(const HTableNode* a_, const HTableNode* b_, void *arg)
{
  (void) arg;
  filelist_cache_data_t* a = (filelist_cache_data_t*)a_;
  filelist_cache_data_t* b = (filelist_cache_data_t*)b_;
  return (strcmp(a->filename, b->filename) == 0);
}

uint32_t hash_func(const HTableNode* a_, void *arg)
{
  (void) arg;
  filelist_cache_data_t* a = (filelist_cache_data_t*)a_;
  return htable_default_hash(a->filename, strlen(a->filename));
}

void* alloc_func(size_t size, void *arg)
{
  (void) arg;
  return malloc(size);
}

void free_func(void* mem, void *arg)
{
  (void) arg;
  free(mem);
}

void filelist_cache_create(HTable *hTable) {
  htable_create(hTable,
		sizeof(filelist_cache_data_t),
		hash_func,
		keyeq_func,
		alloc_func,
		free_func,
		NULL,
		NULL);
}

void filelist_cache_free(HTable *hTable) {
  htable_free_items(hTable);
  filelist_cache_create(hTable);
}
