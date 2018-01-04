#ifndef __LINKED_H__
#define __LINKED_H__

#define NAME_SIZE 128

struct Person
{
	int 	m_id;
	char 	m_name[NAME_SIZE];
	int 	m_age;
	struct Person* m_next;
};

typedef struct Person Person;


Person* ListInsertHead(Person* _head, Person* _p);

Person* ListRemoveHead(Person* _head, Person** _item);
/*

*/
Person* ListInsertByKey(Person* _head, int _key, Person* _p);
/*

*/
Person* ListInsertByKeyRec(Person* _head, int key, Person* _p);
/*

*/
Person* ListRemoveByKey(Person* _head, int _key, Person** _p);
/*

*/
Person* ListRemoveByKeyRec(Person* _head, int key, Person** _p);
/*

*/
void PrintList(Person* _head);

#endif /* endif __LINKED_H__ */

