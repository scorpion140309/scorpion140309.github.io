#include "CHECK_MULTI_ACTIVATION.h"

#include <windows.h>

////////////////////////////////

class CHECK_MULTI_ACTIVATION_IMPL
{
private:
	HANDLE hMutex__;
public:
	CHECK_MULTI_ACTIVATION_IMPL(void);
	~CHECK_MULTI_ACTIVATION_IMPL(void);

	int IMPL_CheckAlreadyExists(const char *a_p_obj_name);
	void IMPL_Close(void);
};

// constructor
CHECK_MULTI_ACTIVATION_IMPL::CHECK_MULTI_ACTIVATION_IMPL(void)
{
	this->hMutex__ = NULL;
}

// destructor
CHECK_MULTI_ACTIVATION_IMPL::~CHECK_MULTI_ACTIVATION_IMPL(void)
{
	this->IMPL_Close();
}

//
int CHECK_MULTI_ACTIVATION_IMPL::IMPL_CheckAlreadyExists(const char *a_p_obj_name)
{
	// リソース開放
	// 開放されるべきリソースがない場合、何も起きない。
	this->IMPL_Close();

	int ret_flag_exist = 1;

	SECURITY_DESCRIPTOR sd;
	SECURITY_ATTRIBUTES secAttribute;

	::InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	::SetSecurityDescriptorDacl(&sd, TRUE, 0, FALSE);
	secAttribute.nLength = sizeof(secAttribute);
	secAttribute.lpSecurityDescriptor = &sd;
	secAttribute.bInheritHandle = TRUE;


	this->hMutex__ = ::CreateMutex(&secAttribute, FALSE, a_p_obj_name);
	if (this->hMutex__ != NULL)
	{
		if (::GetLastError() != ERROR_ALREADY_EXISTS)
		{
			ret_flag_exist = 0;
		}
		else
		{
			this->IMPL_Close();
			ret_flag_exist = 1;
		}
	}
	else
	{
		ret_flag_exist = 0;
	}

	//
	return ret_flag_exist;
}

//
void CHECK_MULTI_ACTIVATION_IMPL::IMPL_Close(void)
{
	if (this->hMutex__)
	{
		::ReleaseMutex(this->hMutex__);
		::CloseHandle(this->hMutex__);
		this->hMutex__ = NULL;
	}
}

/////////////////////////

// 二重起動チェック

// constructor
CHECK_MULTI_ACTIVATION::CHECK_MULTI_ACTIVATION(void)
{
	this->p_impl__ = new CHECK_MULTI_ACTIVATION_IMPL;
}

// destructor
CHECK_MULTI_ACTIVATION::~CHECK_MULTI_ACTIVATION(void)
{
	if (this->p_impl__)
	{
		delete this->p_impl__;
		this->p_impl__ = NULL;
	}
}

//
int CHECK_MULTI_ACTIVATION::CheckAlreadyExists(const char *a_p_obj_name)
{
	int ret_flag_exist = -1;
	if (this->p_impl__)
	{
		ret_flag_exist = this->p_impl__->IMPL_CheckAlreadyExists(a_p_obj_name);
	}
	return ret_flag_exist;
}

//
void CHECK_MULTI_ACTIVATION::Close(void)
{
	if (this->p_impl__)
	{
		this->p_impl__->IMPL_Close();
	}
}
