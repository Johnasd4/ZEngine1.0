#ifndef ZPoolList_h
#define ZPoolList_h

#include"ZBasicDrive.h"


namespace ZEngine {


	/*
		����������

	*/
	template<typename _ObjectType, Boolean threadSafe>
	class ZPoolList {

	private:

		/*
			�ڵ�����
		*/
		template<typename _ObjectType>
		struct Node {
			//�洢��object
			_ObjectType object;
			//��һ��object��ַ
			Node* nextNodePtr;
		};



	protected:



		_ObjectType* applyObject() {
			
		}
		

	private:

		//����ͷ
		Node<_ObjectType>* headNodePtr;
		//�����ݻ�
		Int32 capacity;

	};


}

#endif // !ZPoolList_h
