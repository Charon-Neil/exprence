#include "student.h"

bool student::operator==(const student& st)
{
	if (this->id == st.id)
		return true;
	else
		return false;
}

bool student::operator<(const student& st)
{
	for (int i = 0; i < this->id.length(); i++) {
		if (this->id.at(i) < st.id.at(i)) {
			return true;
		}
		else if (this->id.at(i) > st.id.at(i)) {
			return false;
		}
	}
	//���ѭ��ȫ����������������,��ʱ���ý���
	return true;
}

