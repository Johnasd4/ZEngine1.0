#ifndef ZPoolList_h
#define ZPoolList_h

#include"ZBasicDrive.h"


namespace ZEngine {


	/*
		池类链表类

	*/
	template<typename _ObjectType, Boolean threadSafe>
	class ZPoolList {

	private:

		/*
			节点类型
		*/
		template<typename _ObjectType>
		struct Node {
			//存储的object
			_ObjectType object;
			//下一个object地址
			Node* nextNodePtr;
		};



	protected:



		_ObjectType* applyObject() {
			
		}
		

	private:

		//链表头
		Node<_ObjectType>* headNodePtr;
		//池内容积
		Int32 capacity;

	};


}

#endif // !ZPoolList_h
