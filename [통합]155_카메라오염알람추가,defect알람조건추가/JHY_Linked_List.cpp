// JHY_Linked_List.cpp: implementation of the CJHY_Linked_List class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JHY_Linked_List.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJHY_Linked_List::CJHY_Linked_List()
{
	m_head = m_cl = new_Link(NULL);
	m_tail = m_head->next = new_Link(NULL);
	m_tail->next = m_tail;
	m_len = 0;
}

CJHY_Linked_List::~CJHY_Linked_List()
{
	slink *te,*de;
	te = de = m_head->next;
	while(te != m_tail)
	{
		te = te->next;
		free(de);	// Remember!! when freeing this might cause dangling of the void* data!
		de = te;		
	}

	free(m_head);
	free(m_tail);
}

void CJHY_Linked_List::addnext_LL(void *newobjectP)
{
	slink*	newlinkP;

	newlinkP = new_Link(newobjectP);

	newlinkP->next = m_cl->next;
	m_cl = m_cl->next = newlinkP;
	m_len++;
}

void* CJHY_Linked_List::replace_LL(void *objectP)
{
	void* old_object = m_cl->cont;
	m_cl->cont = objectP;

	return old_object;
}

void CJHY_Linked_List::delete_LL()
{
	slink*	delLinkP;
	slink*	curLinkP;

	head_LL();
	curLinkP = m_cl;

	for (int i=0; i<m_len; i++) 
	{
		if (curLinkP->next != NULL) 
		{
			delLinkP = curLinkP;
			curLinkP = curLinkP->next;
			free(delLinkP);
		}
		else 
		{
			free(curLinkP);
			break;
		}
	}
	CJHY_Linked_List();
}

slink* CJHY_Linked_List::new_Link(void *newcontentsP)
{
	slink* lP;
	lP = (slink *) malloc(sizeof(slink));
	lP->cont = newcontentsP;
	return lP;
}

slink* CJHY_Linked_List::node_LL()
{
	return m_cl;
}

int CJHY_Linked_List::size_LL()
{
	return m_len;
}

void CJHY_Linked_List::head_LL()
{
	m_cl = m_head;
}

void CJHY_Linked_List::tail_LL()
{
	for(;!istail_LL();)
		next_LL();
}

void* CJHY_Linked_List::retrieve_LL()
{
	return m_cl->cont;
}

int CJHY_Linked_List::istail_LL()
{
	return (m_cl->next == m_tail);
}

void CJHY_Linked_List::next_LL()
{
	m_cl = m_cl->next;
}



// m_cl을 두 개이상의 프로세스에서 사용하게 되면, 문제가 될 수 있다. 
// 보조 수단으로 데이터 검색만을 위해서 아래의 함수를 지원한다. 
void CJHY_Linked_List::sub_head_LL()
{
	m_sub = m_head;
}

void CJHY_Linked_List::sub_next_LL()
{
	m_sub = m_sub->next;
}

void* CJHY_Linked_List::sub_retrieve_LL()
{
	return m_sub->cont;
}

int CJHY_Linked_List::sub_istail_LL()
{
	return (m_sub->next == m_tail);
}

void CJHY_Linked_List::sub_tail_LL()
{
	for(;!istail_LL();)
		sub_next_LL();
}
