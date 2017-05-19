/*
 ============================================================================
 Name         : skipList.h
 Author        : Tim Budd
 Description : Skip List Data Structure Header File
 ============================================================================
 */

#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#ifndef TYPE
#define TYPE double
#endif

#ifndef EQ
#define EQ(a, b) (a == b)
#endif

#ifndef LT
#define LT(a, b) (a < b)
#endif

typedef struct skipLink {
    TYPE value;
    struct skipLink *next;
    struct skipLink *down;
} skipLink;

typedef struct {
    struct skipLink *topSentinel;
    int size;
} skipList;

/* the public interface */
void test(void);
void initSkipList(skipList *slst);
int containsSkipList(skipList *slst, TYPE e);
void removeSkipList(skipList *slst, TYPE e);
void addSkipList(skipList *slst, TYPE e);
int sizeSkipList(skipList *slst);
void printSkipList(skipList *slst);
void mergeSkipList(skipList *slst1, skipList *slst2);

/* internal routines */
int flipSkipLink();
skipLink *slideRightSkipList(skipLink *current, TYPE e);
skipLink *skipLinkAdd(skipLink *current, TYPE e);
skipLink *newSkipLink(TYPE e, skipLink *nextLnk, skipLink *downLnk);

#endif /* SKIPLIST_H_ */
