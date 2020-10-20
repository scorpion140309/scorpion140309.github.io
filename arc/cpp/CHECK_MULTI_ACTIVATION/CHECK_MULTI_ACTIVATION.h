#ifndef _CHECK_MULTI_ACTIVATION_H_
#define _CHECK_MULTI_ACTIVATION_H_


//! ���d�N�����`�F�b�N�A�h�~����N���X
/*!
 *	���̃N���X�́A�A�v���P�[�V�����̑��d�N����h���@�\��񋟂���B
 *
 */
class CHECK_MULTI_ACTIVATION
{
private:
	//! �N���X�̎�����(Handle-Body Idioms)
	class CHECK_MULTI_ACTIVATION_IMPL *p_impl__;
public:
	//! �R���X�g���N�^
	CHECK_MULTI_ACTIVATION(void);
	//! �f�X�g���N�^
	~CHECK_MULTI_ACTIVATION(void);
	/*!
	 * �����I�u�W�F�N�g�������A�v���P�[�V���������Ɏ��s����Ă��邩�ǂ�����Ԃ��B
	 *	@param[in] a_p_obj_name	�I�u�W�F�N�g��������������
	 *	@return
	 *		�����I�u�W�F�N�g�������A�v���P�[�V���������s����Ă��Ȃ��ꍇ�A0��Ԃ��B
	 *		�����I�u�W�F�N�g�������A�v���P�[�V���������s����Ă���ꍇ�A0�ȊO��Ԃ��B
	 */
	int CheckAlreadyExists(const char *a_p_obj_name);
	/*!
	 * ���d�N�����`�F�b�N���邽�߂̃��\�[�X���J������B
	 * ���\�[�X���m�ۂ���Ă��Ȃ��ꍇ�A�����N�����Ȃ��B
	 *	@return
	 *	�Ȃ�
	 */
	void Close(void);
};

#endif	// _CHECK_MULTI_ACTIVATION_H_
