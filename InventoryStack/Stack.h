#ifndef STACK_H
#define STACK_H

template<class T>
class Stack
{
public:
	Stack()
		: count(0), head(0)
	{
	}

	~Stack()
	{
		this->clear();
	}

	void clear()
	{
		internal_node *next;
		for (internal_node *it = head; it != 0; it = next)
		{
			next = it->next;
			delete it;
		}

		count = 0;
		head = 0;
	}

	void pop()
	{
		if (head != 0)
		{
			internal_node *next = head->next;
			delete head;
			head = next;
			--count;
		}
	}

	void push(T const& val)
	{
		internal_node *node = new internal_node(val, head);
		head = node;
		count++;
	}

	inline bool empty() const {
		return (count == 0);
	}

	inline int size() const {
		return count;
	}

	inline T top() const {
		return head->data;
	}

private:
	struct internal_node
	{
		internal_node(T const& val, internal_node *next)
			: next(next), data(val) { }

		T data;
		internal_node *next;
	};

	int count;
	internal_node *head;
};


#endif
