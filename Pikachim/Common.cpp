#include "stdafx.h"
#include "Common.h"

NODE_ makeNode(int x, int y){
	NODE_ temp = {x, y};
	return temp;
}

bool sosanh(NODE_ A, NODE_ B){
	return (A.x == B.x && A.y == B.y);
}

DoubleNode::DoubleNode(){
	node1_.x = 0;
	node2_.x = 0;
	node1_.y = 0;
	node2_.y = 0;
}