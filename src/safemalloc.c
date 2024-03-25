/********************************************************************************
**
*A  safemalloc.c              Safer memory allocation
**
**
**  Copyright (C) 2024 - Daniel Pointon, J. D. Mitchell
**
**  This file is free software, see the digraphs/LICENSE.
**
********************************************************************************/

#include "safemalloc.h"
#include "digraphs-debug.h"
#include <stdlib.h>

void* safe_malloc(size_t size) {
  void* allocation = malloc(size);
  DIGRAPHS_ASSERT(allocation != NULL);

  return allocation;
}

void* safe_calloc(size_t nitems, size_t size) {
  void* allocation = calloc(nitems, size);
  DIGRAPHS_ASSERT(allocation != NULL);

  return allocation;
}
