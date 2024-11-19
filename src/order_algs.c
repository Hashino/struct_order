#include "../include/order.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void _selectionSort(OrderStruct order, cmpFn cmp) {
  for (int i = 0; i < order.data_len - 1; i++) {
    int min_idx = i;

    for (int j = i + 1; j < order.data_len; j++) {
      void *curr = nthKEY(order, j);
      void *min = nthKEY(order, min_idx);

      if (cmp(curr, min)) {
        min_idx = j;
      }
    }

    if (i != min_idx)
      swap(order, i, min_idx);
  }
}
void selectionSort(OrderStruct order, cmpFn cmp) {
  _selectionSort(order, cmp); //
}

void _bucketSort(OrderStruct order, cmpFn eq, prefixFn prfx, void *prefixes,
                 int n_prefixes, int prefix_size, cmpFn cmp) {
  int *buckets = (int *)calloc(n_prefixes, sizeof(int));
  int *counts = (int *)calloc(n_prefixes, sizeof(int));

  void *curr_key_prefix = malloc(prefix_size + 1);
  void *curr_bucket_prefix = malloc(prefix_size + 1);

  // getting count of buckets
  // first iterates through keys
  for (int i = 0; i < order.data_len; i++) {
    prfx(nthKEY(order, i), curr_key_prefix);

    // for each key, iterates through buckets
    for (int j = 0; j < n_prefixes; j++) {
      // gets prefix of current bucket
      prfx(prefixes + (j * prefix_size), curr_bucket_prefix);

      // checks if bucket and key have same prefix
      if (eq(curr_key_prefix, curr_bucket_prefix)) {
        buckets[j]++;
        counts[j]++;

        break;
      }
    }
  }

  // reordering array into subarrays (buckets)
  int j = 0; // j is a variable which points at the index we are updating
  // first iterates through buckets
  for (int i = 0; j < order.data_len; i++) {
    // gets prefix of current bucket
    prfx(prefixes + (i * prefix_size), curr_bucket_prefix);

    // for each bucket, iterates through keys
    while (buckets[i] > 0) {
      for (int k = 0; buckets[i] > 0; k++) {
        // gets prefix of current key
        prfx(nthKEY(order, k), curr_key_prefix);

        // checks if bucket and key have same prefix
        if (eq(curr_bucket_prefix, curr_key_prefix)) {
          swap(order, j, k);

          j++;
          buckets[i]--;
        }
      }
    }
  }

  // ordering subarrays with selection sort (buckets)
  j = 0;
  // iterates through subarrays (buckets)
  for (int i = 0; j < order.data_len; i++) {
    if (counts[i]) {
      // sort each subarray (bucket) with selection sort
      selectionSort(order, cmp);
      j += counts[i];
    }
  }

  free(buckets);
  free(counts);
  free(curr_key_prefix);
  free(curr_bucket_prefix);
}

void bucketSort(OrderStruct order, cmpFn eq, prefixFn prfx, void *b_prefixes,
                int n_prefixes, int prefix_size, cmpFn cmp) {
  _bucketSort(order, eq, prfx, b_prefixes, n_prefixes, prefix_size, cmp);
}

int partition(OrderStruct order, cmpFn cmp, int left, int right) {
  void *pivot = nthKEY(order, right);
  int i = (left - 1);

  for (int j = left; j < right; j++) {
    void *curr_key = nthKEY(order, j);
    if (cmp(curr_key, pivot) || eqANY(curr_key, pivot, order.key_size)) {
      i++;
      swap(order, i, j);
    }
  }

  swap(order, i + 1, right);
  return (i + 1);
}

void _quickSort(OrderStruct order, cmpFn cmp, int left, int right) {
  if (left < right) {
    int part = partition(order, cmp, left, right);

    _quickSort(order, cmp, left, part - 1);
    _quickSort(order, cmp, part + 1, right);
  }
}

void quickSort(OrderStruct order, cmpFn cmp) {
  _quickSort(order, cmp, 0, order.data_len - 1);
}

void _radixSortInt(OrderStruct order, cmpFn cmp, bool asc) {
  void *output = malloc(order.data_len * order.data_entry_size);

  // Get maximum element
  int maxElement = *(int *)getMax(order, cmp);

  // Apply counting sort to sort elements based on place value
  for (int place = 1; maxElement / place > 0; place *= 10) {
    int count[10] = {0};

    for (int i = 0; i < order.data_len; i++) {
      int curr_key = *(int *)nthKEY(order, i);
      int index = (curr_key / place) % 10;
      count[index]++;
    }

    for (int i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }

    for (int i = order.data_len - 1; i >= 0; i--) {
      int curr_key = *(int *)nthKEY(order, i);
      int index = (curr_key / place) % 10;

      int target = (count[index] - 1) * order.data_entry_size;

      memcpy(output + target, nthENTRY(order, i), order.data_entry_size);

      count[index]--;
    }

    for (int i = 0; i < order.data_len; i++) {
      // decides if ascending or descending
      int target = asc ? i : order.data_len - 1 - i;
      memcpy(nthENTRY(order, target), output + (i * order.data_entry_size),
             order.data_entry_size);
    }
  }

  free(output);
}

void radixSort(OrderStruct order, char type, bool asc) {
  switch (type) {
  case 'i': // integer
    _radixSortInt(order, gtINT, asc);
    break;
  case 's': // string (char*)
    if (asc) {
      quickSort(order, ltBIN_STR);
    } else {
      quickSort(order, gtBIN_STR);
    }
    break;
  default:
    break;
  }
}
