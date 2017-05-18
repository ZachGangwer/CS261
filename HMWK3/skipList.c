#include "skipList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ************************************************************************
Main Function
 ************************************************************************ */
int main(int argc, char const *argv[]) {
    test();
    return 0;
}

/* TEST
 * Test function
 * no parameters
 * PRE:     no parameres
 * POST:    prints out the contents of the skip list
 */
void test() {
    /* int i, j; */
    int M;
    struct skipList *slst;
    test();

    srand(time(NULL));

    slst = (struct skipList *)malloc(sizeof(struct skipList)); /*2*/
    assert(slst);

    /*  Initialize the skip list */

    initSkipList(slst);

    /*  Add to the skip list  M = 20 random integers in [0,100] */

    for (M = 0; M < 20; M++) {
        addSkipList(slst, rand() % 101);
    }

    /*  Print out the contents of the skip list in the breadth-first order,
        starting from top.
        While printing the elements,
        move to a new line every time you reach the end of one level,
        and move down to the lower level of the skip list.
        For example, the print out of a skip list with 5 elements
        should look like

        7
        7 14 29
        3 7 9 14 20
     */

    printSkipList(slst);

    /* Develop 3 test cases for printing out the contents of skip list
     * after remove function:
            int removeSkipList(struct skipList *slst, TYPE e)
     */

    /*  FIXME */

    /* Develop 3 test cases corresponding to the above 3 test cases
       for printing out the output of contains function when e is equal to
       the elements you removed above:
             int containsSkipList(struct skipList *slst, TYPE e)
    */

    /*  FIXME */
}

/* ************************************************************************
Internal Functions
 ************************************************************************ */

/* FLIP_SKIP_LINK
 * Coin toss function:
 * NO_PARAMS
 * PRE: no parameres
 * POST: output is a random intiger number in {0,1}
 */
int flipSkipLink(void) {
    return rand() % 2;
}

/* SLIDE_RIGHT_SKIP_LIST
 * Move to the right as long as the next element is smaller than the input value
 * CURRENT: pointer to a place in the list from where we need to slide to the right
 * E:       input value PRE:	current is not NULL
 * POST:    returns one link before the link that contains the input value e
 */
struct skipLink *slideRightSkipList(struct skipLink *current, TYPE e) {
    while ((current->next != 0) && LT(current->next->value, e))
        current = current->next;
    return current;
}

/* NEW_SKIP_LINK
 * Create a new skip link for a value
 * E:       the value to create a link for
 * NEXTLNK: the new link's next should point to nextLnk
 * DOWNLNK: the new link's down should point to downLnk
 * PRE:     none
 * POST:    a link to store the value
 */
struct skipLink *newSkipLink(TYPE e, struct skipLink *nextLnk, struct skipLink *downLnk) {
    struct skipLink *tmp = (struct skipLink *)malloc(sizeof(struct skipLink));
    assert(tmp != 0);
    tmp->value = e;
    tmp->next = nextLnk;
    tmp->down = downLnk;
    return tmp;
}

/* SKIP_LIST_ADD
 * Add a new skip link recursively
 * CURRENT: pointer to a place in the list where the new element should be inserted
 * E:       the value to create a link for
 * PRE:     current is not NULL
 * POST:    a link to store the value
 */
struct skipLink *skipLinkAdd(struct skipLink *current, TYPE e) {
    /* *** TODO: LinkAdd *** */
    struct skipLink *newLink;
    if (current->down == NULL) {
        newLink = newSkipLink(e, current->next, NULL);
        current->next = newLink;
    } else {
        newLink = newSkipLink(e, current->next, skipLinkAdd(slideRightSkipList(current->down, e), e));
        current->next = newLink;
    }
    return newLink;
}

/* ************************************************************************
Public Functions
 ************************************************************************ */

/* INIT_SKIP_LIST
 * Initialize skip list:
 * SLST:    pointer to the skip list
 * PRE:     slst is not null
 * POST:    the sentinels are allocated, the pointers are set, and the list size equals zero
 */
void initSkipList(struct skipList *slst) {
    slst->size = 0;
    slst->topSentinel = (struct skipLink *)malloc(sizeof(struct skipLink));
    assert(slst->topSentinel);
    slst->topSentinel->next = NULL;
    slst->topSentinel->down = NULL;
}

