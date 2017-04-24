#include "stdafx.h"
#include "CutLeadLine.h"


CutLeadLine::CutLeadLine()
{
}


CutLeadLine::~CutLeadLine()
{
}
double CutLeadLine::Get_k_twoPoint(Line_para a)
{
	double k;//б��
	if (a.x0 != a.x1)//б�ʴ���
	{
		return k = (a.y0 - a.y1) / (a.x0 - a.x1);
	}
	else//б�ʲ����ڣ�����һ����ֵ
	{
		return k = 999.12;
	}
}
//�жϼнǵĿ��ڷ���,1Ϊ���Ͽ��ڣ�2Ϊ���¿��ڣ�3Ϊ���󿪿ڣ�4Ϊ���ҿ��ڡ�
int  CutLeadLine::Get_OpenDirect(Line_para a, Line_para b)
{
	//����ab��x0,y0������ͬ��
	int m_opendirect = 0;
	//����и���Ƶ��Y����Сֵ����ô�������Ͽ���
	if ((a.y0 <= a.y1) && (b.y0 <= b.y1))
	{
		return m_opendirect = 1;//���Ϸ��򿪿�
	}
	//����и���Ƶ��Y�����ֵ����ô�������¿���
	else if ((a.y0 >= a.y1) && (b.y0 >= b.y1))
	{
		return m_opendirect = 2;//���·��򿪿�
	}
	//���¿��ڷ���Ƚ��������֣����ҿ��ڷ�������Ҫ�ֶ����������
	//����б���������ж�����
	//�����ж����ҿ���
	else if (a.k*b.k<0)//б��һ��һ��
	{
		//xΪ���ֵ���������򿪿�
		if ((a.x0 >= a.x1) && (b.x0 >= b.x1))
		{
			return m_opendirect = 3;
		}
		else//xΪ��Сֵ�������ҷ��򿪿�
		{
			return m_opendirect = 4;
		}
	}
	//б��ͬ����ʱ��
	else if (a.k >= 0 && b.k >= 0)
	{
		//б��С��x1С��б�ʴ��x1����������
		if (a.k<b.k && a.x1<b.x1)
		{
			return m_opendirect = 3;
		}
		else//б��С��x1��б�ʴ��x1С���������ҿ�
		{
			return m_opendirect = 4;
		}
	}
	//б��ͬ����ʱ��
	else if (a.k <= 0 && b.k <= 0)
	{
		//б��С��x1��б�ʴ��x1С����������
		if (a.k<b.k && a.x1>b.x1)
		{
			return m_opendirect = 3;
		}
		else//б��С��x1С��б�ʴ��x1���������ҿ�
		{
			return m_opendirect = 4;
		}
	}
}
//��������ֱ�ߵ�б�ʣ��ͼнǵĿ��ڷ���
double CutLeadLine::Get_k_twoK(double k1, double k2, int m_opendirect)
{
	double k = 0.0;
	double a, b, c;
	double d;//�����и�������ƫת�ǵĻ���
	if ((k1 != 999.12) && (k2 != 999.12))//����ֱ�ߵ�б�ʾ����ڵ������
	{
		a = atan(k1) * 180 / pii;//��б��
		b = atan(k2) * 180 / pii;//��б��
	}
	else if (k1 == 999.12)//k1�Ǵ�ֱ��û��б��
	{
		a = 90.0;//����90��
		b = atan(k2) * 180 / pii;//��б��
	}
	else if (k2 == 999.12)//k2�Ǵ�ֱ��û��б��
	{
		a = atan(k1) * 180 / pii;//��б��
		b = 90.0;//����90��
	}
	//�Դ���90�ȵ���б�ǽ���ת��
	//����ֱ�߿��Թ��������нǣ�Ҫ�жϼнǿ��ڷ���
	//���Y����ֵ��ô�����¿��ڣ����������ô�������ҿ���
	if (m_opendirect == 3 || m_opendirect == 4)//���ҿ���
	{
		if (a*b<0)//б��һ��һ��
		{
			c = (a + b) / 2;//ֱ�����/2
		}
		else if ((a >= 0) && (b >= 0))//б�ʶ�������
		{
			if (a>b)//б�ʴ��ȡ���Ĳ��Ǻ����
			{
				a = a - 180;
			}
			else
			{
				b = b - 180;
			}
			c = (a + b) / 2;//ֱ�����/2
		}
		else//�������Ǹ��������
		{
			if (a<b)//б��С��ȡ������
			{
				a = 180 + a;
			}
			else
			{
				b = 180 + b;
			}
			c = (a + b) / 2;//ֱ�����/2
		}
	}
	else//�н����¿��ڵ�ʱ�򣬴�ʱ�и���Ƶ��yֵ������ֵ
	{
		if (a*b<0)//б��һ��һ��,������ȡ����
		{
			if (a<0)
			{
				a = 180 + a;
			}
			else
			{
				b = 180 + b;
			}
			c = (a + b) / 2;//ֱ�����/2
		}
		else if ((a >= 0) && (b >= 0))//б�ʶ�������
		{
			c = (a + b) / 2;//ֱ�����/2
		}
		else//�������Ǹ��������
		{
			c = (a + b) / 2;//ֱ�����/2
		}
	}
	if (c != 90)
	{
		d = (c / 180)*pii;
		k = tan(d);
	}
	else
		k = 999.12;
	return k;
}
//ǰ���Ѿ���������и������ߵ�б��
//���룬�и���Ƶ㣬�и������ߵ�б�ʣ���ջ��ĵ�˫����ȡ�Ǹ��и������ߵ����
//��������ȡֵ��˫������ȡֵ
//������ֵ�������
Line_para 	CutLeadLine::Get_CutLine_Point(Point start, double k)
{
	//ֱ�߷��̣�y = k(x-a) + b��
	//Բ���̣�(x - a) ^ 2 + (y - b) ^ 2 = r ^ 2;
	Line_para Lp;
	double x1, x2, y1, y2;//��������
	double a, b, r;
	a = start.x;
	b = start.y;
	r = 25.0;//�����߳���
	x1 = a + sqrt(r*r / (1 + k*k));
	y1 = b + k*sqrt(r*r / (1 + k*k));
	x2 = a - sqrt(r*r / (1 + k*k));
	y2 = b - k*sqrt(r*r / (1 + k*k));
	Lp.x0 = x1;
	Lp.x1 = x2;
	Lp.y0 = y1;
	Lp.y1 = y2;
	Lp.k = k;//�����и������ߵ�б�ʣ��Ժ��õ���
	return Lp;
}
//���ݿ��ڷ���ͷ�ջ���˫��ȡ����һ��ֵ��Ϊ�и������ߵ����
//������������ֵ�����뿪�ڷ������뵥˫��,�����и���Ƶ�
//����и�������ͼԪ
Line_para CutLeadLine::Get_CutLine_StartPoint(Line_para m_Line, int m_OpenDirect, bool m, Point start)
{
	Line_para m_CutGuideL;
	m_CutGuideL.x1 = start.x;
	m_CutGuideL.y1 = start.y;
	m_CutGuideL.k = m_Line.k;
	//����ǵ�����ô��Ҫ����ȡֵ
	//����������ϣ���ȡyС�ģ��������£���ȡy��ġ�
	//�������������ȡx��ģ��������ң���ȡxС�ġ�
	if (m)//����
	{
		switch (m_OpenDirect)
		{
		case 1://��������
			if (m_Line.y0<m_Line.y1)
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			break;
		case 2://��������
			if (m_Line.y0<m_Line.y1)
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			break;
		case 3://��������
			if (m_Line.x0<m_Line.x1)
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			break;
		case 4://��������
			if (m_Line.x0<m_Line.x1)
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			break;
		default:
			break;
		}
	}
	//˫�㣬����ȡ
	//����������ϣ���ȡy��ģ��������£���ȡyС�ġ�
	//�������������ȡxС�ģ��������ң���ȡx��ġ�
	else
	{
		switch (m_OpenDirect)
		{
		case 1://��������
			if (m_Line.y0<m_Line.y1)
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			break;
		case 2://��������
			if (m_Line.y0<m_Line.y1)
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			break;
		case 3://��������
			if (m_Line.x0<m_Line.x1)
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			break;
		case 4://��������
			if (m_Line.x0<m_Line.x1)
			{
				m_CutGuideL.x0 = m_Line.x1;
				m_CutGuideL.y0 = m_Line.y1;
			}
			else
			{
				m_CutGuideL.x0 = m_Line.x0;
				m_CutGuideL.y0 = m_Line.y0;
			}
			break;
		default:
			break;
		}
	}
	return m_CutGuideL;
}
//������ֹ��ջ�����ͼԪ���ͷ�ջ���˫���ʣ����и������߻�������
Line_para CutLeadLine::Get_CutLeadLine(Line_para a, Line_para b, bool m)
{
	Point start;
	double k = 0.0;
	Line_para m_Line;
	Line_para m_CutGuideL;
	int m_opendirect;//���ڷ����ж�,1���Ͽ���2���¿���3���󿪣�4���ҿ�
	start.x = a.x0;
	start.y = a.y0;
	a.k = Get_k_twoPoint(a);
	b.k = Get_k_twoPoint(b);
	m_opendirect = Get_OpenDirect(a, b);//�жϼнǿ��ڷ���
	k = Get_k_twoK(a.k, b.k, m_opendirect);//���и�������б��
	m_Line = Get_CutLine_Point(start, k);
	m_CutGuideL = Get_CutLine_StartPoint(m_Line, m_opendirect, m, start);
	return m_CutGuideL;
}


