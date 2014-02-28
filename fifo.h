/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/*****************************************************************************/
/* fifo                                                                      */
/* Author: Olivier Ly                                                        */
/* Date : 2008/07                                                            */
/*****************************************************************************/
#ifndef FIFO_H
#define FIFO_H

#include <stdlib.h>
#include <stdio.h>
#include "util.h"

/* General use fifo.
 * The fifo size must be less than 255 byte, because of the 
 * size of the indexes. */

/*****************************************************************************/
/* Data Structure                                                            */
/*****************************************************************************/

template <typename FIFO_TYPE>
class Fifo {

  FIFO_TYPE * q_buffer;
  int q_size;
  int q_start;
  int q_end;

  /* fifo index manipulation */
  inline
  int incr_index(int i) {
    int idx = i;
    idx++;
    if (idx == q_size)
      idx=0;
    return idx;
  }

public:
  Fifo(int size);
  ~Fifo();

  void reset_fifo();
  int size();
  bool full();

  /* get a new byte from the fifo.
   * Caution: if the fifo is empty, return 0. */
  FIFO_TYPE get_item();

  /* get a new byte from the fifo.
   * Caution: if the fifo is empty, return 0. */
  FIFO_TYPE get_nth_item(int idx);
  
  /* Push a new byte into the fifo. */
  void push_item(FIFO_TYPE b);
  
};

/*****************************************************************************/

template <typename FIFO_TYPE>
Fifo<FIFO_TYPE>::Fifo(int siz) {
  
  q_buffer = (FIFO_TYPE*) malloc((siz+1)*sizeof(FIFO_TYPE));
  if (q_buffer == NULL) {
    printf("FIFO buffer allocation error!\n");
    return;
  }

  q_size = siz+1;
  reset_fifo();
}

template <typename FIFO_TYPE>
Fifo<FIFO_TYPE>::~Fifo() {
  free(q_buffer);
}

template <typename FIFO_TYPE>
void Fifo<FIFO_TYPE>::reset_fifo() {
  /* set the starting of the fifo to 0 */
  q_start=0;
  /* set current position to 0 */
  q_end=0;
}

template <typename FIFO_TYPE>
int Fifo<FIFO_TYPE>::size() {
  if (q_end >= q_start)
    return q_end - q_start;
  else
    return q_end + (q_size - q_start);
}

template <typename FIFO_TYPE>
FIFO_TYPE Fifo<FIFO_TYPE>::get_item() {
  FIFO_TYPE c;
  
  if (q_start == q_end)
    return c;
  
  c = q_buffer[q_start];
  q_start = incr_index(q_start);
  return c;
}

template <typename FIFO_TYPE>
FIFO_TYPE Fifo<FIFO_TYPE>::get_nth_item(int idx) {
  return q_buffer[(q_start + idx) % q_size];
}

template <typename FIFO_TYPE>
bool Fifo<FIFO_TYPE>::full() {
  int idx = incr_index(q_end);
  return (idx == q_start);
}

template <typename FIFO_TYPE>
void Fifo<FIFO_TYPE>::push_item(FIFO_TYPE b) {
  int idx = incr_index(q_end);
  
  if (idx == q_start) {
    printf("FIFO buffer full, push operation aborted [q_start=%d; q_end=%d; q_size=%d].\n", q_start, q_end, q_size);
    return;
  }

  q_buffer[q_end] = b;
  q_end = idx;
}

#endif /* FIFO_H */
/*****************************************************************************/
/*****************************************************************************/