/* CONTAINS_SKIP_LIST
 * Checks if an element is in the skip list:
 * SLST:    pointer to the skip list
 * E:       element to be checked
 * PRE:     slst is not null
 * POST:    returns true or false
 */
int containsSkipList(struct skipList *slst, TYPE e) {
    struct skipLink *tmp = slst->topSentinel;
    while (tmp != 0) {                                   /* 2pts */
        tmp = slideRightSkipList(tmp, e);                /* 1pt */
        if ((tmp->next != 0) && EQ(e, tmp->next->value)) /* 2pts */
            return 1;
        tmp = tmp->down; /* 1pt */
    }
    return 0;
}

/* REMOVE_SKIP_LIST
 * Remove an element from the skip list
 * SLST:    pointer to the skip list
 * E:       element to be removed
 * PRE:     slst is not null
 * POST:    the new element is removed from all internal sorted lists
 */
void removeSkipList(struct skipList *slst, TYPE e) {
    struct skipLink *current, *tmp;
    current = slst->topSentinel; /* 1pts */
    while (current != 0) {       /* 2pts */
        current = slideRightSkipList(current, e);
        if (current->next != 0 && EQ(e, current->next->value)) { /* 2pts */
            tmp = current->next;                                 /* 2pts */
            current->next = current->next->next;
            free(tmp); /* 2pts */
            if (current->down == NULL)
                slst->size--; /* 2pts */
        }
        current = current->down; /* 1pt */
    }
}

/* ADD_SKIP_LIST
 * Add a new element to the skip list
 * SLST:    pointer to the skip list
 * E:       element to be added
 * PRE:     slst is not null
 * POST:    e is added to the lowest list and randomly to higher-level lists
 */
void addSkipList(struct skipList *slst, TYPE e) {
    assert(slst != NULL);
    struct skipLink *current = slideRightSkipList(slst->topSentinel->next, e);

    while (flipSkipLink() && current->down != NULL) {
        current = slideRightSkipList(current->down, e);
    }

    skipLinkAdd(current, e);
}

/* SIZE_SKIP_LIST
 * Find the number of elements in the skip list:
 * SLST:    pointer to the skip list
 * PRE:     slst is not null
 * POST:    the number of elements
 */
int sizeSkipList(struct skipList *slst) {
    return slst->size;
}

/* TO_LINKED_LIST
 * Convert SkipList to LinkedList
 * NODE:    pointer to the first node in skip list
 * PRE:     slst is not null and slst is not empty
 * POST:    the links in the skip list are printed breadth-first, top-down
 */
struct skipLink *toLinkedList(struct skipLink *node) {
    while (node->down != NULL) {
        node = node->down;
    }
    return node;
}

/* PRINT_SKIP_LIST
 * Print the links in the skip list
 * SLST:    pointer to the skip list
 * PRE:     slst is not null and slst is not empty
 * POST:    the links in the skip list are printed breadth-first, top-down
 */
void printSkipList(struct skipList *slst) {
    /* *** TODO: Print *** */
    assert(slst != NULL && slst->size > 0);
    struct skipLink *sentinal = slst->topSentinel;
    struct skipLink *currNode = sentinal;

    while (sentinal != NULL) {
        while (currNode != NULL) {
            printf("%f\t", currNode->value);
            currNode = currNode->next;
        }
        sentinal = sentinal->down;
    }

    return;
}

/* MERGE_SKIP_LIST
 * Merge two skip lists:
 * SLST1:   pointer to the skip list 1.
 * SLST2:   pointer to the skip list 2.
 * PRE:     slst1 and slst2 != null, and skip list 1 and skip list 2 are not
 * POST:    slst1 points to the merger skip list, slst2 is null.
 */
void mergeSkipList(struct skipList *slst1, struct skipList *slst2) {
    assert((slst1 != NULL) && (slst2 != NULL));
    struct skipLink *currNode = toLinkedList(slst2->topSentinel);

    while (currNode->next != NULL) {
        addSkipList(slst1, currNode->value);
        currNode = currNode->next;
    }
}
