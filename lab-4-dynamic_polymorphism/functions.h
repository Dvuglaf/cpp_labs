#pragma once
#include<memory>
/*�������� �������: ������� �� ����� ����������
.
����������, ��� �������, ��������� ����� ���������:
����������� �������� ������� ��� �������� ���������;
���������� �������, ���������� ����������� �� �������;
������������, ��� �������, ��������� ����
������:
���������;
�������� �������;
������������ �������;
�����;
�������.

� �������� ���� ���������� ������������ ����������� ����������� ������� � ����������,
����������� ������� ��� ��������� ��������� ��������� ���������� ��������
.
��������� �������� �����:������������ �������; �����������;�������� �����������
. ���� ����� ������� ���������, ������� ������ �� ���
.���������� ������������ ����� ���������: ����� ����� � � �������������� ���������� ����������� ����������.*/
class functions
{
public:
	virtual std::shared_ptr<functions> derivative()noexcept = 0;
	virtual double value_point(double) const noexcept = 0;
	virtual bool equals(const functions& ) const noexcept = 0;//��������� ���� �� ���������
	virtual void print()const noexcept = 0;//���������� ���������� ������������� �������
	virtual ~functions() = default;
protected:
	/*functions() = default;
	functions(const functions&) = default;
	functions& operator=(const functions&) = default;*/
};