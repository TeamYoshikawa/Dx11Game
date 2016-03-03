#ifndef DEF_SINGLETON_H
#define DEF_SINGLETON_H
/*
シングルトン作成テンプレートクラス
Singleton<自作のクラス名>でそのポインタをシングルトンとして扱えます。
GetPtr()かGetRef()を使えば自作クラスのメンバにアクセス可能

ver 1.0
制作者:Ko Hashimoto
*/
template<class TYPE>
class Singleton
{

private:
	// テンプレート引数型を使うのに必要
	typedef TYPE Style;

	friend Style;

public:

	/*
	関数名 :GetInstance
	型    : テンプレート引数ポインタ型
	機能  : Createで確保したインスタンスのポインタを返します。
	*/
	static Style& GetInstance(){

		static Style m_instance;
		return m_instance;
	}

private:
	/*
	外部でのインスタンス化をやらせない
	*/
	Singleton() = default;
	virtual ~Singleton() = default;
};


#endif// !DEF_SINGLETON_H