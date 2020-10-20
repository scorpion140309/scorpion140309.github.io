#ifndef _CHECK_MULTI_ACTIVATION_H_
#define _CHECK_MULTI_ACTIVATION_H_


//! 多重起動をチェック、防止するクラス
/*!
 *	このクラスは、アプリケーションの多重起動を防ぐ機能を提供する。
 *
 */
class CHECK_MULTI_ACTIVATION
{
private:
	//! クラスの実装部(Handle-Body Idioms)
	class CHECK_MULTI_ACTIVATION_IMPL *p_impl__;
public:
	//! コンストラクタ
	CHECK_MULTI_ACTIVATION(void);
	//! デストラクタ
	~CHECK_MULTI_ACTIVATION(void);
	/*!
	 * 同じオブジェクト名を持つアプリケーションが既に実行されているかどうかを返す。
	 *	@param[in] a_p_obj_name	オブジェクト名を示す文字列
	 *	@return
	 *		同じオブジェクト名を持つアプリケーションが実行されていない場合、0を返す。
	 *		同じオブジェクト名を持つアプリケーションが実行されている場合、0以外を返す。
	 */
	int CheckAlreadyExists(const char *a_p_obj_name);
	/*!
	 * 多重起動をチェックするためのリソースを開放する。
	 * リソースが確保されていない場合、何も起こさない。
	 *	@return
	 *	なし
	 */
	void Close(void);
};

#endif	// _CHECK_MULTI_ACTIVATION_H_
