// JHY_Linked_List.h: interface for the CJHY_Linked_List class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JHY_LINKED_LIST_H__90C987F2_361E_11D6_BA81_00B0D06FE5CC__INCLUDED_)
#define AFX_JHY_LINKED_LIST_H__90C987F2_361E_11D6_BA81_00B0D06FE5CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct	SimpleLL {
	struct SimpleLL*	next;
	void*			cont;
};
typedef	struct SimpleLL		slink;

class CJHY_Linked_List
{
public:
	CJHY_Linked_List();
	virtual ~CJHY_Linked_List();

	void tail_LL();
	void next_LL();
	int istail_LL();
	void* retrieve_LL();
	void head_LL();
	int size_LL();
	void delete_LL();
	slink* new_Link(void* newcontentsP);
	slink*	node_LL();
	void addnext_LL(void* newobjectP);	
	void* replace_LL(void* objectP);	// return old data pointer, and put it object pointer.

	// m_cl을 두 개이상의 프로세스에서 사용하게 되면, 문제가 될 수 있다. 
	// 보조 수단으로 데이터 검색만을 위해서 아래의 함수를 지원한다. 
	void sub_head_LL();
	void sub_next_LL();
	void* sub_retrieve_LL();
	int sub_istail_LL();
	void sub_tail_LL();

private:
	slink*  m_sub;
	slink*	m_cl;
	slink*	m_head;
	slink*	m_tail;
	int		m_len;
};

#endif // !defined(AFX_JHY_LINKED_LIST_H__90C987F2_361E_11D6_BA81_00B0D06FE5CC__INCLUDED_)
