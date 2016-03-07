#ifndef DEF_SINGLETON_H
#define DEF_SINGLETON_H
/*
�V���O���g���쐬�e���v���[�g�N���X
Singleton<����̃N���X��>�ł��̃|�C���^���V���O���g���Ƃ��Ĉ����܂��B
GetPtr()��GetRef()���g���Ύ���N���X�̃����o�ɃA�N�Z�X�\

ver 1.0
�����:Ko Hashimoto
*/
template<class TYPE>
class Singleton
{

private:
	// �e���v���[�g�����^���g���̂ɕK�v
	typedef TYPE Style;

	friend Style;

public:

	/*
	�֐��� :GetInstance
	�^    : �e���v���[�g�����|�C���^�^
	�@�\  : Create�Ŋm�ۂ����C���X�^���X�̃|�C���^��Ԃ��܂��B
	*/
	static Style& GetInstance(){

		static Style m_instance;
		return m_instance;
	}

private:
	/*
	�O���ł̃C���X�^���X������点�Ȃ�
	*/
	Singleton() = default;
	virtual ~Singleton() = default;
};


#endif// !DEF_SINGLETON_H