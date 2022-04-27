#include "subject.h"

Subject::Subject(QString tempNumber)
{
    number = tempNumber;
    studentsize = 0;
    struct stulist *head, *p1, *p2;
    head = NULL;
    p1 = p2 = NULL;
}

