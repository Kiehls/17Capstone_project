#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <vector>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

typedef char (*State)[WIDTH_SIZE] ;

class node
{
public:
   int host;
   char arr[HEIGHT_SIZE][WIDTH_SIZE] ;
   node(State board);
   node();

   int num_of_han;
   int num_of_cho;

   // state�� ���¸� ����Ѵ�.
   void Print_State();

   // state�� ���� ��ȯ
   State returnState();

   // state�� ���¸� �ʱ�ȭ�Ѵ�.
   void UnitOrder(int cho_order, int han_order);

   // state�� ���¸� �����Ѵ�.
   void changeState(int pos[], char unit);

   // state�� ��, ���� ���� ������ ���Ѵ�.
   void getNumOfUnit();
};

#endif
