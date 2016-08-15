#pragma once
#include"GeomClose.h"
//这个类主要是实现把之前的封闭环之间串起来切割使用。
//实现，将封闭环之间排序，对圆这种特殊图形要另外处理，对于圆弧要转换成原来的数据形式
//包含封闭图元之间的过渡直线
//弄个单向链表来存储着一张排样dxf的数据

typedef struct NestResultDataNode//存储所有的图元的单向链表。
{
	
	struct GeomCloseHEAD*FirstGeomClose;//指向封闭环GeomCloseHEAD的头结点
	struct NestResultDataNode*prevNestResultDataNode;//指向前一个排样图数据结果NestResultDataNode的地址，在不同的排样结果图之间调用
	struct NestResultDataNode*nextNestResultDataNode;//指向前一个排样图数据结果NestResultDataNode的地址，在不同的排样结果图之间调用
	unsigned int NestResult_ID;//系统存储的第几张排样结果图，初始化为0。
	unsigned int m_NumGeomClose;//该双向链表存储的封闭环的个数
	bool AcceptNestResultflag;//是否已经被调用，初始化为false,目的不同排样结果图案中调用。
}NestResultDataNode;
//存储生产批次，一次开机就划出一块内存保存指向了这批生产加工的n张排样结果图，和每张排样结果图里面的n个封闭图形，和每个封闭图形里面的n个基本单元LINE,ARC,CIRCLE
typedef struct BatchHEAD
{
	unsigned int BatchHEAD_ID;
	unsigned int m_NumNestrsltDtNode;//这个批次有多少张排样结果图
	struct NestResultDataNode*FirstNestRsltNode;//指向第一张加工的排样图头结点
}BatchHEAD;
class GeomForCut
{
public:
	GeomForCut();
	~GeomForCut();
public:
	GeomClose geomclose;
	NestResultDataNode m_nestrsltNode;
public:
	
	BatchHEAD*CreatBatchHEAD(int BatchHEAD_ID);//初始化一块内存为头结点存放，无需参数传入
	NestResultDataNode*CreatNestResultNode(int NestResult_ID);//初始化一块内存来存放链表结点，无需参数传入
	//先无规律的把结点挂上
	NestResultDataNode*AddGeomCloseHeadNode(NestResultDataNode*head,GeomCloseHEAD*node);//输入每一个闭环的F头结点，把他们全部挂在一条链上。
	BatchHEAD*AddNestRsltDtNode(BatchHEAD*head, NestResultDataNode*node);//把每一张排样图的地址挂到以BatchHEAD为头结点的双向链表中。
	//把无规律的GeomEleNode找出其规律，转化成有规律的几个封闭环。
	//*************************************************************************//
	//步骤是先分封闭环，再在每一个封闭环里面对数据进行排序。
	//*************************************************************************//
	void SepDiffGeomCls(GeomCloseHEAD*head);//输入指向收录整张排样图全部基本图元的双向链表的F头结点
};

