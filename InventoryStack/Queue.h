#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class Queue
{
public:
	Queue()
		: m_count(0), m_head(0), m_tail(0)
	{
	}

	~Queue()
	{
		this->clear();
	}

	void clear()
	{
		internal_node *next;
		for (internal_node *it = m_head; it != 0; it = next)
		{
			next = it->next;
			delete it;
		}

		m_count = 0;
		m_head = 0;
		m_tail = 0;
	}

	void pop()
	{
		if (m_head != 0)
		{
			internal_node *next = m_head->next;
			delete m_head;
			m_head = next;
			--m_count;
		}
	}

	void push(T const& val)
	{
		internal_node *node = new internal_node(val, 0);
		if (m_head == 0)
			m_head = node;
		else
			m_tail->next = node;

		m_tail = node;
		m_count++;
	}

	inline bool empty() const {
		return (m_count == 0);
	}

	inline int size() const {
		return m_count;
	}

	inline T front() const {
		return m_head->data;
	}

	inline T back() const {
		return m_tail->data;
	}

protected:
	struct internal_node
	{
		internal_node(T const& val, internal_node *next)
			: data(val), next(next) { }

		T data;
		internal_node *next;
	};

	int m_count;
	internal_node *m_head;
	internal_node *m_tail;
};

#endif
